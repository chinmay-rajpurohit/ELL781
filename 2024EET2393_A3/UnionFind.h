#ifndef UNIONFIND_H
#define UNIONFIND_H
#include <bits/stdc++.h>
using namespace std;

struct DisjointSet {
    int* parent;
    int* rank;

    DisjointSet(int n);
    int find(int u);
    void unite(int u, int v);
    ~DisjointSet();
};

#endif
