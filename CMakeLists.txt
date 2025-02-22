cmake_minimum_required(VERSION 3.10)
project(Tetris C)

set(CMAKE_C_STANDARD 11)

# Check the platform
if(WIN32)
    message(STATUS "Compiling for Windows - Using Win32 Threads")
    set(THREADS_LIB "")  # No need to link against Threads on Windows
    # Windows-specific configuration: use conio.h or Windows API (no Curses)
else()
    message(STATUS "Compiling for UNIX - Using Pthreads")
    find_package(Threads REQUIRED)
    set(THREADS_LIB Threads::Threads)  # Link against pthreads on UNIX
    find_package(Curses REQUIRED)     # Find the Curses package for UNIX
    include_directories(${CURSES_INCLUDE_DIRS})  # Add the include directories for Curses
endif()

file(GLOB SOURCES "src/*.c")
file(GLOB HEADERS "src/*.h")

# Create the executable
add_executable(Tetris ${SOURCES} ${HEADERS})

# Link the appropriate libraries
if(WIN32)
    # On Windows, link against the necessary threading libraries (if needed)
    target_link_libraries(Tetris PRIVATE ${THREADS_LIB})
else()
    # On UNIX, link against Pthreads and Curses
    target_link_libraries(Tetris PRIVATE ${THREADS_LIB} ${CURSES_LIBRARIES})
endif()
