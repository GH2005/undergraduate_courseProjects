Artificial Intelligence - the course project.
There is a well-known problem, the 8-puzzle problem, that requires brute-force search. The A* heuristic algorithm can be used to speed up the search.
What I implemented in "main.cpp" is a solution to (N*N-1)-puzzle problem where N is the length of the square grid. In the square grid, each position has an index, and the heuristic value I used was the difference between indices of two positions.
