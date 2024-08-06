# TileTango

Problem: Solving a sliding puzzle of size 3x3 using two different algorithms to compare the paths they will take and time to get to their solutions.

Motivation: Sliding puzzles are a fun logic puzzle that are created to be solved. In this case, the problem is solving the puzzle while the board is scrambled because it isn't solved.

Features: When the block’s number matches the randomly generated solution, this indicates that the puzzle is complete. The solution is a generalized board of blocks with numbers arranged in ascending order that the scrambled puzzles must match.

![solving puzzle](https://github.com/user-attachments/assets/b4bab71c-9ed4-47fe-a995-4841de4a660b)


Data: 100,000 randomly generated puzzle boards ranging in difficulty. These boards will be contained in a txt file with many lines of formatted randomly generated numbers.

Tools: Openframeworks for the GUI using SFML library and C++.

Strategy: We will be implementing IDA* and BFS as our algorithms. Our boards will be individual graphs with points being puzzle board states and edges being valid moves for the blocks.


## Running Instructions

This project was initially coded in the CLion IDE. To compile the project download the entire zip folder of the project or clone it as all of the assets, including the data.txt file, SFML library, and images, are included within the repository. 
Next, using Clion open the CMakeList.txt, press "open (folder name)" as project, let it compile using the file, and then run the project.
If Clion is not being used for compiling, any method in general that allows you to operate with Cmake to build and install the CMakeList.txt file will work.

Step by step:
1. Install Cmake version 3.27+ for your respective OS, https://cmake.org/download/ 
2. Once in your respective terminal, cd to the file "TileTango-main" or the files name. paste in these instructions into the cmake terminal.
'''
make -C build install
cmake --build build --target install
--install build
'''
