#include <stdio.h>
#include <stdbool.h>
#include "board.h"

typedef enum {
    TETROMINO_I,
    TETROMINO_O,
    TETROMINO_T,
    TETROMINO_L,
    TETROMINO_J,
    TETROMINO_S,
    TETROMINO_Z,
    TETROMINO_COUNT
} TetrominoType;

#define TETROMINO_SIZE 4 // Each tetromino is a 4x4 block (symmetric)

typedef struct {
    TetrominoType type;
    int x, y; 
    int prev_x, prev_y; 
    const int (*shape)[TETROMINO_SIZE];
} Tetromino;

const int TETROMINO_SHAPES[TETROMINO_COUNT][TETROMINO_SIZE][TETROMINO_SIZE];

const int (*get_tetromino_shape(TetrominoType type))[TETROMINO_SIZE];

Tetromino create_tetromino(TetrominoType type);

void add_tetromino(Board* board, Tetromino* tetromino);

bool is_inside_board(Board* board, Tetromino* tetromino, int x_diff, int y_diff);