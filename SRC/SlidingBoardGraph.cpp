#include "SlidingBoardGraph.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <set>
using namespace std;

// get a board from the file and insert it into the graph; need to keep track of what board has already been used
void SlidingBoardGraph::GetBoardFromFile(const string& filename) {
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
    auto* newBoard = new SlidingBoard(board);
    for (auto & i : newBoard->Board) {
        for (int j : i) {
            cout << j << " ";
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

// get the possible moves for a board; called recursively to get all possible moves till the solution is found
/*
bool SlidingBoardGraph::GetAllMoves(SlidingBoard* board, int depth) {
    if (board == nullptr) {
        return false;
    }
    bool solutionFound = false;
    if (IsSolution(board)) {
        solutionFound = true;
        cout << "Solution found" << endl;
        cout << "Depth: " << depth << endl;
        return solutionFound;
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

    for (int i = 0; i < board->children.size(); i++) {
        if (GetAllMoves(board->children[i], depth + 1)) {
            solutionFound = true;
            break;
        }
    }
    return solutionFound;
}

// create a move for a board
void SlidingBoardGraph::CreateMove(SlidingBoard* board, int row, int col) {
    // copy the board into the new board
    int newBoard[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            newBoard[i][j] = board->Board[i][j];
        }
    }
    // swap the blank tile with the tile to be moved
    swap(newBoard[board->blankRow][board->blankCol], newBoard[row][col]);
    // check if the new board is already in gameStates
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
 */
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
vector<vector<int>> SlidingBoardGraph::IDAStar(SlidingBoard* board, int GScore, int threshold) {
    // HScore is the heuristic score = number of blocks not in the correct position
    // GScore is the number of moves made towards the solution
    // FScore is the sum of GScore and HScore
    int FScore = board->HScore + GScore;
    int newThreshold = threshold;

}

// sets the heuristic for a board
// if a block is not in the correct position, the heuristic is incremented by 1
int SlidingBoard::SetHScore(SlidingBoard *board) {
    int hScore = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board->Board[i][j] != Solution[i][j]) {
                hScore++;
            }
        }
    }
    return hScore;
}

// use the BFS algorithm to solve the puzzle and returns a vector of grid lines representing the path taken
// shortest path from s-t reference: https://www.geeksforgeeks.org/shortest-path-unweighted-graph/
vector<vector<int>> SlidingBoardGraph::BFS(SlidingBoard *board) {
    vector<int> currGrid(9);
    vector<int> tempGrid(9);
    vector<int> solutionGrid = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    set<vector<int>> visitedBoards;
    queue<vector<int>> boardQueue;
    int blankRow;
    int blankCol;


    //Converting the board root inserted into a vector representing a 3x3 board
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            currGrid[i*3 + j] = board->Board[i][j];
        }
    }
    boardQueue.push(currGrid);
    //maps out as key: child grid, value: parent grid
    map<vector<int>, vector<int>> gridParent;
    gridParent[currGrid] = {};

    //looping through each possible blank shift until solution state is reached
    while(!boardQueue.empty()) {
        //Adding the current grid to the set and the queue
        currGrid = boardQueue.front();
        visitedBoards.insert(currGrid);
        boardQueue.pop();

        //Once solution grid is found end loop and create path
        if (currGrid == solutionGrid) {
            break;
        }

        //Find the location of the blank in the grid line
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (currGrid[i * 3 + j] == 9) {
                    blankRow = i;
                    blankCol = j;
                }
            }
        }

        //insert all possible blank shifts and then places it into the queue
        //only if it has not been visited
        //swap up with blank
        if (blankRow > 0){
            tempGrid = currGrid;
            swap(tempGrid[blankRow*3 + blankCol], tempGrid[(blankRow*3 - 3) + blankCol]);
            if (!visitedBoards.count(tempGrid)){
                gridParent.emplace(tempGrid, currGrid);
                boardQueue.push(tempGrid);
                visitedBoards.insert(tempGrid);
            }
        }
        //swap down with blank
        if (blankRow < 2){
            tempGrid = currGrid;
            swap(tempGrid[blankRow*3 + blankCol], tempGrid[(blankRow*3 + 3) + blankCol]);
            if (!visitedBoards.count(tempGrid)){
                gridParent.emplace(tempGrid, currGrid);
                boardQueue.push(tempGrid);
                visitedBoards.insert(tempGrid);
            }
        }
        //swap left with blank
        if (blankCol > 0){
            tempGrid = currGrid;
            swap(tempGrid[blankRow*3 + blankCol], tempGrid[blankRow*3 + (blankCol - 1)]);
            if (!visitedBoards.count(tempGrid)){
                gridParent.emplace(tempGrid, currGrid);
                boardQueue.push(tempGrid);
                visitedBoards.insert(tempGrid);
            }
        }
        //swap right with blank
        if (blankCol < 2){
            tempGrid = currGrid;
            swap(tempGrid[blankRow*3 + blankCol], tempGrid[blankRow*3 + (blankCol + 1)]);
            if (!visitedBoards.count(tempGrid)){
                gridParent.emplace(tempGrid, currGrid);
                boardQueue.push(tempGrid);
                visitedBoards.insert(tempGrid);
            }
        }
    }

    //Assembles path taken by BFS to get to the solution grid
    vector<vector<int>> BoardPath;
    //loops through until no parent is found
    BoardPath.push_back(solutionGrid); //solution is always last child/step
    while(!gridParent[currGrid].empty()){
        BoardPath.insert(BoardPath.begin(), gridParent[currGrid]);
        currGrid = gridParent[currGrid];
    }
    return BoardPath;
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
