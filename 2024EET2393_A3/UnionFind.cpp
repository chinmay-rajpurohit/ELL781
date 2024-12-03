// Implementation of Disjoint Set data structure for Kruskal's Algorithm
#include "UnionFind.h"
#include <bits/stdc++.h>
using namespace std;

// Constructor: Initialize disjoint set with n elements
// Each element starts as its own set with rank 0
DisjointSet::DisjointSet(int n) {
    parent = new int[n];     // Array to store parent pointers
    rank = new int[n];       // Array to store rank of trees
    for (int i = 0; i < n; i++) {
        parent[i] = i;       // Each element is its own parent initially
        rank[i] = 0;         // Initial rank is 0
    }
}

// Find set of an element u with path compression
// Returns the root (representative) of the set containing u
int DisjointSet::find(int u) {
    // If not root, recursively find root and compress path
    if (u != parent[u])
        parent[u] = find(parent[u]);    // Path compression
    return parent[u];
}

// Union by rank: Unite two sets containing elements u and v
void DisjointSet::unite(int u, int v) {
    int rootU = find(u);     // Find root of u's tree
    int rootV = find(v);     // Find root of v's tree

    // If elements are in different sets
    if (rootU != rootV) {
        // Attach smaller rank tree under root of higher rank tree
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } 
        else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        }
        // If ranks are same, make one as root and increment its rank
        else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

// Destructor: Free allocated memory
DisjointSet::~DisjointSet() {
    delete[] parent;
    delete[] rank;
}
