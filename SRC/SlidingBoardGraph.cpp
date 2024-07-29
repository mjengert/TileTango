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
    // Check if the blank tile is in the top right corner of the board
    if (board->blankRow == 0 && board->blankCol == 0) {
        CreateMove(board, board->blankRow + 1, board->blankCol);
    }
    // Check if the blank tile is in the top left corner of the board
    else if (board->blankRow == 0 && board->blankCol == 3) {
        CreateMove(board, board->blankRow, board->blankCol - 1);
    }
    // Check if the blank tile is in the bottom right corner of the board
    else if (board->blankRow == 3 && board->blankCol == 0) {
        CreateMove(board, board->blankRow - 1, board->blankCol);
    }
    // Check if the blank tile is in the bottom left corner of the board
    else if (board->blankRow == 3 && board->blankCol == 3) {
        CreateMove(board, board->blankRow, board->blankCol + 1);
    }
    // Check if the blank tile is in the top row of the board
    else if (board->blankRow == 0) {
        CreateMove(board, board->blankRow, board->blankCol - 1);
        CreateMove(board, board->blankRow, board->blankCol + 1);
        CreateMove(board, board->blankRow + 1, board->blankCol);
    }
    // Check if the blank tile is in the bottom row of the board
    else if (board->blankRow == 3) {
        CreateMove(board, board->blankRow, board->blankCol - 1);
        CreateMove(board, board->blankRow, board->blankCol + 1);
        CreateMove(board, board->blankRow - 1, board->blankCol);
    }
    // Check if the blank tile is in the left column of the board
    else if (board->blankCol == 0) {
        CreateMove(board, board->blankRow - 1, board->blankCol);
        CreateMove(board, board->blankRow + 1, board->blankCol);
        CreateMove(board, board->blankRow, board->blankCol + 1);
    }
    // Check if the blank tile is in the right column of the board
    else if (board->blankCol == 3) {
        CreateMove(board, board->blankRow - 1, board->blankCol);
        CreateMove(board, board->blankRow + 1, board->blankCol);
        CreateMove(board, board->blankRow, board->blankCol - 1);
    }
    // If the blank tile is in the middle of the board
    else {
        CreateMove(board, board->blankRow - 1, board->blankCol);
        CreateMove(board, board->blankRow + 1, board->blankCol);
        CreateMove(board, board->blankRow, board->blankCol - 1);
        CreateMove(board, board->blankRow, board->blankCol + 1);
    }
    bool SolutionFound = false;
    // Check if the solution has been found
    for (int i = 0; i < board->children.size(); i++) {
        if (IsSolution(board->children[i])) {
            SolutionFound = true;
            break;
        }
    }
    // If the solution has not been found, recursively call GetAllMoves on the children
    if (!SolutionFound) {
        for (int i = 0; i < board->children.size(); i++) {
            GetAllMoves(board->children[i]);
        }
    }
    else{
        cout << "Solution found" << endl;
    }
}

// Create a move for a board
void SlidingBoardGraph::CreateMove(SlidingBoard* board, int row, int col) {
    // Create a new board with the move
    int newBoard[4][4];
    // Copy the board into the new board
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            newBoard[i][j] = board->Board[i][j];
        }
    }
    // Swap the blank tile with the tile to be moved
    swap(newBoard[board->blankRow][board->blankCol], newBoard[row][col]);
    // Check if the new board is the same as the parent board
    if (board->parent != nullptr) {
        bool same = true;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (newBoard[i][j] != board->parent->Board[i][j]) {
                    same = false;
                    break;
                }
            }
        }
        if (same) {
            return;
        }
    }
    // Create a new board
    auto* newBoardObj = new SlidingBoard(newBoard);
    // Set the parent of the new board to the current board and update children of the current board
    newBoardObj->parent = board;
    board->children.push_back(newBoardObj);
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
    // Recursively delete the children of the board
    for (int i = 0; i < board->children.size(); i++) {
        DeleteGraph(board->children[i]);
    }
    // Delete the board
    delete board;
}

// Check if a board is the solution
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
