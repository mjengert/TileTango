cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(TileTango)

if (APPLE)
    set(SFML_DIR "/SFML-2.6.1-Mac/lib/cmake/SFML")
elseif (WIN32)
    set(SFML_DIR "/SFML-2.6.1-Windows/lib/cmake/SFML")
endif ()

find_package(SFML 2.6.1 COMPONENTS system window graphics audio REQUIRED)
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