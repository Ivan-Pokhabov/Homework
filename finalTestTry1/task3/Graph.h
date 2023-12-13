#pragma once

// Struct of graph
typedef struct Graph Graph;

// Function of creating graph
Graph* createGraph(const int* const* const adjacencyList, const size_t vertexNumber);

// function of getting vertexes that have node that connects them with this vertex
int* getNeigbours(const Graph* const graph, const int vertex);

// Funvtion of deleting graph and free memory
void deleteGraph(Graph** graph);