// ------------------------------------------------ graphm.cpp -------------------------------------------------------
// Brittney Oeur, CSS 343 A
// Creation Date: 4/30/23
// Date of Last Modification: 5/5/23
// --------------------------------------------------------------------------------------------------------------------
// Description: This implementation file focuses on the Dijkstra's shortest path algorithm. It will be able to read
// a data file consistenting many lines and will be able to find the lowest cost paths and disply the cost and path
// from every node to every other node. Another display routine will output one path in detail.
// --------------------------------------------------------------------------------------------------------------------

#include "graphm.h"
#include <iomanip>

// ------------------------------------ Default constructor -----------------------------------------------
// Description: This a default constructor
// --------------------------------------------------------------------------------------------------- 
GraphM::GraphM() {
    // Set size to 0
    size = 0;

    // Loops as long 'i' is less than MAXNODES
    for (int i = 1; i < MAXNODES; i++) {
        // Loops as long 'j' is less than MAXNODES
        for (int j = 1; j < MAXNODES; j++) {
            // Store max value into adjacency matrix
            C[i][j] = INT_MAX;

            // Has not visited
            T[i][j].visited = false;

            // Set distance to max value
            T[i][j].dist = INT_MAX;

            // Path is empty
            T[i][j].path = 0;
        }
    }
}

// ------------------------------------ buildGraph() -----------------------------------------------
// Description: This will build the graph node information and the adjacency matrix of edges
// between each node reaching from a file
// --------------------------------------------------------------------------------------------------- 
void GraphM::buildGraph(ifstream& infile) {
    // Read from data file
    infile >> size;

    // Set string to empty
    string name = "";

    // Reads the line of text input
    getline(infile, name);

    for (int i = 1; i <= size; i++) {
        // Set the node names
        data[i].setData(infile);
    }

    int from;
    int to;
    int distance;

    // Loops as long there from is not empty
    while (infile >> from >> to >> distance) {
        if (from == 0) {
            // Read the file till node is 0
            break;
        }

        // Set the C table
        C[from][to] = distance;
    }
}

// ------------------------------------ insertEdge() -----------------------------------------------
// Description: Insert an edge into graph between two given nodes
// --------------------------------------------------------------------------------------------------- 
bool GraphM::insertEdge(int from, int to, int distance) {
    // If from is greater than size OR from is less than 1
    if (from > size || from < 1) {
        return false;
    }

    // If to is greater than size OR to is less than 1
    if (to > size || to < 1) {
        return false;
    }

    // If distance is less than 0
    if (distance < 0) {
        return false;
    }

    // If distance is not 0 AND from equals to
    if (distance != 0 && from == to) {
        return false;
    }

    // Inserts the edges to the adjacency matrix
    C[from][to] = distance;

    // Redo the shortest path algorithm with change
    findShortestPath();
    
    // Was able to insert an edge into graph
    return true;
}

// ------------------------------------ removeEdge() -----------------------------------------------
// Description: Remove an edge between two given nodes
// --------------------------------------------------------------------------------------------------- 
bool GraphM::removeEdge(int from, int to) {
    // If from is greater than size OR from is less than 1
    if (from > size || from < 1) {
        return false;
    }

    // If to is greater than size OR to is less than 1
    if (to > size || to < 1) {
        return false;
    }

    // Removes the edges from the adjacency matrix
    C[from][to] = INT_MAX;

    // Redoce the shortest path algorithm with change
    findShortestPath();

    // Able to remove an edge
    return true;
}

// ------------------------------------ findShortestPath() -----------------------------------------------
// Description: Find the shortest path between every node to every other node in the
// graph, i.e., TableType T is updated with shortest path information
// --------------------------------------------------------------------------------------------------- 
void GraphM::findShortestPath() {
    // Side note to self:
    //Source node: In graph theory, a source node is the starting vertex in a graph traversal or a shortest path algorithm.
    
    // Loops until it reaches the size
    for (int source = 1; source <= size; source++) {
        // Set the current distance to 0
        T[source][source].dist = 0;

        // Has visited path
        T[source][source].visited = true;

        // Loops until it reaches size:
        for (int j = 1; j <= size; j++) {
            // If the adjacency matrix does not equal to INT_MAX
            if (C[source][j] != INT_MAX) {
                // Set T's distance to the spot where the adjacency is at
                T[source][j].dist = C[source][j];

                // Set the path to the source
                T[source][j].path = source;
            }
        }

        // Smallest vertex
        int smallestVertex = 0;

        // Loop counter
        int loopCounter = 0;

        // Loops as long smallestVertex is not 0 OR loop counter is 0
        while(smallestVertex != 0 || loopCounter == 0) {
            // Set min to INT_MAX
            int min = INT_MAX;

            // Set 0 to smallestVertex
            smallestVertex = 0;

            // Loops until x reaches to size
            // Finds the nearest child
            for (int x = 1; x <= size; x++) {
                // If T has not visted AND the adjacency matrix is less than the min
                if (!T[source][x].visited && (C[source][x] < min)) {
                    // Set the adjacency matrix to min
                    min = C[source][x];

                    // Set the smallestVertex of the current index
                    smallestVertex = x;
                }
            }

            // If the smallestVertex is not 0
            if (smallestVertex != 0) {
                // Node visited
                T[source][smallestVertex].visited = true;

                // Loops z until it reaches size
                for (int z = 1; z <= size; z++) {
                    // If path has been visited
                    if (T[source][z].visited) {
                        continue;
                    }

                    // If the adjacency matrix equals to INT_MAX
                    if (C[smallestVertex][z] == INT_MAX) {
                        continue;
                    }

                    // If T's distance (with smallestVertex) and the adjacency vertex is less than T's distance
                    if (T[source][smallestVertex].dist + C[smallestVertex][z] < T[source][z].dist) {
                        // Set T's distance
                        T[source][z].dist = T[source][smallestVertex].dist + C[smallestVertex][z];
                        // Set T's path to the smallextVertex
                        T[source][z].path = smallestVertex;
                    }
                }
            }
            // Increment loop counter
            loopCounter++;
        }
    }
}

// ------------------------------------ displayAll() -----------------------------------------------
// Description: uses couts to demonstrate that the algorithm works properly. For the data in
// Figure 1, it will produce the sample output below (similar to, use the general format, but
// blanks do not need not be exact)
// --------------------------------------------------------------------------------------------------- 
void GraphM::displayAll() {
    // Prints table titles
    cout << "Description" << setw(20)<< "From node" << setw(15) << "To node" << setw(15) << "Dijkstra's" << setw(5) << "Path" << endl;
    for (int from = 1; from <= size; from++) {
        // Prints the starting point
        cout << data[from] << endl << endl;

        // Loops until it reaches the size
        for (int to = 1; to <= size; to++) {
            // If T's distance is not 0
            if (T[from][to].dist != 0) {
                // Prints out spaces in between
                cout << setw(20) << from;
                cout << setw(10) << to;

                // If T's distance is at INT_MAX
                if (T[from][to].dist == INT_MAX) {
                    // Print out blank
                    cout << setw(15) << "----" << endl;
                }
                
                // IF T's distance is not at INT_MAX
                else {
                    // Print out the distance
                    cout << setw(15) << T[from][to].dist;
                    cout << setw(10);

                    // Looks for the path to the destination
                    findPathHelper(from, to);
                    cout << "" << endl;
                }

            }
        }
    }
}

// ------------------------------------ display() -----------------------------------------------
// Description: Uses couts to display the shortest distance with path info between the fromNode to
// toNode. For the data in Figure 1, a call of G.display(1,4) is going to produce the following
// output (similar to):
// --------------------------------------------------------------------------------------------------- 
void GraphM::display(int from, int to) {
    // If from is greater than size OR from is less than 0 
    // OR 
    // to is greater than size OR to is less than 0
    if ((from > size || from < 0) || (to > size || to < 0)) {
        // Print out blanks
        cout << setw(7) << from << setw(7) << to;
        cout << setw(15) << "----" << endl;
        return;
    }

    // Set spaces in between from and to
    cout << setw(7) << from << setw(7) << to;

    // If T's distance is not equal to INT_MAX
    if (T[from][to].dist != INT_MAX) {
        // Print out the distance's value
        cout <<  setw(15) << T[from][to].dist << setw(15);

        // Calls findPath to look for the path
        findPathHelper(from, to);
        cout << "" << endl;
        // Calls findPath to look for the path
        findDataHelper(from, to);
    }

    // If T's distance is equal to INT_MAX
    else {
        // Print blank, no adjacent node
        cout << setw(15) << "----" << endl;
    }
    cout << endl;
}

// ------------------------------------ findData() -----------------------------------------------
// Description: Helper method for display() R
// ecursively finds data for the given edge distance
// --------------------------------------------------------------------------------------------------- 
void GraphM::findDataHelper(int from, int to) {
    // If T's distance is at INT_MAX
    if (T[from][to].dist == INT_MAX) {
        // Path does not exist
        return;
    }

    // If the from equals to's path
    if (from == to) {
        // Prints out the given data of the path
        cout << data[to] << endl;
        return;
    }

    // Set the dataNode to the path
    int dataNode = to;

    // Reusirve call on findData
    findDataHelper(from, to = T[from][to].path);

    // Prints out the current path's data
    cout << data[dataNode] << endl << endl;
}

// ------------------------------------ findPath() -----------------------------------------------
// Description: Helper method for displayAll() and display().
// Finds the path for the given edge
// --------------------------------------------------------------------------------------------------- 
void GraphM::findPathHelper(int from, int to) {
    // If T's distance is at INT_MAX
    if (T[from][to].dist == INT_MAX) {
        // Path does not exist
        return;
    }

    // If from equals to's path
    if (from == to) {
        // Print out the data
        cout << to << " ";
        return;
    }

    // Set dataPath to the path
    int dataPath = to;

    // Recursive call on findPath
    findPathHelper(from, to = T[from][to].path);

    // Prints out the current path
    cout << dataPath << " ";
}