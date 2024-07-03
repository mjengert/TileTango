# TileTango

Problem: Solving a sliding puzzle using two different algorithms to compare the paths they will take to get to the solution.

Motivation: Sliding puzzles are a fun logic puzzle that are created to be solved. In this case, the problem is solving the puzzle while the board is scrambled because it isn't solved.

Features: When the block’s number matches the randomly generated solution, this indicates that the puzzle is complete. The solution is a generalized board of blocks with numbers arranged in ascending order that the scrambled puzzles must match.

Data: 100,000 randomly generated puzzle boards ranging in difficulty. These boards will be contained in a B+ tree (keys being the difficulty of the board).

Tools: Openframeworks for the GUI and C++

Strategy: We will be implementing A* and BFS as our algorithms. Our boards will be individual graphs with points being puzzle board states and edges being valid moves for the blocks.
