#include "SlidingBoardGraph.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

// Get a board from the file and insert it into the graph; will need to keep track of what board has already been used
void SlidingBoardGraph::GetBoardFromFile(string filename) {

}

// Insert a board into the graph
void SlidingBoardGraph::InsertBoard(SlidingBoard* board) {

}

// Get the possible moves for a board; will be called recursively to get all possible moves till the solution is found
void SlidingBoardGraph::GetMoves(SlidingBoard* board) {

}

// Get the heuristic for a board
int SlidingBoardGraph::GetHeuristic(SlidingBoard *board) {
    return 0;
}

// Get the difficulty for a board
int SlidingBoardGraph::GetDifficulty(SlidingBoard *board) {
    return 0;
}

// Print the board; will be used for debugging
void SlidingBoardGraph::PrintBoard() {

}

// Delete the graph
void SlidingBoardGraph::DeleteGraph(SlidingBoard *board) {

}
