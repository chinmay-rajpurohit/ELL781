// Priority Queue implementation for Prim's MST algorithm
#include "PriorityQueue.h"
#include <bits/stdc++.h>
using namespace std;

// Constructor: Initialize priority queue with given maximum size
PQueue::PQueue(int maxSize) {
    capacity = maxSize;
    N = new Node[capacity];             // Array to store nodes
    VertexToIndex = new int[capacity];  // Maps vertex to its index in heap
    size = 0;
    for (int i = 0; i < capacity; i++) {
        VertexToIndex[i] = -1;          // Initialize mapping as invalid
    }
}

// Destructor: Free allocated memory
PQueue::~PQueue() {
    delete[] N;
    delete[] VertexToIndex;
}

// Swap two nodes in the heap and update their mappings
void PQueue::swap(int i, int j) {
    Node temp = N[i];
    N[i] = N[j];
    N[j] = temp;
    VertexToIndex[N[i].v] = i;
    VertexToIndex[N[j].v] = j;
}

// Maintain heap property by moving node up
void PQueue::heapifyUp(int i) {
    while (i > 0 && N[(i - 1) / 2].k > N[i].k) {
        swap(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

// Maintain heap property by moving node down
void PQueue::heapifyDown(int i) {
    int minIndex = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Find smallest among root, left and right
    if (left < size && N[left].k < N[minIndex].k)
        minIndex = left;

    if (right < size && N[right].k < N[minIndex].k)
        minIndex = right;

    // If smallest is not root
    if (minIndex != i) {
        swap(i, minIndex);
        heapifyDown(minIndex);
    }
}

// Insert new vertex with given key
void PQueue::insert(int vertex, int key) {
    if (size == capacity) {
        std::cout << "Priority queue is full" << std::endl;
        return;
    }
    N[size] = {vertex, key};
    VertexToIndex[vertex] = size;
    heapifyUp(size);
    size++;
}

// Remove and return node with minimum key
Node PQueue::deleteMin() {
    if (size == 0) {
        return {-1, INT_MAX};
    }

    Node min = N[0];
    N[0] = N[size - 1];
    VertexToIndex[N[0].v] = 0;
    size--;
    VertexToIndex[min.v] = -1;

    if (size > 0) {
        heapifyDown(0);
    }

    return min;
}

// Decrease key of given vertex to new value
void PQueue::decreaseKey(int vertex, int newKey) {
    int i = VertexToIndex[vertex];
    if (i != -1 && newKey < N[i].k) {
        N[i].k = newKey;
        heapifyUp(i);
    }
}

// Check if queue is empty
bool PQueue::isEmpty() {
    return size == 0;
}
