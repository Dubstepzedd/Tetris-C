#include <stdio.h>
#include <stdbool.h>
#include "board.h"
#include <time.h>

#define TETROMINO_SIZE 5 // Each tetromino is a 5x5 block (symmetric) - 1 extra for padding
#define TETROMINO_MOVING 2
#define TETROMINO_PLACED 1

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

typedef struct Point {
    int x,y;
} Point;


typedef struct {
    TetrominoType type;
    int x, y; 
    int** shape;
} Tetromino;


const int (*get_tetromino_shape(TetrominoType type))[TETROMINO_SIZE];

Tetromino create_tetromino(TetrominoType type);

void clear_board(Board* board);

void add_tetromino(Board* board, Tetromino* tetromino, int type);

Tetromino get_random_tetromino();

void free_tetromino(Tetromino* tetromino);

bool is_colliding(Board* board, Tetromino* tetromino, int x_diff, int y_diff);

void rotate_tetromino(Board* board, Tetromino* tetromino);