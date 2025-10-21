#include <stdio.h>

#define BOARD_SIZE 10
#define SHIP_SIZE  3
#define WATER      0
#define SHIP       3

void init_board(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = WATER;
        }
    }
}

void print_board(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int board[BOARD_SIZE][BOARD_SIZE];
    init_board(board);

    // Coordenadas fixas para os navios
    int rowH = 2, colH = 4; // Navio horizontal
    int rowV = 5, colV = 1; // Navio vertical

    // Posiciona navio horizontal (3 posições)
    for (int i = 0; i < SHIP_SIZE; i++) {
        board[rowH][colH + i] = SHIP;
    }

    // Posiciona navio vertical (3 posições)
    for (int i = 0; i < SHIP_SIZE; i++) {
        board[rowV + i][colV] = SHIP;
    }

    // Exibe o tabuleiro
    printf("Tabuleiro com navios posicionados:\n");
    print_board(board);

    return 0;
}
