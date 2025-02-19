#include <stdio.h>
#include "board.h"
#include <time.h>
#include "tetromino.h"

#define UPDATE_THRESHHOLD 1


void do_logic(Board* board) {
    for(int i = 0; i < board->width; i++) {
        board->board[0][i] = !board->board[0][i];
    }
}

int main() {
    Board board;
    board.width = 10;
    board.height = 20;
    init_board(&board);

    
    double elapsedTime = 0;
    double timeDiff = 0;
    double start = clock();
    double end = 0;

    while(true) {
        end = clock();
        timeDiff = (end - start) / CLOCKS_PER_SEC;
        start = end;

        elapsedTime += timeDiff;

        if (elapsedTime >= UPDATE_THRESHHOLD) {
            do_logic(&board);
            #ifdef _WIN32
                system("cls");  // For Windows
            #else
                system("clear");  // For Unix/Linux/Mac
            #endif
            print_board(board);
            elapsedTime = 0;
        }
    }

    free_board(board);
    return 0;
}
