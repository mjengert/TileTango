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
    int Board[3][3] = {};
    int heuristic;
    int blankRow;
    int blankCol;
    SlidingBoard* parent = nullptr;
    vector<SlidingBoard*> children = {};
    // constructor for the board from file
    explicit SlidingBoard(vector<int> board) {
        int index = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[index] == 9) {
                    blankRow = i;
                    blankCol = j;
                }
                Board[i][j] = board[index];
                index++;
            }
        }
        this->heuristic = 0;
        this->parent = nullptr;
        this->children = {};
    }
    // constructor for the board from move
    explicit SlidingBoard(int board[3][3]) {
        int index = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 9) {
                    blankRow = i;
                    blankCol = j;
                }
                Board[i][j] = board[i][j];
                index++;
            }
        }
        this->heuristic = 0;
        this->parent = nullptr;
        this->children = {};
    }
};

// Class to create the graph (verticies are boards, edges are moves)
class SlidingBoardGraph {
public:
    // Constructor and destructor
    SlidingBoardGraph() {
        root = nullptr;
    }
    ~SlidingBoardGraph() {
        if (root != nullptr) {
            DeleteGraph(root);
        }
    }
    // Operations on the graph
    void GetBoardFromFile(string filename);
    void InsertBoard(SlidingBoard* board);
    void GetAllMoves(SlidingBoard* board, int depth);
    bool IsSolution(SlidingBoard* board);
    void CreateMove(SlidingBoard* board, int row, int col);
    int GetHeuristic(SlidingBoard* board);
    void PrintBoard();
    void DeleteGraph(SlidingBoard* board);

private:
    // Private variables
    SlidingBoard* root;
    vector<SlidingBoard*> usedBoards = {};
    vector<SlidingBoard*> gameStates = {};
    int Solution[3][3] = {{1, 2, 3},
                          {4, 5, 6},
                          {7, 8, 9}};
};

#endif //TILETANGO_SLIDINGBOARDGRAPH_H
