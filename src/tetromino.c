#include "tetromino.h"

const int TETROMINO_SHAPES[TETROMINO_COUNT][TETROMINO_SIZE][TETROMINO_SIZE] = {
    // I
    {
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // O
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // T
    {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // L
    {
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // J
    {
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // S
    {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // Z
    {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }
};


const int (*get_tetromino_shape(TetrominoType type))[TETROMINO_SIZE] {
    return TETROMINO_SHAPES[type];
}

Tetromino create_tetromino(TetrominoType type) {
    Tetromino tetromino;
    tetromino.type = type;
    tetromino.x = 0;
    tetromino.y = 0;
    tetromino.prev_x = -1;
    tetromino.prev_y = -1;
    tetromino.shape = get_tetromino_shape(tetromino.type);
    return tetromino;
}

void remove_tetromino(Board* board, Tetromino tetromino) {
    // You could clear the entire board instead of doing this but it isn't optimal due to the tetromino becoming solid after collision. 
    for (int row = 0; row < TETROMINO_SIZE; row++) {
        for (int col = 0; col < TETROMINO_SIZE; col++) {
            if (tetromino.shape[row][col] == 1) {
                board->board[tetromino.prev_y + row][tetromino.prev_x + col] = 0;
            }
        }
    }
}

bool is_inside_board(Board* board, Tetromino* tetromino, int x_diff, int y_diff) {
    for (int row = 0; row < TETROMINO_SIZE; row++) {
        for (int col = 0; col < TETROMINO_SIZE; col++) {
            if (tetromino->shape[row][col] == 1) {
                if (tetromino->x + col + x_diff >= board->width || tetromino->x + col + x_diff < 0 || tetromino->y + row + y_diff >= board->height) {
                    return false;
                }
            }
        }
    }

    return true;
}

void add_tetromino(Board* board, Tetromino* tetromino) {
    // Remove the previous tetromino
    if (tetromino->prev_x != -1 && tetromino->prev_y != -1) {
        remove_tetromino(board, *tetromino);
    }

    tetromino->prev_x = tetromino->x;
    tetromino->prev_y = tetromino->y;

    for (int row = 0; row < TETROMINO_SIZE; row++) {
        for (int col = 0; col < TETROMINO_SIZE; col++) {
            if (tetromino->shape[row][col] == 1) {
                board->board[tetromino->y + row][tetromino->x + col] = 2;
            }
        }
    }
}