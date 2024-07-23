#include <iostream>
#include "SlidingBoards.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

// Project 3 - TileTango
// Partners: Maralynn Engert, Natalie Poche, Andre Stennett

// Generate lots of boards; used for creating the AllBoards.txt file
void GenerateLotsOfBoards() {
    SlidingBoards Board;
    // Generate lots of boards
    Board.GenerateLotsOfBoards();
}

// Main function
int main() {
    // the current state of the main function is only used for generating lots of boards
    // will be commented out when the boards are generated and solvable, then will be changed to window creation
    // after they are correctly generated we will pull from the AllBoards.txt file
    // i do not recommend running the program with this uncommented if you have a slow computer cause it will take a while
    // - Maralynn

    GenerateLotsOfBoards();
    return 0;
}
