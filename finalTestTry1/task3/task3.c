#include <stdio.h>
#include <stdbool.h>

#include "Graph.h"

#define VERTEX_NUMBER 3

void dfs(const int vertex, const Graph* const graph, bool** visited, const size_t vertexNumber, size_t* vertexCount)
{
    if ((*visited)[vertex])
    {
        return;
    }
    (*visited)[vertex] = true;
    ++(*vertexCount);
    int* neighbours = getNeigbours(graph, vertex);
    for (size_t i = 0; i < vertexNumber; ++i)
    {
        if (neighbours[i] == -1)
        {
            break;
        }
        dfs(neighbours[i], graph, visited, vertexNumber, vertexCount);
    }
}

int main()
{
    int** adjacencyList = (int**)calloc(VERTEX_NUMBER, sizeof(int*));
    if (adjacencyList == NULL)
    {
        return -1;
    }
    for (size_t i = 0; i < VERTEX_NUMBER; ++i)
    {
        adjacencyList[i] = (int*)calloc(VERTEX_NUMBER, sizeof(int));
        if (adjacencyList[i] == NULL)
        {
            for (size_t j = 0; j < i; ++j)
            {
                free(adjacencyList[j]);
            }
            free(adjacencyList);
            return -1;
        }
        for (size_t j = 0; j < VERTEX_NUMBER; ++j)
        {
            adjacencyList[i][j] = -1;
        }
    }
    adjacencyList[0][0] = 1;
    adjacencyList[0][1] = 2;
    Graph* graph = createGraph(adjacencyList, VERTEX_NUMBER);
    bool* visited = (bool*)calloc(VERTEX_NUMBER, sizeof(bool));
    for (int i = 0; i < VERTEX_NUMBER; ++i)
    {
        size_t vertexCount = 0;
        if (visited[i])
        {
            continue;
        }
        dfs(i, graph, &visited, VERTEX_NUMBER, &vertexCount);
        if (vertexCount == VERTEX_NUMBER)
        {
            printf("%d ", i + 1);
        }
        for (size_t i = 0; i < VERTEX_NUMBER; ++i)
        {
            visited[i] = false;
        }
    }
    deleteGraph(&graph);
}
