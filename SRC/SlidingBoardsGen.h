#ifndef TILETANGO_SLIDINGBOARDS_H
#define TILETANGO_SLIDINGBOARDS_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

// file for board class and functions
class SlidingBoardsGen {
public:
    // operations
    void GenerateLotsOfBoards();
    void GenerateBoard();
    bool isSolvable();
private:
    // private variables
    unordered_map<int, vector<pair<int, double>>> BoardList;
    map<int, vector<pair<int, double>>> SolutionList = {
            {1,  {{2,  1}, {5,  1}}},
            {2,  {{1,  1}, {3,  1}, {6,  1}}},
            {3,  {{2,  1}, {4,  1}, {7,  1}}},
            {4,  {{3,  1}, {8,  1}}},
            {5,  {{1,  1}, {6,  1}, {9,  1}}},
            {6,  {{2,  1}, {5,  1}, {7,  1}, {10, 1}}},
            {7,  {{3,  1}, {6,  1}, {8,  1}, {11, 1}}},
            {8,  {{4,  1}, {7,  1}, {12, 1}}},
            {9,  {{5,  1}, {10, 1}, {13, 1}}}
    };
};

#endif //TILETANGO_SLIDINGBOARDS_H
