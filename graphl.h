#ifndef GRAPHL_HEADER
#define GRAPHL_HEADER

#include <iostream>
#include <fstream>
#include "nodedata.h"

using namespace std;

// CONST size for an array
const int MAXNODESL = 101;

class GraphL {
    public:
        // Default constructor
        GraphL();   

        // Destructor
        ~GraphL();  

        // builds up graph node information and adjacency list of 
        // edges between each node reading from a data file
        void buildGraph(ifstream& infile);

        // Displays each node information and edge in the graph
        void displayGraph();

        // Makes a depth-first search and displays each node in depth-first order
        void depthFirstSearch();


    private:
        // forward reference for the compiler
        struct EdgeNode;

        // structs used for simplicity, use classes if desired
        struct GraphNode {
            // head of the list of edges
            EdgeNode* edgeHead;

            // data information about each node
            NodeData* data;

            // whether node has been visited
            bool visited;
        };

        // Array of GraphNodes
        GraphNode node[MAXNODESL];

        // number of nodes in the graph
        int size;

        struct EdgeNode {
            // subscript of the adjacent graph node
            int adjGraphNode;
            EdgeNode* nextEdge;
        };

        // Deletes the object
        void makeEmpty();

        // Helper method for depthFirstSearch()
        void depthFirstSearchHelper(int x);
};

#endif