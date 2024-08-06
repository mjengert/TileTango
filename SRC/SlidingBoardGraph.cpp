#include "SlidingBoardGraph.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <map>
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
    root = newBoard;
    usedBoards.push_back(newBoard);
}

// use the IDA* algorithm to solve the puzzle
// reference: https://www.geeksforgeeks.org/iterative-deepening-a-algorithm-ida-artificial-intelligence/#
// reference: https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/
vector<vector<int>> SlidingBoardGraph::IDAStar(SlidingBoard* board, int GScore) {
    // create a vector to store the path taken to solve the puzzle and change the board to a vector
    vector<vector<int>> IDAPath;
    vector<int> currGrid(9);
    vector<int> totalBoards = {0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            currGrid[i * 3 + j] = board->Board[i][j];
        }
    }
    // set the threshold to the heuristic score of the board and start the IDA* algorithm
    int threshold = SetHScore(currGrid);
    while (true) {
        // call the helper function to solve the puzzle
        set<vector<int>> visitedBoards;
        int temp = IDAStarHelper(currGrid, GScore, threshold, IDAPath, visitedBoards, totalBoards);
        // if the puzzle is solved, return the path taken to solve it
        if (temp == -1) {
            reverse(IDAPath.begin(), IDAPath.end());
            totalBoards[0] += visitedBoards.size();
            IDAPath.push_back(totalBoards);
            return IDAPath;
        }
        // if the puzzle cannot be solved, return an empty vector
        if (temp == INT_MAX) {
            return {};
        }
        // update the threshold and continue the algorithm
        threshold = temp;
    }
}

// helper function for the IDA* algorithm
int SlidingBoardGraph::IDAStarHelper(vector<int>& board, int GScore, int threshold, vector<vector<int>>& IDAPath, set<vector<int>>& visitedBoards, vector<int>& totalBoards) {
    // calculate the heuristic score of the board and the F score
    int HScore = SetHScore(board);
    int FScore = GScore + HScore;
    vector<int> solutionGrid = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    // if the F score is greater than the threshold, return the F score
    if (FScore > threshold) {
        return FScore;
    }
    // if the board is the solution, return -1
    if (board == solutionGrid) {
        IDAPath.push_back(board);
        return -1;
    }
    // add the board to the set of visited boards and find the blank space
    visitedBoards.insert(board);
    int min = INT_MAX;
    vector<vector<int>> successors;
    vector<int> tempGrid;
    int blankRow;
    int blankCol;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i * 3 + j] == 9) {
                blankRow = i;
                blankCol = j;
            }
        }
    }
    //swap up with blank
    if (blankRow > 0) {
        tempGrid = board;
        swap(tempGrid[blankRow * 3 + blankCol], tempGrid[(blankRow * 3 - 3) + blankCol]);
        successors.push_back(tempGrid);
    }
    //swap down with blank
    if (blankRow < 2) {
        tempGrid = board;
        swap(tempGrid[blankRow * 3 + blankCol], tempGrid[(blankRow * 3 + 3) + blankCol]);
        successors.push_back(tempGrid);
    }
    //swap left with blank
    if (blankCol > 0) {
        tempGrid = board;
        swap(tempGrid[blankRow * 3 + blankCol], tempGrid[blankRow * 3 + (blankCol - 1)]);
        successors.push_back(tempGrid);
    }
    //swap right with blank
    if (blankCol < 2) {
        tempGrid = board;
        swap(tempGrid[blankRow * 3 + blankCol], tempGrid[blankRow * 3 + (blankCol + 1)]);
        successors.push_back(tempGrid);
    }
    // loop through the successors and call the helper function recursively
    for (vector<int>& successor : successors) {
        if (visitedBoards.find(successor) == visitedBoards.end()) {
            int temp = IDAStarHelper(successor, GScore + 1, threshold, IDAPath, visitedBoards, totalBoards);
            // if the puzzle is solved, return -1
            if (temp == -1) {
                IDAPath.push_back(board);
                return -1;
            }
            // update the minimum F score
            if (temp < min) {
                min = temp;
            }
        }
    }
    // remove the board from the set of visited boards and return the minimum F score
    totalBoards[0] += visitedBoards.size();
    visitedBoards.erase(board);
    return min;
}

// for SlidingBoardGraph constructor, set the heuristic score for the board
// uses the Manhattan distance to calculate the heuristic score
// reference: https://www.geeksforgeeks.org/maximum-manhattan-distance-between-a-distinct-pair-from-n-coordinates/
int SlidingBoardGraph::SetHScore(vector<int>& board) {
    int hScore = 0;
    // calculate the Manhattan distance for each tile on the board and add it to the heuristic score
    for (int i = 0; i < 9; i++) {
        if (board[i] != 9) {
            int row = i / 3;
            int col = i % 3;
            int correctRow = (board[i] - 1) / 3;
            int correctCol = (board[i] - 1) % 3;
            hScore += abs(row - correctRow) + abs(col - correctCol);
        }
    }
    // return the heuristic score
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

    //assembles path taken by BFS to get to the solution grid
    vector<vector<int>> BoardPath;
    //loops through until no parent is found
    BoardPath.push_back(solutionGrid); //solution is always last child/step
    while(!gridParent[currGrid].empty()){
        BoardPath.insert(BoardPath.begin(), gridParent[currGrid]);
        currGrid = gridParent[currGrid];
    }

    //add the total grid lines created at the end of the board path
    vector<int> totalGridLines = {0};
    totalGridLines[0] = visitedBoards.size();
    BoardPath.push_back(totalGridLines);

    return BoardPath;
}
