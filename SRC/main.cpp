#include "SlidingBoardsGen.h"
#include "SlidingBoardGraph.h"
#include "WelcomeWindow.h"

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

//    int width = 1000;
//    int height = 900;
//    WelcomeWindow welcome(width,height);

    SlidingBoardGraph Graph;
    Graph.GetBoardFromFile("../DATA/AllBoards.txt");
    return 0;
}
