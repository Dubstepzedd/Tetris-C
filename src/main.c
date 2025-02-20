#include <stdio.h>
#include "board.h"
#include <time.h>
#include "tetromino.h"
#include <conio.h>

#ifdef USE_WIN32_THREADS
    #include <windows.h>
#else
    #include <pthread.h>
#endif

#define RENDER_THRESHOLD 0.16
#define MOVE_DOWN_THRESHOLD 1.0

volatile char last_char = '\0'; // Volatile ensures proper multi-threading handling

#ifdef USE_WIN32_THREADS
DWORD WINAPI thread_function(LPVOID lpParam) {
    while (1) {
        if (_kbhit()) {
            last_char = _getch();
        }
        Sleep(10); // Prevents excessive CPU usage
    }
    return 0;
}
#else
void* thread_function(void* arg) {
    while (1) {
        if (_kbhit()) {
            last_char = _getch();
        }
        usleep(10000); // Sleep for 10ms
    }
    return NULL;
}
#endif

void process_input(Board* board, Tetromino* tetromino) {
    switch (last_char) {
        case 'a': // Move left
            if (is_inside_board(board, tetromino, -1, 0))
                tetromino->x--;
            break;
        case 'd': // Move right
            if (is_inside_board(board, tetromino, 1, 0))
                tetromino->x++;
            break;
        case 's': // Soft drop
            if (is_inside_board(board, tetromino, 0, 1))
                tetromino->y++;
            break;
        case 'q': // Quit game
            exit(0);
    }
    last_char = '\0'; // Reset input after processing
}

int main() {
    Board board;
    board.width = 10;
    board.height = 20;
    init_board(&board);
    Tetromino tetromino = create_tetromino(TETROMINO_I);
    
#ifdef USE_WIN32_THREADS
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

        // Move tetromino down at intervals
        if (move_down_elapsed >= MOVE_DOWN_THRESHOLD) {
            if (is_inside_board(&board, &tetromino, 0, 1))
                tetromino.y++;
            move_down_elapsed = 0;
        }

        // Render board at set intervals
        if (render_elapsed >= RENDER_THRESHOLD) {
            #ifdef _WIN32
                system("cls");  // Windows clear screen
            #else
                system("clear"); // Unix/Linux clear screen
            #endif
            
            add_tetromino(&board, &tetromino);
            print_board(&board);
            render_elapsed = 0;
        }
    }

    // Cleanup (won't execute due to infinite loop, but good practice)
    free_board(&board);

#ifdef USE_WIN32_THREADS
    CloseHandle(thread);
#else
    pthread_cancel(thread);
    pthread_join(thread, NULL);
#endif

    return 0;
}
