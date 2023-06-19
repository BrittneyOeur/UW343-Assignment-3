# UW343-Assignment-3
**Part 1: Programming (Dijkstra's shortest path algorithm)**
- This project is to implement Dijkstra's shortest path algorithm. Your code should be able to read a data file consisting of many lines (an example file called data31.txt will be given, explained below) and will be able to find the lowest cost paths (findShortestPath function) and display the cost and path from every node to every other node (displayAll function). Another display routine (display function) will output one path in detail.
In the input data (e.g., data31.txt), the first line tells the number of nodes, say n, followed by a text description of each of the 1 through n nodes, one description per line (50 chars max length). After that, each line consists of 3 integers representing an edge. If there is an edge from node 1 to node 2 with a label of 10, the data is: 1 2 10. If the first integer is zero, it means the end of the data for that one graph. There may be several graphs, each having at most 100 nodes

**Part 2: Programming (depth-first search)**
- This project is to display the graph information and implement depth-first (search always starts at node #1). Similar to Part 1, in the input data (e.g., data32.txt), the first line tells the number of nodes, say n,
followed by a text description of each of the 1 through n nodes, one description per line (50 chars max length). After that, each line consists of 2 integers (instead of 3 integers in Part 1) representing an edge. If there is an edge from node 1 to node 2, the data is: 1 2. A zero for the first integer signifies the end of the data for that one graph. In the file, all the edges for the 1st node will be listed first, then all the edges for the 2nd node, etc. Take them as they come, no sorting. There may be several graphs, each having at most 100 nodes. 
