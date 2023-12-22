#pragma once
#include <stdlib.h>

#include "List.h"

// Struct of graph
typedef struct Graph Graph;

// Function of creating graph
Graph* createGraph(const size_t vertexNumber);

// Function of adding edge to graph
void addEdge(Graph* const graph, const int vertex1, const int vertex2, const int length);

// function of getting vertexes that have node that connects them with this vertex
List* getNeigbours(const Graph* const graph, const int vertex);

// Funvtion of deleting graph and free memory
void deleteGraph(Graph** graph);