cmake_minimum_required(VERSION 3.3)
project(Maze_Generator_Port)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Maze.cpp Maze.h Maze.cpp Maze.h)
add_executable(Maze_Generator_Port ${SOURCE_FILES})