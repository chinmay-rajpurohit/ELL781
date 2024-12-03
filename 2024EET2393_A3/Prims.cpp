// Implementation of Prim's MST Algorithm
#include "GraphADT.h"
#include "PriorityQueue.h"
#include <bits/stdc++.h>
using namespace std;

// Function to find Minimum Spanning Tree using Prim's algorithm
Graph* PrimsMST(Graph* G) {
    int V = G->vertices;
    
    // Create new Graph object for MST
    Graph* MST = (Graph*)malloc(sizeof(Graph));
    MST->vertices = V;
    MST->size = 0;
    MST->Connected = G->Connected;
    
    // Allocate and initialize MST's cost matrix
    MST->costMatrix = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        MST->costMatrix[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            MST->costMatrix[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }
    
    // Initialize arrays for Prim's algorithm
    int* parent = new int[V];
    int* key = new int[V];
    bool* inMST = new bool[V];

    for (int i = 0; i < V; i++) {
        parent[i] = -1;
        key[i] = INT_MAX;
        inMST[i] = false;
    }

    // Create priority queue for vertices
    PQueue pq(V);
    pq.insert(0, 0);
    key[0] = 0;

    // Build MST
    while (!pq.isEmpty()) {
        Node node = pq.deleteMin();
        int u = node.v;
        inMST[u] = true;

        for (int v = 0; v < V; v++) {
            if (G->costMatrix[u][v] != -1 && u != v && !inMST[v] && G->costMatrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = G->costMatrix[u][v];

                if (pq.VertexToIndex[v] != -1) {
                    pq.decreaseKey(v, key[v]);
                } else {
                    pq.insert(v, key[v]);
                }
            }
        }
    }

    // Construct MST's cost matrix and edge list
    MST->listOFedges = new edge[V - 1];  // MST has V-1 edges
    int edgeCount = 0;
    
    for (int i = 1; i < V; i++) {
        if (parent[i] != -1) {
            int weight = G->costMatrix[i][parent[i]];
            
            // Update cost matrix (both directions since undirected graph)
            MST->costMatrix[parent[i]][i] = weight;
            MST->costMatrix[i][parent[i]] = weight;
            
            // Add to edge list
            MST->listOFedges[edgeCount].u = parent[i];
            MST->listOFedges[edgeCount].v = i;
            MST->listOFedges[edgeCount].weight = weight;
            edgeCount++;
        }
    }
    
    MST->size = edgeCount;

    // Free allocated memory
    delete[] parent;
    delete[] key;
    delete[] inMST;

    return MST;
}