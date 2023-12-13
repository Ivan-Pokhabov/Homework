#include <stdlib.h>

#include "Graph.h"

struct Graph
{
    int** graph;
    size_t vertexNumber;
};

Graph* createGraph(const int* const* const adjacencyList, const size_t vertexNumber)
{
    if (adjacencyList == NULL)
    {
        return NULL;
    }
    Graph* graph = (Graph*)calloc(1, sizeof(graph));
    graph->graph = adjacencyList;
    graph->vertexNumber = vertexNumber;
    return graph;
}

int* getNeigbours(const Graph* const graph, const int vertex)
{
    return (graph->graph)[vertex];
}

void deleteGraph(Graph** graph)
{
    for (size_t i = 0; i < (*graph)->vertexNumber; ++i)
    {
        free((*graph)->graph[i]);
    }
    free(*graph);
    *graph = NULL;
}