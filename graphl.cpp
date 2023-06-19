// ------------------------------------------------ graphl.cpp -------------------------------------------------------
// Brittney Oeur, CSS 343 A
// Creation Date: 4/30/23
// Date of Last Modification: 5/5/23
// --------------------------------------------------------------------------------------------------------------------
// Description: This implementation file focuses on the depth-first search algorithm and to display the graph
// information. Similar to the "graphm.cpp" file, in the input data, the first line tells the number of nodes, 
// say n, followed by a text description of each of the 1 through n nodes, on description per line.
// After that, each line consists of 2 intergers represnting an edge. 
// --------------------------------------------------------------------------------------------------------------------

#include "graphl.h"
#include <iomanip>

// ------------------------------------ Default constructor -----------------------------------------------
// Description: This a default constructor
// --------------------------------------------------------------------------------------------------- 
GraphL::GraphL() {
    // Set size to 0
    size = 0;

    // Loops as long i is less than MAXNODESL
    for (int i = 0; i < MAXNODESL; i++) {
        // Has not visited
        node[i].visited = false;

        // Set the edgeHead to null
        node[i].edgeHead = nullptr;

        // Set data's to null
        node[i].data = nullptr;
    }
}

// ------------------------------------ Destructor-----------------------------------------------
// Description: This a destructor
// --------------------------------------------------------------------------------------------------- 
GraphL::~GraphL() {
    // Calls makeEmpty()
    makeEmpty();
}

// ------------------------------------ makeEmpty() -----------------------------------------------
// Description: Helper method for the destructor. 
// This delete the objects.
// --------------------------------------------------------------------------------------------------- 
void GraphL::makeEmpty() {
    // Loops until it reaches size
    for (int i = 1; i <= size; i++) {
        // Has not visited
        node[i].visited = false;

        // Deletes the current node
        delete node[i].data;

        // Set node to null
        node[i].data = nullptr;

        // Loops as long the node is not null
        if (node[i].edgeHead != nullptr) {
            EdgeNode* deleteNode = node[i].edgeHead;

            // Loops as long the node is not null
            while (deleteNode != nullptr) {
                // Set the node to the next node
                node[i].edgeHead = node[i].edgeHead->nextEdge;

                // Deletes the node
                delete deleteNode;

                // Set the node to null
                deleteNode = nullptr;

                // Moves the head
                deleteNode = node[i].edgeHead;
            }
        }
    }
}

// ------------------------------------ buildGraph() -----------------------------------------------
// Description: This a default constructor
// --------------------------------------------------------------------------------------------------- 
void GraphL::buildGraph(ifstream& infile) {
    // Read from data file
    infile >> size;

    // Set nodeName empty
    string nodeName = "";

    // Reads the line of text input
    getline(infile, nodeName);

    // Loops until it reaches the size
    for (int i = 1; i <= size; i++) {
        // Reads the line of text input
        getline(infile, nodeName);

        // Create a temporary node
        NodeData* tempNode = new NodeData(nodeName);

        // Insert it into the array
        node[i].data = tempNode;
    }

    int from;
    int to;

    // Loops as long there from is not empty
    while (infile >> from >> to) {
        if (from == 0) {
            break;
        }

        // If the first node is null
        if (node[from].edgeHead == nullptr) {
            // Create a new edge node
            EdgeNode* nodeEdge = new EdgeNode;

            // Insert the adjacaent
            nodeEdge->adjGraphNode = to;

            // Points to the head
            node[from].edgeHead = nodeEdge;

            // Set to null
            node[from].edgeHead-> nextEdge = nullptr;
        }

        // If the first node is not null
        else {
            // Create a new edge node
            EdgeNode* edgeNode = new EdgeNode;

            // Insert the adjacent
            edgeNode->adjGraphNode = to;

            // Move to the next node
            edgeNode->nextEdge = node[from].edgeHead;

            // Set as head
            node[from].edgeHead = edgeNode;
        }
    }
}

// ------------------------------------ depthFirstSearch() -----------------------------------------------
// Description: Makes a depth-first search and displays each node in depth-first order
// --------------------------------------------------------------------------------------------------- 
void GraphL::depthFirstSearch() {
    cout << "Depth-first ordering:";
    // Loops until it reaches the size
    for (int i = 1; i <= size; i++) {

        // If the node has not been visited
        if (!node[i].visited) {
            // Calls a helper method
            depthFirstSearchHelper(i);
        }
    }
    cout << endl;
}

// ------------------------------------ depthFirstSearchHelper() -----------------------------------------------
// Description: Helper method for depthFirstSearch()
// Recursively looks for the depth
// --------------------------------------------------------------------------------------------------- 
void GraphL::depthFirstSearchHelper(int x) {
    // Prints the node
    cout << setw(5) << x;

    // Set visit to true
    node[x].visited = true;

    // Create a current node set to the head
    EdgeNode* current = node[x].edgeHead;

    // Loops as long the current node is not null
    while (current != nullptr) {
        // If the node has not been visited
        if (!node[current->adjGraphNode].visited) {
            // Call the helper method
            depthFirstSearchHelper(current->adjGraphNode);
        }
        // Moves to the next node
        current = current->nextEdge;
    }
}


// ------------------------------------ displayGraph() -----------------------------------------------
// Description: Displays each node information and edge in the graph
// --------------------------------------------------------------------------------------------------- 
void GraphL::displayGraph() {
    cout << "Graph: ";
    cout << endl;

    // Loops until it reaches size
    for (int i = 1; i <= size; i++) {
        // Prints the index and the node's data
        cout << "Node" << i << "    " << *node[i].data << endl << endl;

        // Create a node to set as current node
        EdgeNode* current = node[i].edgeHead;

        // Loops until current is null
        while (current != nullptr) {
            // Prints the edge
            cout << setw(10) << "edge  " << i << setw(5) << current->adjGraphNode << endl;

            // Moves to the next node
            current = current->nextEdge;
        }
    }
}