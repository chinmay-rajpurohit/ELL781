#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <bits/stdc++.h>
using namespace std;
struct Node {
    int v;
    int k;
};

struct PQueue {
    Node* N;
    int* VertexToIndex;
    int capacity;
    int size;

    PQueue(int maxSize);
    ~PQueue();
    void swap(int i, int j);
    void heapifyUp(int i);
    void heapifyDown(int i);
    void insert(int vertex, int key);
    Node deleteMin();
    void decreaseKey(int vertex, int newKey);
    bool isEmpty();
};

#endif
