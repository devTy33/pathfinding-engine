# pathfinding-engine

A C++ pathfinding engine that uses Dijkstra's to find the shortest path between 2 points. 

### Input Files and Run Commands
The input file contains the number of different edges, the edges and edge weights, the size of the grid, the grid itself, and the coordinates that you want to find the shortest path between.

Example input .txt file:

6

f 3

g 1
G 2
h 4
m 7
r 5
10 10
G r g g m m m r f m
G g r G G G G m f h
m r f m m f G r h h
G m G f h r g m g g
g g g m h m h f m f
h r g f f f g h r h
m G f r m m G r g f
m r h h h h G m m r
r r g f G r r m f r
G g r g g r h m m r
0 0
7 6


How to Run:

  g++ -o dijkstras dijkstras.cpp
  ./dijkstras < inputfile.txt

### Output

The output contains the weight/length of the shortest path and the path itself.

The input above gives us the output: 

27
0 0
0 1
0 2
0 3
1 3
1 4
1 5
1 6
2 6
3 6
4 6
5 6
6 6
7 6
