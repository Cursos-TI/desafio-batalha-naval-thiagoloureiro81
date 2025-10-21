
 // Batalha Naval
 

#include <stdio.h>
#include <stdbool.h>

#define BOARD_SIZE 10
#define SHIP_SIZE  3
#define WATER      0
#define SHIP       3

/* Orientacoes suportadas:
 * ORIENT_H   -> horizontal (para a direita)
 * ORIENT_V   -> vertical   (para baixo)
 * ORIENT_DDR -> diagonal   (↘: linha+1, coluna+1)
 * ORIENT_DDL -> diagonal   (↙: linha+1, coluna-1)
 */
typedef enum {
    ORIENT_H,
    ORIENT_V,
    ORIENT_DDR,
    ORIENT_DDL
} Orientation;

/* Representa um navio: posicao inicial (linha, coluna) e orientacao */
typedef struct {
    int row;
    int col;
    Orientation orient;
} Ship;

/* Inicializa todo o tabuleiro com WATER (0) */
static void init_board(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            board[r][c] = WATER;
        }
    }
}

/* Imprime cabecalhos e o tabuleiro formatado */
static void print_board(const int board[BOARD_SIZE][BOARD_SIZE]) {
    // Cabecalho das colunas
    printf("    ");
    for (int c = 0; c < BOARD_SIZE; c++) {
        printf("%2d ", c);
    }
    printf("\n");

    // Linha separadora
    printf("   ");
    for (int c = 0; c < BOARD_SIZE; c++) {
        printf("---");
    }
    printf("-\n");

    // Linhas com os valores
    for (int r = 0; r < BOARD_SIZE; r++) {
        printf("%2d |", r);
        for (int c = 0; c < BOARD_SIZE; c++) {
            printf(" %d ", board[r][c]);
        }
        printf("\n");
    }
}

/* Verifica se (row, col) esta dentro do tabuleiro */
static inline bool within_bounds(int row, int col) {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

/* Converte a orientacao em (dr, dc), o passo a cada segmento do navio */
static void step_from_orientation(Orientation o, int *dr, int *dc) {
    switch (o) {
        case ORIENT_H:   *dr = 0; *dc = 1;  break; // direita
        case ORIENT_V:   *dr = 1; *dc = 0;  break; // baixo
        case ORIENT_DDR: *dr = 1; *dc = 1;  break; // diagonal ↘
        case ORIENT_DDL: *dr = 1; *dc = -1; break; // diagonal ↙
        default:         *dr = 0; *dc = 0;  break;
    }
}

/* Verifica se e possivel posicionar um navio de tamanho SHIP_SIZE
 * a partir de (row, col) seguindo a orientacao 'o', SEM:
 * - sair do tabuleiro
 * - sobrepor outro navio (cobre ortogonal e diagonal)
 */
static bool can_place_ship(const int board[BOARD_SIZE][BOARD_SIZE],
                           int row, int col, Orientation o) {
    int dr, dc;
    step_from_orientation(o, &dr, &dc);

    for (int k = 0; k < SHIP_SIZE; k++) {
        int rr = row + dr * k;
        int cc = col + dc * k;

        if (!within_bounds(rr, cc)) {
            return false; // extrapola tabuleiro
        }
        if (board[rr][cc] != WATER) {
            return false; // sobreposicao
        }
    }
    return true;
}

/* Aplica o posicionamento do navio no tabuleiro (assume que pode) */
static void place_ship(int board[BOARD_SIZE][BOARD_SIZE],
                       int row, int col, Orientation o) {
    int dr, dc;
    step_from_orientation(o, &dr, &dc);

    for (int k = 0; k < SHIP_SIZE; k++) {
        int rr = row + dr * k;
        int cc = col + dc * k;
        board[rr][cc] = SHIP;
    }
}

/* Funcao util: tenta posicionar um navio e retorna sucesso/fracasso */
static bool try_place_ship(int board[BOARD_SIZE][BOARD_SIZE], Ship s) {
    if (!can_place_ship(board, s.row, s.col, s.orient)) {
        return false;
    }
    place_ship(board, s.row, s.col, s.orient);
    return true;
}

int main(void) {
    int board[BOARD_SIZE][BOARD_SIZE];
    init_board(board);

    /* ===============================
     *  COORDENADAS FIXAS DOS 4 NAVIOS
     *  - Tamanho de cada navio = 3
     * =============================== */

    // 1) Horizontal (para a direita) a partir de (1,2): (1,2), (1,3), (1,4)
    Ship ship_H   = { .row = 1, .col = 2, .orient = ORIENT_H };

    // 2) Vertical (para baixo) a partir de (4,6): (4,6), (5,6), (6,6)
    Ship ship_V   = { .row = 4, .col = 6, .orient = ORIENT_V };

    // 3) Diagonal ↘ a partir de (0,0): (0,0), (1,1), (2,2)
    Ship ship_DDR = { .row = 0, .col = 0, .orient = ORIENT_DDR };

    // 4) Diagonal ↙ a partir de (0,9): (0,9), (1,8), (2,7)
    Ship ship_DDL = { .row = 0, .col = 9, .orient = ORIENT_DDL };

    /* Tentativa de posicionamento com validacao */
    if (!try_place_ship(board, ship_H)) {
        printf("ERRO: nao foi possivel posicionar o navio horizontal.\n");
        return 1;
    }
    if (!try_place_ship(board, ship_V)) {
        printf("ERRO: nao foi possivel posicionar o navio vertical.\n");
        return 1;
    }
    if (!try_place_ship(board, ship_DDR)) {
        printf("ERRO: nao foi possivel posicionar o navio diagonal ↘.\n");
        return 1;
    }
    if (!try_place_ship(board, ship_DDL)) {
        printf("ERRO: nao foi possivel posicionar o navio diagonal ↙.\n");
        return 1;
    }

    /* Impressao do resultado */
    printf("TABULEIRO 10x10 (0 = agua, 3 = navio):\n");
    print_board(board);

    return 0;
}