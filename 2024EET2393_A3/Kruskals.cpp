// Implementation of Kruskal's MST Algorithm
#include "GraphADT.h"
#include "UnionFind.h"
#include <bits/stdc++.h>
using namespace std;

// Forward declarations
void merge(edge arr[], int left, int mid, int right);
void mergeSort(edge arr[], int left, int right);
// Function to find Minimum Spanning Tree using Kruskal's algorithm
int KruskalsMST(Graph* G) {
    // Sort edges by weight
    mergeSort(G->listOFedges, 0, G->size - 1);

    // Create disjoint set for cycle detection
    DisjointSet ds(G->vertices);

    // Arrays to store MST
    edge* mst = new edge[G->vertices - 1];
    int Size = 0;
    int totalCost = 0;
    G->Kruskals=(edge*)malloc(G->size * sizeof(edge));

    // Process edges in sorted order
    for (int i = 0; i < G->size; i++) {
        int u = G->listOFedges[i].u;
        int v = G->listOFedges[i].v;
        if (G->listOFedges[i].weight != -1) {
            // Check if adding edge creates cycle
            if (ds.find(u) != ds.find(v)) {
                ds.unite(u, v);
                G->Kruskals[Size]= G->listOFedges[i];
                Size++;
                totalCost += G->listOFedges[i].weight;
            }

            // Stop if MST is complete
            if (Size == G->vertices - 1)
                break;
        }
    }

    cout << "Total cost: " << totalCost << endl;
   
    delete[] mst;
    return Size;
}

// Merge two sorted subarrays
void merge(edge arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;


    // Create temporary arrays
    edge* leftArray = new edge[n1];
    edge* rightArray = new edge[n2];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        leftArray[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        rightArray[i] = arr[mid + 1 + i];

    // Merge temporary arrays back
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i].weight <= rightArray[j].weight) {
            arr[k] = leftArray[i];
            i++;
        } else {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements
    while (i < n1) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }

    delete[] leftArray;
    delete[] rightArray;
}

// Recursive merge sort
void mergeSort(edge arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}