#include <stdio.h>

typedef enum {
    TETROMINO_I,
    TETROMINO_O,
    TETROMINO_T,
    TETROMINO_L,
    TETROMINO_J,
    TETROMINO_S,
    TETROMINO_Z,
    TETROMINO_COUNT // Number of tetromino types
} TetrominoType;

#define TETROMINO_SIZE 4 // Each tetromino is a 4x4 block

typedef struct {
    TetrominoType type;
    int x, y;      // Position on the board
    int shape[TETROMINO_SIZE][TETROMINO_SIZE]; // 4x4 matrix representing the shape
} Tetromino;

const int (*getTerominoShape(TetrominoType type))[TETROMINO_SIZE];

void printTetromino(Tetromino* tetromino);
