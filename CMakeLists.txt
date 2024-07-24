cmake_minimum_required(VERSION 3.28)
project(TileTango)

set(CMAKE_CXX_STANDARD 14)

include_directories(SRC)
include_directories(DATA)

add_executable(TileTango
        SRC/main.cpp
        SRC/SlidingBoardsGen.h
        SRC/IDA.h
        SRC/BFS.h
        SRC/SlidingBoardsGen.cpp
        SRC/IDA.cpp
        SRC/BFS.cpp
        SRC/SlidingBoardGraph.h
        SRC/SlidingBoardGraph.cpp
)

find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(TileTango sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

