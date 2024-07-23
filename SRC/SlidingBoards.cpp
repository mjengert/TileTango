#include <iostream>
#include "SlidingBoards.h"
#include "BFS.h"
#include "IDA.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
using namespace sf;
using namespace std;

// File for implementing the sliding block puzzle class

// For understanding of the positioning of the tiles, refer to the following:
// 1  2  3  4
// 5  6  7  8
// 9  10 11 12
// 13 14 15 16
// The blank tile is represented by 16 in the above diagram
// When referenced in the code below, saying "position 1" means the POSITION of the tile
// with the number 1, in other words, the top left corner of the board

void SlidingBoards::GenerateLotsOfBoards() {
    // Open the file to write the boards to
    ofstream BoardFile("../DATA/AllBoards.txt");
    if (!BoardFile) {
        cout << "Error opening file" << endl;
    }
    // If the file is opened successfully, generate 100,000 boards
    else {
        cout << "File opened successfully" << endl;
        for (int i = 1; i <= 100000; i++) {
            GenerateBoard();
            // First check if the board is solvable before writing it to the file
            if (!isSolvable()) {
                i--;
            }
            // If the board is solvable, write it to the file
            else {
                // Format is as follows: Board number followed by the adjacent tiles
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

// Generates a board randomly
void SlidingBoards::GenerateBoard() {
    // Clear the board list
    BoardList.clear();
    // Generate a random board
    int tiles = 16;
    while (tiles > 0) {
        int tile = rand() % 16 + 1;
        if (BoardList.find(tile) == BoardList.end()) {
            BoardList[tile] = {};
            tiles--;
        }
    }
    // Determine adjacent tiles for each tile
    int position = 1;
    auto prevIt1 = BoardList.begin();
    auto prevIt4 = BoardList.begin();
    for (auto it = BoardList.begin(); it != BoardList.end(); it++) {
        // Position 1
        if (position == 1) {
            auto it2 = next(it, 1);
            auto it5 = next(it, 4);
            BoardList[it->first].push_back(make_pair(it2->first, 1));
            BoardList[it->first].push_back(make_pair(it5->first, 1));
            position++;
        }
        // Position 2
        else if (position == 2) {
            auto it3 = next(it, 1);
            auto it6 = next(it, 4);
            BoardList[it->first].push_back(make_pair(prevIt1->first, 1));
            BoardList[it->first].push_back(make_pair(it3->first, 1));
            BoardList[it->first].push_back(make_pair(it6->first, 1));
            position++;
            prevIt1++;
        }
        // Position 3
        else if (position == 3) {
            auto it4 = next(it, 1);
            auto it7 = next(it, 4);
            BoardList[it->first].push_back(make_pair(prevIt1->first, 1));
            BoardList[it->first].push_back(make_pair(it4->first, 1));
            BoardList[it->first].push_back(make_pair(it7->first, 1));
            position++;
            prevIt1++;
        }
        // Position 4
        else if (position == 4) {
            auto it8 = next(it, 4);
            BoardList[it->first].push_back(make_pair(prevIt1->first, 1));
            BoardList[it->first].push_back(make_pair(it8->first, 1));
            position++;
            prevIt1++;
        }
        // Position 5
        else if (position == 5) {
            auto it6 = next(it, 1);
            auto it9 = next(it, 4);
            BoardList[it->first].push_back(make_pair(prevIt4->first, 1));
            BoardList[it->first].push_back(make_pair(it6->first, 1));
            BoardList[it->first].push_back(make_pair(it9->first, 1));
            position++;
            prevIt1++;
            prevIt4++;
        }
        // Position 6
        else if (position == 6) {
            auto it7 = next(it, 1);
            auto it10 = next(it, 4);
            BoardList[it->first].push_back(make_pair(prevIt1->first, 1));
            BoardList[it->first].push_back(make_pair(prevIt4->first, 1));
            BoardList[it->first].push_back(make_pair(it7->first, 1));
            BoardList[it->first].push_back(make_pair(it10->first, 1));
            position++;
            prevIt1++;
            prevIt4++;
        }
        // Position 7
        else if (position == 7) {
            auto it8 = next(it, 1);
            auto it11 = next(it, 4);
            BoardList[it->first].push_back(make_pair(prevIt4->first, 1));
            BoardList[it->first].push_back(make_pair(prevIt1->first, 1));
            BoardList[it->first].push_back(make_pair(it8->first, 1));
            BoardList[it->first].push_back(make_pair(it11->first, 1));
            position++;
            prevIt1++;
            prevIt4++;
        }
        // Position 8
        else if (position == 8) {
            auto it12 = next(it, 4);
            BoardList[it->first].push_back(make_pair(prevIt4->first, 1));
            BoardList[it->first].push_back(make_pair(prevIt1->first, 1));
            BoardList[it->first].push_back(make_pair(it12->first, 1));
            position++;
            prevIt1++;
            prevIt4++;
        }
        // Position 9
        else if (position == 9) {
            auto it10 = next(it, 1);
            auto it13 = next(it, 4);
            BoardList[it->first].push_back(make_pair(prevIt4->first, 1));
            BoardList[it->first].push_back(make_pair(it10->first, 1));
            BoardList[it->first].push_back(make_pair(it13->first, 1));
            position++;
            prevIt1++;
            prevIt4++;
        }
        // Position 10
        else if (position == 10) {
            auto it11 = next(it, 1);
            auto it14 = next(it, 4);
            BoardList[it->first].push_back(make_pair(prevIt4->first, 1));
            BoardList[it->first].push_back(make_pair(prevIt1->first, 1));
            BoardList[it->first].push_back(make_pair(it11->first, 1));
            BoardList[it->first].push_back(make_pair(it14->first, 1));
            position++;
            prevIt1++;
            prevIt4++;
        }
        // Position 11
        else if (position == 11) {
            auto it12 = next(it, 1);
            auto it15 = next(it, 4);
            BoardList[it->first].push_back(make_pair(prevIt4->first, 1));
            BoardList[it->first].push_back(make_pair(prevIt1->first, 1));
            BoardList[it->first].push_back(make_pair(it12->first, 1));
            BoardList[it->first].push_back(make_pair(it15->first, 1));
            position++;
            prevIt1++;
            prevIt4++;
        }
        // Position 12
        else if (position == 12) {
            auto it16 = next(it, 4);
            BoardList[it->first].push_back(make_pair(prevIt4->first, 1));
            BoardList[it->first].push_back(make_pair(prevIt1->first, 1));
            BoardList[it->first].push_back(make_pair(it16->first, 1));
            position++;
            prevIt1++;
            prevIt4++;
        }
        // Position 13
        else if (position == 13) {
            auto it14 = next(it, 1);
            BoardList[it->first].push_back(make_pair(prevIt4->first, 1));
            BoardList[it->first].push_back(make_pair(it14->first, 1));
            position++;
            prevIt1++;
            prevIt4++;
        }
        // Position 14
        else if (position == 14) {
            auto it15 = next(it, 1);
            BoardList[it->first].push_back(make_pair(prevIt4->first, 1));
            BoardList[it->first].push_back(make_pair(prevIt1->first, 1));
            BoardList[it->first].push_back(make_pair(it15->first, 1));
            position++;
            prevIt1++;
            prevIt4++;
        }
        // Position 15
        else if (position == 15) {
            auto it16 = next(it, 1);
            BoardList[it->first].push_back(make_pair(prevIt4->first, 1));
            BoardList[it->first].push_back(make_pair(prevIt1->first, 1));
            BoardList[it->first].push_back(make_pair(it16->first, 1));
            position++;
            prevIt1++;
            prevIt4++;
        }
        // Position 16
        else if (position == 16) {
            BoardList[it->first].push_back(make_pair(prevIt4->first, 1));
            BoardList[it->first].push_back(make_pair(prevIt1->first, 1));
            position++;
            prevIt1++;
            prevIt4++;
        }
    }
}

// From Maralynn Engert PageRank.cpp file aka Project 2
vector<int> SlidingBoards::GetAdjacent(int vertex) {
    vector<int> adjTiles = {};
    for (int i = 0; i < BoardList[vertex].size(); i++) {
        adjTiles.push_back(BoardList[vertex][i].first);
    }
    sort(adjTiles.begin(), adjTiles.end());
    return adjTiles;
}

// Checks if the board is solvable using the inversion method
// Used https://www.geeksforgeeks.org/check-instance-15-puzzle-solvable/# for reference
bool SlidingBoards::isSolvable() {
    // Initialize vector to hold the board and count the number of inversions
    int inversions = 0;
    vector <int> board;
    for (auto it = BoardList.begin(); it != BoardList.end(); it++) {
        board.push_back(it->first);
    }
    // Count the number of inversions
    for (int i = 0; i < board.size(); i++) {
        for (int j = i + 1; j < board.size(); j++) {
            if (board[i] > board[j] && board[i] != 16 && board[j] != 16) {
                inversions++;
            }
        }
    }
    // Find the position of the blank tile
    int blankTile = 0;
    for (int i = 0; i < board.size(); i++) {
        if (board[i] == 16) {
            blankTile = i;
        }
    }
    // Check if the board is solvable
    if ((blankTile % 2 == 0 && inversions % 2 == 1) || (blankTile % 2 == 1 && inversions % 2 == 0)) {
        return true;
    }
    // If the board is not solvable, return false
    else {
        return false;
    }
}


