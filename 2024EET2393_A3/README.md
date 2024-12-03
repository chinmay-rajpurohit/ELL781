This assignment involves implementing the Prim and Kruskal algorithms for finding a Minimum Spanning Tree (MST) of an undirected weighted graph.

TO RUN this program :
1) Unzip the file
2) Update the input.txt with your cost matrix
3) Compile the program using the provided source files:
   GraphADT.cpp, Kruskals.cpp, Prims.cpp, PriorityQueue.cpp, DisjointSet.cpp, and main.cpp.
   ### command - g++ GraphADT.cpp Kruskals.cpp Prims.cpp PriorityQueue.cpp DisjointSet.cpp main.cpp
   then ./a for running a.exe file. 
Then there will choice to run the MST algorithms or exit the program. 


FILES INCLUDED

GraphADT.h - This file contains the structure definitions and function declarations used to represent a graph and its edges. This header file provides the necessary data types and functions required to create and manage graph representations, such as those used in Minimum Spanning Tree (MST) algorithms like Prim's and Kruskal's algorithms.

PriorityQueue.h - This file provides the declaration of the PQueue class, which includes methods for inserting elements, deleting the minimum element, and decreasing the key of an element. The priority queue is implemented using a binary heap to ensure efficient time complexity for these operations.

Prims.h - This file contains the function declaration for Prim's Minimum Spanning Tree (MST) algorithm. Prim’s algorithm is used to find a subset of the edges that forms a tree including every vertex, where the total weight of the tree is minimized.

main.cpp - This file is the driver program that runs both Prim's and Kruskal's algorithms to compute the Minimum Spanning Tree (MST) of a given graph. The program includes a simple menu system that allows the user to select an option to run the MST algorithms or exit the program.

The program also measures and outputs the execution time of both Prim's and Kruskal's algorithms for performance analysis.

GraphADT.cpp - This file contains the abstract data type for representation and management of graph strcture. This file provides the function create_Graph() that reads a graph from an input file, initializes the cost matrix, and generates the list of edges. This graph representation is used in MST algorithms to compute the minimum spanning tree. This file relies on the GraphADT.h header, which declares the Graph structure and its components, including vertices, edges, and cost matrix.

PriorityQueue.cpp - This file contains an implementation of a priority queue using a binary heap structure. This priority queue is used to efficiently manage and access the minimum key values, which is particularly useful in graph algorithms like Prim’s algorithm for finding the Minimum Spanning Tree (MST).

Prims.cpp - This file contains the implementation of Prim’s Minimum Spanning Tree (MST) algorithm. This algorithm constructs an MST for a weighted, undirected graph, ensuring that the total weight of the selected edges is minimized.

DisjointSet.h - This file contains the class declaration for the Disjoint Set data structure, also known as the Union-Find data structure. It is used to efficiently manage and track the components in a graph, which is particularly useful in algorithms such as Kruskal’s MST algorithm to detect cycles.

Kruskals.h - This file contains the function declaration for Kruskal's Minimum Spanning Tree (MST) algorithm. Kruskal’s algorithm is a greedy algorithm used to find the MST of a graph by sorting the edges and selecting the minimum weight edges that do not form a cycle, until all vertices are connected.

DisjointSet.cpp - This file implements the Disjoint Set (Union-Find) data structure with path compression and union by rank. This data structure is used to efficiently manage the components of a graph, which is particularly useful in algorithms like Kruskal’s MST algorithm to detect and avoid cycles.

Kruskals.cpp - This file implements Kruskal's Minimum Spanning Tree (MST) algorithm. Kruskal’s algorithm is a greedy algorithm that finds the MST of a graph by sorting the edges in ascending order of weight and then adding them to the MST as long as they do not form a cycle, using the Disjoint Set (Union-Find) data structure to manage connected components.

### input example : 
0 6 1 5 -1 -1
6 0 5 -1 3 -1
1 5 0 5 6 4
5 -1 5 0 -1 2
-1 3 6 -1 0 6
-1 -1 4 2 6 0


### output example : 
Menu:
1. Run MST Algo    
2. Exit
Enter your choice: 1
Edge    Weight
(2 - 1)         5 
(0 - 2)         1 
(5 - 3)         2 
(1 - 4)         3 
(2 - 5)         4 
Total cost: 15
Prim's Algorithm running time: 0.0065 seconds

Edge    Weight
(0 - 2)         1
(3 - 5)         2
(1 - 4)         3
(2 - 5)         4
(1 - 2)         5
Total cost: 15
Kruskal's Algorithm running time: 0.003989 seconds
Exiting the program!!


The output includes the edges of the MST and their weights for both Prim's and Kruskal's algorithms, followed by the total cost and running time for each algorithm.






