#include <stdlib.h>

#include "Graph.h"
#include "List.h"

struct Graph
{
    List** graph;
    size_t vertexNumber;
};

Graph* createGraph(const size_t vertexNumber)
{
    Graph* graph = (Graph*)calloc(1, sizeof(graph));
    if (graph == NULL)
    {
        return NULL;
    }
    graph->graph = (List**)calloc(vertexNumber, sizeof(List*));
    if (graph->graph == NULL)
    {
        free(graph);
        return NULL;
    }
    for (size_t i = 0; i < vertexNumber; ++i)
    {
        (graph->graph)[i] = createList();
    }
    graph->vertexNumber = vertexNumber; 
    return graph;
}

void addEdge(Graph* const graph, const int vertex1, const int vertex2, const int length)
{
    addList((graph->graph)[vertex1], vertex2, length);
}

List* getNeigbours(const Graph* const graph, const int vertex)
{
    return (graph->graph)[vertex];
}

void deleteGraph(Graph** graph)
{
    for (size_t i = 0; i < (*graph)->vertexNumber; ++i)
    {
        deleteList(&((*graph)->graph)[i]);
    }
    free(*graph);
    *graph = NULL;
}