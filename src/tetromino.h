#include <stdio.h>

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
    int x, y;      // Position on the board
    const int (*shape)[TETROMINO_SIZE];
} Tetromino;

const int (*getTetrominoShape(TetrominoType type))[TETROMINO_SIZE];

void printTetromino(Tetromino* tetromino);
