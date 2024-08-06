#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <fstream>
#include "SlidingBoardsGen.h"
using namespace std;

// file for implementing the sliding block puzzle class

// for understanding the positioning of the tiles, refer to the following:
// 1  2  3
// 4  5  6
// 7  8  9

// the blank tile is represented by 16 in the preceding diagram
// when referenced in the code below, saying "position 1" means the POSITION of the tile
// with the number 1, in other words, the top left corner of the board

void SlidingBoardsGen::GenerateLotsOfBoards() {
    // open the file to write the boards to
    ofstream BoardFile("../DATA/AllBoards.txt");
    if (!BoardFile) {
        cout << "Error opening file" << endl;
    }
    // if the file is opened successfully, generate 100,000 boards
    else {
        cout << "File opened successfully" << endl;
        for (int i = 1; i <= 100000; i++) {
            GenerateBoard();
            // first check if the board is solvable before writing it to the file
            if (!isSolvable()) {
                i--;
            }
            // if the board is solvable, write it to the file
            else {
                // format is as follows: Board number followed by the adjacent tiles
                for (auto it = BoardList.begin(); it != BoardList.end(); it++) {
                    BoardFile << it->first << " ";
                    for (int j = 0; j < it->second.size(); j++) {
                        BoardFile << it->second[j].first << " ";
                    }
                    BoardFile << endl;
                }
                BoardFile << endl;
            }
        }
        BoardFile.close();
    }
    cout << "File closed successfully" << endl;
}

// generates a board randomly
void SlidingBoardsGen::GenerateBoard() {
    // clear the board list
    BoardList.clear();
    // generate a random board
    int tiles = 9;
    while (tiles > 0) {
        int tile = rand() % 9 + 1;
        if (BoardList.find(tile) == BoardList.end()) {
            BoardList[tile] = {};
            tiles--;
        }
    }
    // determine adjacent tiles for each tile
    int position = 1;
    auto prevIt1 = BoardList.begin();
    auto prevIt3 = BoardList.begin();
    for (auto it = BoardList.begin(); it != BoardList.end(); it++) {
        // position 1
        if (position == 1) {
            auto it2 = next(it, 1);
            auto it4 = next(it, 3);
            BoardList[it->first].push_back(make_pair(it2->first, 1));
            BoardList[it->first].push_back(make_pair(it4->first, 1));
            position++;
        }
        // position 2
        else if (position == 2) {
            auto it3 = next(it, 1);
            auto it5 = next(it, 3);
            BoardList[it->first].push_back(make_pair(prevIt1->first, 1));
            BoardList[it->first].push_back(make_pair(it3->first, 1));
            BoardList[it->first].push_back(make_pair(it5->first, 1));
            position++;
            prevIt1++;
        }
        // position 3
        else if (position == 3) {
            auto it6 = next(it, 3);
            BoardList[it->first].push_back(make_pair(prevIt1->first, 1));
            BoardList[it->first].push_back(make_pair(it6->first, 1));
            position++;
            prevIt1++;
        }
        // position 4
        else if (position == 4) {
            auto it5 = next(it, 1);
            auto it7 = next(it, 3);
            BoardList[it->first].push_back(make_pair(prevIt3->first, 1));
            BoardList[it->first].push_back(make_pair(it5->first, 1));
            BoardList[it->first].push_back(make_pair(it7->first, 1));
            position++;
            prevIt1++;
            prevIt3++;
        }
        // position 5
        else if (position == 5) {
            auto it6 = next(it, 1);
            auto it8 = next(it, 3);
            BoardList[it->first].push_back(make_pair(prevIt3->first, 1));
            BoardList[it->first].push_back(make_pair(prevIt1->first, 1));
            BoardList[it->first].push_back(make_pair(it6->first, 1));
            BoardList[it->first].push_back(make_pair(it8->first, 1));
            position++;
            prevIt1++;
            prevIt3++;
        }
        // position 6
        else if (position == 6) {
            auto it9 = next(it, 3);
            BoardList[it->first].push_back(make_pair(prevIt3->first, 1));
            BoardList[it->first].push_back(make_pair(prevIt1->first, 1));
            BoardList[it->first].push_back(make_pair(it9->first, 1));
            position++;
            prevIt1++;
            prevIt3++;
        }
        // position 7
        else if (position == 7) {
            auto it8 = next(it, 1);
            BoardList[it->first].push_back(make_pair(prevIt3->first, 1));
            BoardList[it->first].push_back(make_pair(it8->first, 1));
            position++;
            prevIt1++;
            prevIt3++;
        }
        // position 8
        else if (position == 8) {
            auto it9 = next(it, 1);
            BoardList[it->first].push_back(make_pair(prevIt3->first, 1));
            BoardList[it->first].push_back(make_pair(prevIt1->first, 1));
            BoardList[it->first].push_back(make_pair(it9->first, 1));
            position++;
            prevIt1++;
            prevIt3++;
        }
        // position 9
        else if (position == 9) {
            BoardList[it->first].push_back(make_pair(prevIt3->first, 1));
            BoardList[it->first].push_back(make_pair(prevIt1->first, 1));
            position++;
            prevIt1++;
            prevIt3++;
        }
    }
}

// checks if the board is solvable using the inversion method
// used https://www.geeksforgeeks.org/check-instance-15-puzzle-solvable/# for reference
bool SlidingBoardsGen::isSolvable() {
    // initialize vector to hold the board and count the number of inversions
    int inversions = 0;
    vector <int> board;
    for (auto it = BoardList.begin(); it != BoardList.end(); it++) {
        board.push_back(it->first);
    }
    // count the number of inversions
    for (int i = 0; i < board.size(); i++) {
        for (int j = i + 1; j < board.size(); j++) {
            if (board[i] > board[j] && board[i] != 9 && board[j] != 9) {
                inversions++;
            }
        }
    }
    // check if the board is solvable
    if (inversions % 2 == 0) {
        return true;
    }
    // if the board isn't solvable, return false
    else {
        return false;
    }
}


