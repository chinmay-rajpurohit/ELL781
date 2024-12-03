// Graph ADT Implementation
#include "GraphADT.h"
#include <iostream>
#include <limits.h>
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;

// Create an empty graph with given number of vertices
Graph* create_Empty_Graph(int vertices) {
    Graph* G = (Graph*)malloc(sizeof(Graph));
    G->vertices = vertices;
    G->size = 0;
    G->Connected = 1;  // Assume connected until proven otherwise
    
    // Allocate memory for cost matrix
    G->costMatrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        G->costMatrix[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            G->costMatrix[i][j] = (i == j) ? 0 : INT_MAX;  // Initialize with infinity except diagonal
        }
    }
    
    // Allocate memory for edge list (maximum possible edges)
    G->listOFedges = new edge[vertices * (vertices - 1) / 2];
    
    return G;
}

// Create graph from input file (existing function)
Graph* create_Graph(ifstream &input) {
    // Count vertices from first line
    string firstLine;
    int v = 0;

    if (getline(input, firstLine)) {
        bool inNumber = false;
        for (char c : firstLine) {
            if (isdigit(c) && !inNumber) {
                v++;
                inNumber = true;
            }
            else if (!isdigit(c)) {
                inNumber = false;
            }
        }
    }
    input.clear();
    input.seekg(0);

    // Use create_Empty_Graph instead of manual allocation
    Graph* G = create_Empty_Graph(v);

    // Read cost matrix and create edge list
    G->Connected = 0;
    for (int i = 0; i < G->vertices; i++) {
        G->Connected = 0;
        for (int j = 0; j < G->vertices; j++) {
            input >> G->costMatrix[i][j];

            // Check if graph is connected
            if(G->costMatrix[i][j] > 0) {
                G->Connected = 1;
            }
            
            // Convert 0 to INT_MAX for non-adjacent vertices
            if (i != j && G->costMatrix[i][j] == 0) {
                G->costMatrix[i][j] = INT_MAX;
            }

            // Add edge to list (only add each edge once)
            if (G->costMatrix[i][j] != INT_MAX && i < j) {
                G->listOFedges[G->size].u = i;
                G->listOFedges[G->size].v = j;
                G->listOFedges[G->size].weight = G->costMatrix[i][j];
                G->size++;
            }
        }
        // Return early if graph is disconnected
        if(G->Connected == 0) {
            return G;
        }
    }

    return G;
}