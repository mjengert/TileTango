#ifndef TILETANGO_SLIDINGBOARDGRAPH_H
#define TILETANGO_SLIDINGBOARDGRAPH_H
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <fstream>
using namespace std;

struct SlidingBoard {
    int Board[3][3];
    // constructor for the board from file
    explicit SlidingBoard(vector<int> board) {
        int index = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                Board[i][j] = board[index];
                index++;
            }
        }
    }
    // constructor for the board from move
    explicit SlidingBoard(int board[3][3]) {
        int index = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                Board[i][j] = board[i][j];
                index++;
            }
        }
    }
};

// class to form the graph of the sliding board
class SlidingBoardGraph {
public:
    // constructor and destructor
    SlidingBoardGraph() {
        root = nullptr;
    }
    ~SlidingBoardGraph() {
        delete root;
    }
    // operations on the graph
    void GetBoardFromFile(const string& filename);
    SlidingBoard* GetRoot() { return root; }
    vector<vector<int>> IDAStar(SlidingBoard* board, int GScore);
    int IDAStarHelper(vector<int>& board, int GScore, int threshold, vector<vector<int>>& IDAPath, set<vector<int>>& visitedBoards, vector<int>& totalBoards);
    int SetHScore(vector<int>& board);
    vector<vector<int>> BFS(SlidingBoard* board);
private:
    // private variables
    SlidingBoard* root;
    vector<SlidingBoard*> usedBoards = {};
};

#endif //TILETANGO_SLIDINGBOARDGRAPH_H
