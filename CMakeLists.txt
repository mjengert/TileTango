cmake_minimum_required(VERSION 3.28)
project(TileTango)

set(CMAKE_CXX_STANDARD 14)

add_executable(TileTango
        main.cpp
        SlidingBoards.h
        IDA.h
        BFS.h
        SlidingBoards.cpp
        IDA.cpp
        BFS.cpp)

find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(TileTango sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

