#include "board.h"

void init_board(Board* board) {
    // Allocate memory for the 2D array
    board->board = (bool**)malloc(board->height * sizeof(bool*));
    for(int i = 0; i < board->height; i++) {
        board->board[i] = (bool*)malloc(board->width * sizeof(bool));
    }

    // Initialize the board to all false
    for(int i = 0; i < board->height; i++) {
        for(int j = 0; j < board->width; j++) {
            board->board[i][j] = false;
        }
    }
}

void free_board(Board* board) {
    if (board->board != NULL) {
        for (int i = 0; i < board->height; i++) {
            free(board->board[i]);
        }
        free(board->board);
    }
}


void print_board(Board* board) {
    for(int i = 0; i < board->height; i++) {  // Loop over height for rows
        for(int j = 0; j < board->width; j++) {  // Loop over width for columns
            printf("%d", board->board[i][j]);
        }
        printf("\n");
    }
}