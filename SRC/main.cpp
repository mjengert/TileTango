#include "SlidingBoardsGen.h"
#include "SlidingBoardGraph.h"
#include  "WelcomeWindow.h"

// Project 3 - TileTango
// Partners: Maralynn Engert, Natalie Poche, Andre Stennett

// generate lots of boards; used for creating the AllBoards.txt file
// currently not in use as the file has already been created

void GenerateLotsOfBoards() {
    SlidingBoardsGen Board;
    // generate lots of boards
    Board.GenerateLotsOfBoards();
}

// main function
int main() {
    // setup the window size and the graph
    int width = 1000;
    int height = 700;
    SlidingBoardGraph Graph;
    Graph.GetBoardFromFile("../DATA/AllBoards.txt");
    WelcomeWindow welcome(width,height, Graph);
    return 0;
}
