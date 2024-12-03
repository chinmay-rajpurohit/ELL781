// Main program to run MST algorithms
#include "GraphADT.h"
#include "Prims.h"
#include "Kruskals.h"
#include <chrono>
#include <bits/stdc++.h>
using namespace std;

// Display menu options
void selectoption() {
    cout << "Menu:" << endl;
    cout << "1. Run MST Algo"<<endl;
    cout << "2. Exit" << endl;
    cout << "Enter your choice: "<<endl;
}

int main() {
    // Read input from file
    ifstream input("input.txt");
    Graph* G = create_Graph(input);
    input.close();
    int flag=1;
    int option;

    while(flag==1) {
        selectoption();
        cin>>option;

        // Check if graph is connected
        if(G->Connected==0) {
            cout<<"**MST does not exist**"<<endl;
            break;
        }

        switch(option) {
            case 1: {
                // Run and time Prim's algorithm
                auto startPrim = chrono::high_resolution_clock::now();
                Graph* primMST = PrimsMST(G);
                
                
                // Print MST edges and total cost
                cout << "Prim's MST Edges:\n";
                int totalCost = 0;
                for (int i = 0; i < primMST->size; i++) {
                    cout << "(" << primMST->listOFedges[i].u << " - " 
                        << primMST->listOFedges[i].v<<")"<< "\n";
                    totalCost += primMST->listOFedges[i].weight;
                }
                cout << "Total cost: " << totalCost << endl;
                auto endPrim = chrono::high_resolution_clock::now();
                chrono::duration<double> primDuration = endPrim - startPrim;
                cout << "Prim's Algorithm running time: " << primDuration.count() << " seconds" << endl<<"\n";

                // Free MST memory
                for (int i = 0; i < primMST->vertices; i++) {
                    free(primMST->costMatrix[i]);
                }
                free(primMST->costMatrix);
                delete[] primMST->listOFedges;
                free(primMST);

                // Run and time Kruskal's algorithm
                auto startKruskal = chrono::high_resolution_clock::now();
                cout << "Kruskals's MST Edges:\n";
                int t=KruskalsMST(G);
                for (int i = 0; i < t; i++) 
                {
                    cout <<"("<< G->Kruskals[i].u << " - " << G->Kruskals[i].v <<")" <<"\n";
                }
                auto endKruskal = chrono::high_resolution_clock::now();
                chrono::duration<double> kruskalDuration = endKruskal - startKruskal;
                cout << "Kruskal's Algorithm running time: " << kruskalDuration.count() << " seconds" << endl;
            }
            case 2:{
                 cout << "Exiting the program!!" <<endl;
                 flag=0;
                 break;
            }
        }         
    }
    
    // Free allocated memory
    for (int i = 0; i < G->vertices; i++)
        free(G->costMatrix[i]);
    free(G->costMatrix);
    free(G);

    return 0;
}