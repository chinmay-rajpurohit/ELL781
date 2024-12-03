#ifndef GRAPHADT_H
#define GRAPHADT_H
#include <bits/stdc++.h>
using namespace std;


struct edge {
    int u;
    int v;
    int weight;
};

struct Graph {
    int size;
    int vertices;
    int** costMatrix;
    edge* listOFedges;
    int Connected;
    edge* Kruskals;
};

Graph* create_Graph(ifstream &input);

#endif
