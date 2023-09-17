# pathfinding-engine

A C++ pathfinding engine that uses Dijkstra's to find the shortest path between 2 points. 

### Input Files and Run Commands
The input file contains the number of different edges, the edges and edge weights, the size of the grid, the grid itself, and the coordinates that you want to find the shortest path between.

Example input .txt file:

6 <br />
f 3 <br />
g 1 <br />
G 2 <br />
h 4 <br />
m 7 <br />
r 5 <br />
10 10 <br />
G r g g m m m r f m <br />
G g r G G G G m f h <br />
m r f m m f G r h h <br />
G m G f h r g m g g <br />
g g g m h m h f m f <br />
h r g f f f g h r h <br />
m G f r m m G r g f <br />
m r h h h h G m m r <br />
r r g f G r r m f r <br />
G g r g g r h m m r <br />
0 0 <br />
7 6 <br />


How to Run:

  g++ -o dijkstras dijkstras.cpp <br />
  ./dijkstras < inputfile.txt    <br />

### Output

The output contains the weight/length of the shortest path and the path itself.

The input above gives us the output: 

27 <br />
0 0 <br />
0 1 <br />
0 2 <br />
0 3 <br />
1 3 <br />
1 4 <br />
1 5 <br />
1 6 <br />
2 6 <br />
3 6 <br /> 
4 6 <br />
5 6 <br />
6 6 <br />
7 6 <br />
 
