#ifndef GRAPHM_HEADER
#define GRAPHM_HEADER

#include <iostream>
#include <fstream>
#include "nodedata.h"
#include "nodedata.cpp"

using namespace std;

// CONST size for T and C table
const int MAXNODES = 101;   

class GraphM {
    public:
        // Default constructor
        GraphM();   

        // builds up graph node information and adjacency matrix of edges between each
        // node reading from a data file.
        void buildGraph(ifstream& infile);  

        // insert an edge into graph between two given nodes
        bool insertEdge(int from, int to, int distance);  

        // remove an edge between two given nodes  
        bool removeEdge(int from, int to);  

        // ind the shortest path between every node to every other node in the
        // graph, i.e., TableType T is updated with shortest path information
        void findShortestPath();

        // uses couts to demonstrate that the algorithm works properly
        void displayAll(); 

        // uses couts to display the shortest distance with path info between the fromNode to toNode
        void display(int from, int to); 

    
    private:
        // TableType is a struct to keep the current shortest distance 
        // (and associated path info) known at any point in the algorithm
        struct TableType {

            // whether node has been visited
            bool visited; 

            // shortest distance from source known so far
            int dist;   

            // previous node in path of min dist
            int path;   
        };

        // data for graph nodes
        NodeData data[MAXNODES];   

        // Cost array, the adjacency matrix
        int C[MAXNODES][MAXNODES];  

        // number of nodes in the graph
        int size;   

        // stores visited, distance, path
        TableType T[MAXNODES][MAXNODES];    

        // Helper function for display() 
        void findDataHelper(int from, int to);    

        // Find the shortest path between every node to every other node in the graph
        void findPathHelper(int from, int to);    
};

#endif