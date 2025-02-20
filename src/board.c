#include "board.h"

void init_board(Board* board) {
    // Allocate memory for the 2D array
    board->board = (int**)malloc(board->height * sizeof(int*));
    for(int i = 0; i < board->height; i++) {
        board->board[i] = (int*)malloc(board->width * sizeof(int));
    }

    // Initialize the board to all false
    for(int i = 0; i < board->height; i++) {
        for(int j = 0; j < board->width; j++) {
            board->board[i][j] = 0;
        }
    }
}

// This does not reset the board, it only clears the tetrominos
void clear_board(Board* board) {
    for(int i = 0; i < board->height; i++) {
        for(int j = 0; j < board->width; j++) {
            if (board->board[i][j] == 2) {
                board->board[i][j] = 0;
            }
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
            int val = board->board[i][j];
            if (val == 0) {
                printf(" . ");
            } 
            else {
                printf(" O ");
            }
        }
        printf("\n");
    }
}

void check_line_clears(Board* board) {
    for (int i = 0; i < board->height; i++) {
        bool is_full = true;
        for (int j = 0; j < board->width; j++) {
            if (board->board[i][j] != 1) {
                is_full = false;
                break;
            }
        }

        if (is_full) {
            // Move all rows above down by 1
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < board->width; j++) {
                    board->board[k][j] = board->board[k-1][j];
                }
            }

            // Clear the top row
            for (int j = 0; j < board->width; j++) {
                board->board[0][j] = 0;
            }
        }
    }
}