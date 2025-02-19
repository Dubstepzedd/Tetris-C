cmake_minimum_required(VERSION 3.10)
project(Tetris C)

set(CMAKE_C_STANDARD 11)
file(GLOB SOURCES "src/*.c")

file(GLOB HEADERS "src/*.h")

# Create the executable
add_executable(Tetris ${SOURCES} ${HEADERS})
