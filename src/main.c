#include <stdio.h>
#include "board.h"
#include <time.h>
#include "tetromino.h"
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h> 
#else
    #include <pthread.h>
    #include <unistd.h>
    #include <ncurses.h>
#endif

#define RENDER_THRESHOLD 0.1
#define MOVE_DOWN_THRESHOLD 0.7

volatile char last_char = '\0'; // Volatile ensures proper multi-threading handling

#ifdef _WIN32
DWORD WINAPI thread_function(LPVOID lpParam) {
    while (1) {
        if (_kbhit()) { 
            last_char = (char)_getch(); 
        }

        Sleep(10); 
    }
    return 0;
}

#else



void* thread_function(void* arg) {

    while (1) {
        int ch = getch(); 
        if (ch != ERR) {
            last_char = (char)ch; // Store the character
        }
        
        usleep(10000); 
    }
}
#endif

void process_input(Board* board, Tetromino* tetromino) {
    switch (last_char) {
        case 'a': // Move left
            if (!is_colliding(board, tetromino, -1, 0))
                tetromino->x--;
            break;
        case 'd': // Move right
            if (!is_colliding(board, tetromino, 1, 0))
                tetromino->x++;
            break;
        case 'r': // Rotate
            rotate_tetromino(board, tetromino);
            break;
        case 's': // Speed down
            if (!is_colliding(board, tetromino, 0, 1))
                tetromino->y++;
            break;
        case 'q': // Quit game
            exit(0);
    }
    last_char = '\0'; // Reset input after processing
}

int main() {
    #ifndef _WIN32
        initscr(); // Initialize the ncurses screen for Unix
        timeout(0);           // Non-blocking input (timeout 0)
        cbreak();             // Disable line buffering
        noecho();             // Don't echo input
        keypad(stdscr, TRUE); // Enable special keys
    #endif

    Board board;
    board.width = 10;
    board.height = 20;
    init_board(&board);
    Tetromino tetromino = get_random_tetromino();
    
#ifdef _WIN32
    HANDLE thread = CreateThread(NULL, 0, thread_function, NULL, 0, NULL);
#else
    pthread_t thread;
    pthread_create(&thread, NULL, thread_function, NULL);
#endif

    double render_elapsed = 0;
    double move_down_elapsed = 0;
    clock_t start_time = clock();

    while (1) {
        // Calculate delta time
        clock_t current_time = clock();
        double delta_time = (double)(current_time - start_time) / CLOCKS_PER_SEC;
        start_time = current_time;

        render_elapsed += delta_time;
        move_down_elapsed += delta_time;

        // Process user input asynchronously
        process_input(&board, &tetromino);

        // Render board at set intervals
        if (render_elapsed >= RENDER_THRESHOLD) {
            clear_board(&board);
           
            add_tetromino(&board, &tetromino, TETROMINO_MOVING);
            print_board(&board);
            render_elapsed = 0;
        }

        if (move_down_elapsed >= MOVE_DOWN_THRESHOLD) {
            if (!is_colliding(&board, &tetromino, 0, 1))
                tetromino.y++;
            else {
                add_tetromino(&board, &tetromino, TETROMINO_PLACED);
                free_tetromino(&tetromino);
                check_line_clears(&board);
                tetromino = get_random_tetromino();

                if (is_colliding(&board, &tetromino, 0, 0)) {
                    printf("Game Over!\n");
                    free_tetromino(&tetromino);
                    break;  // Exit the loop (end the game)
                }
            }

            move_down_elapsed = 0;
        }
    }

    // Cleanup (won't execute due to infinite loop, but good practice)
    free_board(&board);
    #ifndef _WIN32
        endwin(); // End the ncurses screen
    #endif
#ifdef _WIN32
    CloseHandle(thread);
#else
    pthread_cancel(thread);
    pthread_join(thread, NULL);
#endif

    return 0;
}
