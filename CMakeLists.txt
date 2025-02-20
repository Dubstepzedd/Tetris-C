cmake_minimum_required(VERSION 3.10)
project(Tetris C)

set(CMAKE_C_STANDARD 11)

# Detect platform and set threading library
if(WIN32)
    message(STATUS "Compiling for Windows - Using Win32 Threads")
    add_compile_definitions(USE_WIN32_THREADS) 
    set(THREADS_LIB "") 
else()
    message(STATUS "Compiling for UNIX - Using Pthreads")
    find_package(Threads REQUIRED)
    set(THREADS_LIB Threads::Threads)  # Link against pthreads on UNIX
endif()

file(GLOB SOURCES "src/*.c")
file(GLOB HEADERS "src/*.h")

# Create the executable
add_executable(Tetris ${SOURCES} ${HEADERS})

# Link the appropriate threading library
target_link_libraries(Tetris PRIVATE ${THREADS_LIB})
