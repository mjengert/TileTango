#include "SlidingBoardGraph.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

// get a board from the file and insert it into the graph; will need to keep track of what board has already been used
void SlidingBoardGraph::GetBoardFromFile(string filename) {
    // open the file and check if it was opened successfully
    ifstream dataFile;
    dataFile.open(filename);
    if (!dataFile) {
        cout << "Error opening file" << endl;
        return;
    }
    // read the file line by line to get the board data
    string line;
    vector<int> board;
    // skip the boards that have already been used; each board occupies 9 lines
    for (int i = 0; i < usedBoards.size() * 10; i++) {
        getline(dataFile, line);
    }
    // get the next board; each board occupies 16 lines
    // a blank line separates the boards in the file
    while (getline(dataFile, line)) {
        if (line.empty()) {
            break;
        }
        board.push_back(stoi(line));

    }
    // create a new board and insert it into the graph; also add it to the usedBoards vector to keep track of it
    SlidingBoard* newBoard = new SlidingBoard(board);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << newBoard->Board[i][j] << " ";
        }
        cout << endl;
    }
    // clear past board data
    if (root != nullptr) {
        DeleteGraph(root);
    }
    root = newBoard;
    usedBoards.push_back(newBoard);
}

// get the possible moves for a board; will be called recursively to get all possible moves till the solution is found
void SlidingBoardGraph::GetAllMoves(SlidingBoard* board, int depth) {
    if (board == nullptr) {
        return;
    }
    // check if the blank tile is in the top right corner of the board
    if (board->blankRow == 0 && board->blankCol == 0) {
        CreateMove(board, board->blankRow + 1, board->blankCol);
        CreateMove(board, board->blankRow, board->blankCol + 1);

    }
    else if (board->blankRow == 0 && board->blankCol == 1) {
        CreateMove(board, board->blankRow + 1, board->blankCol);
        CreateMove(board, board->blankRow, board->blankCol - 1);
        CreateMove(board, board->blankRow, board->blankCol + 1);
    }
    else if (board->blankRow == 0 && board->blankCol == 2) {
        CreateMove(board, board->blankRow + 1, board->blankCol);
        CreateMove(board, board->blankRow, board->blankCol - 1);
    }
    else if (board->blankRow == 1 && board->blankCol == 0) {
        CreateMove(board, board->blankRow + 1, board->blankCol);
        CreateMove(board, board->blankRow - 1, board->blankCol);
        CreateMove(board, board->blankRow, board->blankCol + 1);
    }
    else if (board->blankRow == 1 && board->blankCol == 1) {
        CreateMove(board, board->blankRow + 1, board->blankCol);
        CreateMove(board, board->blankRow - 1, board->blankCol);
        CreateMove(board, board->blankRow, board->blankCol + 1);
        CreateMove(board, board->blankRow, board->blankCol - 1);
    }
    else if (board->blankRow == 1 && board->blankCol == 2) {
        CreateMove(board, board->blankRow + 1, board->blankCol);
        CreateMove(board, board->blankRow - 1, board->blankCol);
        CreateMove(board, board->blankRow, board->blankCol - 1);
    }
    else if (board->blankRow == 2 && board->blankCol == 0) {
        CreateMove(board, board->blankRow - 1, board->blankCol);
        CreateMove(board, board->blankRow, board->blankCol + 1);
    }
    else if (board->blankRow == 2 && board->blankCol == 1) {
        CreateMove(board, board->blankRow - 1, board->blankCol);
        CreateMove(board, board->blankRow, board->blankCol + 1);
        CreateMove(board, board->blankRow, board->blankCol - 1);
    }
    else if (board->blankRow == 2 && board->blankCol == 2) {
        CreateMove(board, board->blankRow - 1, board->blankCol);
        CreateMove(board, board->blankRow, board->blankCol - 1);
    }
    bool SolutionFound = false;
    // check if the solution has been found
    for (int i = 0; i < board->children.size(); i++) {
        if (IsSolution(board->children[i])) {
            SolutionFound = true;
            break;
        }
    }
    // if the solution has not been found, recursively call GetAllMoves on the children
    if (!SolutionFound) {
        for (int i = 0; i < board->children.size(); i++) {
            GetAllMoves(board->children[i], depth + 1);
        }
    }
    else{
        cout << "Solution found" << endl;
        cout << "Depth: " << depth << endl;
    }
}

// create a move for a board
void SlidingBoardGraph::CreateMove(SlidingBoard* board, int row, int col) {
    // create a new board with the move
    int newBoard[3][3];
    // copy the board into the new board
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            newBoard[i][j] = board->Board[i][j];
        }
    }
    // swap the blank tile with the tile to be moved
    swap(newBoard[board->blankRow][board->blankCol], newBoard[row][col]);
    // check if the new board is the same as the parent board or if it is already in gameStates
    bool boardExists = false;
    for (int i = 0; i < gameStates.size(); i++) {
        bool sameBoard = true;
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (gameStates[i]->Board[j][k] != newBoard[j][k]) {
                    sameBoard = false;
                    break;
                }
            }
            if (!sameBoard) {
                break;
            }
        }
        if (sameBoard) {
            boardExists = true;
            break;
        }
    }
    if (boardExists) {
        return;
    }
    // create a new board object and add it to the gameStates vector
    auto* newBoardObj = new SlidingBoard(newBoard);
    gameStates.push_back(newBoardObj);
    // set the parent of the new board to the current board and update children of the current board
    newBoardObj->parent = board;
    board->children.push_back(newBoardObj);
}
// check if a board is the solution
bool SlidingBoardGraph::IsSolution(SlidingBoard *board) {
    if (board == nullptr) {
        cout << "IsSolution: Board is null" << endl;
        return false;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board->Board[i][j] != Solution[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// use the IDA* algorithm to solve the puzzle
void SlidingBoardGraph::IDAStar(SlidingBoard *board) {
    // initialize the threshold to the heuristic of the board
    SlidingBoard* current = board;
    int threshold = current->heuristic;
    // DFS with a threshold


}

// use the BFS algorithm to solve the puzzle
void SlidingBoardGraph::BFS(SlidingBoard *board) {
    // implement BFS algorithm
}

// get the fastest time to the solution
double SlidingBoardGraph::GetFastestPath() {
    if (BFSTime < IDAStarTime) {
        return BFSTime;
    }
    return IDAStarTime;
}

// sets the heuristic for a board
int SlidingBoard::SetFScore(SlidingBoard *board) {
    // calculate the heuristic for the board
    int totalCost = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int tile = board->Board[i][j];
            if (tile == 9) {
                continue;
            }
            int row = (tile - 1) / 3;
            int col = (tile - 1) % 3;
            int estimatedCost = abs(row - i) + abs(col - j);
            totalCost += estimatedCost;
        }
    }
    return totalCost;
}

// print the board; will be used for debugging
void SlidingBoardGraph::PrintBoard() {
    cout << "Printing board" << endl;
    for (auto & i : root->Board) {
        for (int j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// delete the graph
void SlidingBoardGraph::DeleteGraph(SlidingBoard *board) {
    if (board == nullptr) {
        return;
    }
    for (int i = 0; i < board->children.size(); i++) {
        DeleteGraph(board->children[i]);
    }
    delete board;
}
