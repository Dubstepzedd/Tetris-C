#include "tetromino.h"

const int TETROMINO_SHAPES[TETROMINO_COUNT][TETROMINO_SIZE][TETROMINO_SIZE] = {
    // I
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    },
    // O
    {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    },
    // T
    {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    },
    // L
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    },
    // J
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    },
    // S
    {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    },
    // Z
    {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    }
};

// Coordiantes of the rotation point for each Tetromino
const Point TETROMINO_ROTATION_POINTS[TETROMINO_COUNT] = {
    {2, 2}, // I 
    {2, 2}, // O 
    {2, 1}, // T 
    {2, 1}, // L 
    {2, 1}, // J 
    {2, 1}, // S 
    {2, 1}  // Z 
};

const int (*get_tetromino_shape(TetrominoType type))[TETROMINO_SIZE] {
    return TETROMINO_SHAPES[type];
}

Tetromino get_random_tetromino() {
    srand(time(NULL)); // Seed the random number generator with the current time (had issues with the seed)
    return create_tetromino(rand() % TETROMINO_COUNT);
}

void free_tetromino(Tetromino* tetromino) {
    for (int i = 0; i < TETROMINO_SIZE; i++) {
        free(tetromino->shape[i]);
    }
    free(tetromino->shape);
}

Tetromino create_tetromino(TetrominoType type) {
    Tetromino tetromino;
    tetromino.type = type;
    tetromino.x = 0;
    tetromino.y = 0;
    tetromino.shape = (int**)malloc(sizeof(int*) * TETROMINO_SIZE);

    for (int i = 0; i < TETROMINO_SIZE; i++) {
        tetromino.shape[i] = (int*)malloc(sizeof(int) * TETROMINO_SIZE);
    }

    // Copy the shape from the constant array
    const int (*source_shape)[TETROMINO_SIZE] = get_tetromino_shape(type);
    for (int row = 0; row < TETROMINO_SIZE; row++) {
        for (int col = 0; col < TETROMINO_SIZE; col++) {
            int val = source_shape[row][col];
            tetromino.shape[row][col] = val;
        }
    }

    return tetromino;
}


bool is_colliding(Board* board, Tetromino* tetromino, int x_diff, int y_diff) {
    for (int row = 0; row < TETROMINO_SIZE; row++) {
        for (int col = 0; col < TETROMINO_SIZE; col++) {
            if (tetromino->shape[row][col] == 1) {

                // Calculate new position for the block
                int new_x = tetromino->x + col + x_diff;
                int new_y = tetromino->y + row + y_diff;

                // Check if the block is out of bounds or colliding with filled cells
                if (new_x < 0 || new_x >= board->width || new_y < 0 || new_y >= board->height) {
                    return true;
                }

                // Check if the block collides with an already placed block (value 2)
                if (board->board[new_y][new_x] == 1) {
                    return true;
                }             
            }
        }
    }
    return false;
}


void add_tetromino(Board* board, Tetromino* tetromino, int type) {
    for (int row = 0; row < TETROMINO_SIZE; row++) {
        for (int col = 0; col < TETROMINO_SIZE; col++) {
            if (tetromino->shape[row][col] == 1) {
                board->board[tetromino->y + row][tetromino->x + col] = type;
            }
        }
    }
}

void rotate_tetromino(Board* board, Tetromino* tetromino) {
    int new_shape[TETROMINO_SIZE][TETROMINO_SIZE];
    int old_shape[TETROMINO_SIZE][TETROMINO_SIZE];

    // Copy the current shape to old_shape
    for (int row = 0; row < TETROMINO_SIZE; row++) {
        for (int col = 0; col < TETROMINO_SIZE; col++) {
            old_shape[row][col] = tetromino->shape[row][col];
        }
    }

    Point rotation_point = TETROMINO_ROTATION_POINTS[tetromino->type]; // x and y of the rotation point

    // Rotate around the rotation_point
    for (int row = 0; row < TETROMINO_SIZE; row++) {
        for (int col = 0; col < TETROMINO_SIZE; col++) {
                // Get current coordinates relative to the rotation point
                int x = col - rotation_point.x;
                int y = row - rotation_point.y;

                // Apply rotation around the point (rotation of 90 degrees clockwise)
                int new_x = rotation_point.x - y;
                int new_y = rotation_point.y + x;

                // Set the rotated position in the new shape
                if (new_x >= 0 && new_x < TETROMINO_SIZE && new_y >= 0 && new_y < TETROMINO_SIZE) {
                    new_shape[new_y][new_x] = tetromino->shape[row][col];
                }
        }
    }

    for (int row = 0; row < TETROMINO_SIZE; row++) {
        for (int col = 0; col < TETROMINO_SIZE; col++) {
            tetromino->shape[row][col] = new_shape[row][col];
        }
    }

    // Check for collisions after rotation
    if (is_colliding(board, tetromino, 0, 0)) {
        // If collision happens, revert to original shape (no rotation)
        for (int row = 0; row < TETROMINO_SIZE; row++) {
            for (int col = 0; col < TETROMINO_SIZE; col++) {
                tetromino->shape[row][col] = old_shape[row][col];
            }
        }
    } 
}



