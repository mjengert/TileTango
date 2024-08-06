# TileTango

Problem: Solving a sliding puzzle of size 3x3 using two different algorithms to compare the paths they will take and time to get to their solutions.

Motivation: Sliding puzzles are a fun logic puzzle that are created to be solved. In this case, the problem is solving the puzzle while the board is scrambled because it isn't solved.

Features: When the block’s number matches the randomly generated solution, this indicates that the puzzle is complete. The solution is a generalized board of blocks with numbers arranged in ascending order that the scrambled puzzles must match.

![solving puzzle](https://github.com/user-attachments/assets/b4bab71c-9ed4-47fe-a995-4841de4a660b)


Data: 100,000 randomly generated puzzle boards ranging in difficulty. These boards will be contained in a txt file with many lines of formatted randomly generated numbers.

Tools: Openframeworks for the GUI using SFML library and C++.

Strategy: We will be implementing IDA* and BFS as our algorithms. Our boards will be individual graphs with points being puzzle board states and edges being valid moves for the blocks.
