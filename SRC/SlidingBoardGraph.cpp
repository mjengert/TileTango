#include "SlidingBoardGraph.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

// Get a board from the file and insert it into the graph; will need to keep track of what board has already been used
void SlidingBoardGraph::GetBoardFromFile(string filename) {
    // Open the file and check if it was opened successfully
    ifstream dataFile;
    dataFile.open(filename);
    if (!dataFile) {
        cout << "Error opening file" << endl;
        return;
    }
    // Read the file line by line to get the board data
    string line;
    vector<int> board;
    // Skip the boards that have already been used; each board occupies 16 lines
    for (int i = 0; i < usedBoards.size() * 16; i++) {
        getline(dataFile, line);
    }
    // Get the next board; each board occupies 16 lines
    // A blank line separates the boards in the file
    while (getline(dataFile, line)) {
        if (line.empty()) {
            break;
        }
        board.push_back(stoi(line));

    }
    // Create a new board and insert it into the graph; also add it to the usedBoards vector to keep track of it
    SlidingBoard* newBoard = new SlidingBoard(board);
    // Clear past board data
    if (root != nullptr) {
        DeleteGraph(root);
    }
    InsertBoard(newBoard);
    usedBoards.push_back(newBoard);
}

// Insert a board into the graph
void SlidingBoardGraph::InsertBoard(SlidingBoard* board) {
    // If the root is empty, insert the board as the root
    if (root == nullptr) {
        root = board;
        GetAllMoves(board);
    }
}

// Get the possible moves for a board; will be called recursively to get all possible moves till the solution is found
void SlidingBoardGraph::GetAllMoves(SlidingBoard* board) {
    // Get the row and column of the blank tile
    int row = board->blankRow;
    int col = board->blankCol;
    // Check if a tile can move down into the blank space
    if (row > 0) {
        CreateMove(board, row + 1, col);
    }
    // Check if a tile can move up into blank space
    if (row < 3) {
        CreateMove(board, row - 1, col);
    }
    // Check if a tile can move right into blank space
    if (col > 0) {
        CreateMove(board, row, col - 1);
    }
    // Check if a tile can move left into blank space
    if (col < 3) {
        CreateMove(board, row, col + 1);
    }
}

// Create a move for a board
void SlidingBoardGraph::CreateMove(SlidingBoard* board, int row, int col) {
    if (board == nullptr) {
        return;
    }
    // Create a new board with the move
    int newBoard[4][4];
    // Copy the board into the new board
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            newBoard[i][j] = board->Board[i][j];
        }
    }
    // Swap the blank tile with the tile to be moved
    newBoard[board->blankRow][board->blankCol] = newBoard[row][col];
    newBoard[row][col] = 16;
    // Create a new board
    SlidingBoard* newBoardObj = new SlidingBoard(newBoard);
    // Set the parent of the new board to the current board
    newBoardObj->parent = board;
    bool solution = IsSolution(newBoardObj);
    // If the new board is the solution, stop the search
    if (solution) {
        cout << "Solution found" << endl;
    }
    else {
        GetAllMoves(newBoardObj);
    }
}

// Get the heuristic for a board
int SlidingBoardGraph::GetHeuristic(SlidingBoard *board) {
    return 0;
}


// Print the board; will be used for debugging
void SlidingBoardGraph::PrintBoard() {
    cout << "Printing board" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << root->Board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Delete the graph
void SlidingBoardGraph::DeleteGraph(SlidingBoard *board) {

}

bool SlidingBoardGraph::IsSolution(SlidingBoard *board) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board->Board[i][j] != Solution[i][j]) {
                return false;
            }
        }
    }
    return true;
}
