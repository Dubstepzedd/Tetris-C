#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Board {
    int width;
    int height;
    int** board;

} Board;

void init_board(Board* board);

void print_board(Board* board);

void free_board(Board* board);

#endif