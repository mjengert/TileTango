cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(TileTango)


set(SFML_DIR "C:/Users/Owner/CLionProjects/TileTango/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)
add_executable(TileTango
        SRC/main.cpp
        SRC/SlidingBoards.h
        SRC/SlidingBoardsGen.h
        SRC/SlidingBoardsGen.cpp
        SRC/SlidingBoardGraph.h
        SRC/SlidingBoardGraph.cpp
        SRC/IDA.h
        SRC/BFS.h
        SRC/IDA.cpp
        SRC/BFS.cpp)
target_link_libraries(TileTango sfml-system sfml-window sfml-graphics sfml-audio)