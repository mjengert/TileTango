#ifndef TILETANGO_SLIDINGBOARDGRAPH_H
#define TILETANGO_SLIDINGBOARDGRAPH_H
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <fstream>
using namespace std;

struct SlidingBoard {
    int Board[4][4];
    int heuristic;
    int difficulty;
    SlidingBoard* parent;
    // constructor for the board
    SlidingBoard(vector<int> board) {
        int index = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                Board[i][j] = board[index];
                index++;
            }
        }
        this->heuristic = 0;
        this->difficulty = 0;
        this->parent = nullptr;
    }
};

// class to create the graph (verticies are boards, edges are moves)
class SlidingBoardGraph {
public:
    // constructor and destructor
    SlidingBoardGraph() {
        root = nullptr;
    }
    ~SlidingBoardGraph() {
        if (root != nullptr) {
            DeleteGraph(root);
        }
    }
    // operations on the graph
    void GetBoardFromFile(string filename);
    void InsertBoard(SlidingBoard* board);
    void GetMoves(SlidingBoard* board);
    int GetHeuristic(SlidingBoard* board);
    int GetDifficulty(SlidingBoard* board);
    void PrintBoard();
    void DeleteGraph(SlidingBoard* board);

private:
    // private variables
    SlidingBoard* root;
    int blankRow;
    int blankCol;
    int Solution[4][4] = {{1, 2, 3, 4},
                          {5, 6, 7, 8},
                          {9, 10, 11, 12},
                          {13, 14, 15, 0}};
};

#endif //TILETANGO_SLIDINGBOARDGRAPH_H
