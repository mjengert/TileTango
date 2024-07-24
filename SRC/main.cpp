#include <iostream>
#include "SlidingBoardsGen.h"
#include "SlidingBoardGraph.h"
#include "SlidingBoards.h"
using namespace std;
using namespace sf;

// Project 3 - TileTango
// Partners: Maralynn Engert, Natalie Poche, Andre Stennett

// Generate lots of boards; used for creating the AllBoards.txt file
// Currently not in use as the file has already been created
void GenerateLotsOfBoards() {
    SlidingBoardsGen Board;
    // Generate lots of boards
    Board.GenerateLotsOfBoards();
}

// Main function
int main() {
    int width = 800;
    int height = 800;
    welcomeWindow welcome(width,height);
    SlidingBoardGraph Graph;
    Graph.GetBoardFromFile("AllBoards.txt");
    return 0;
}
