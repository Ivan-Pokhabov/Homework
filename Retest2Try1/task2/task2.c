#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MEMEORY_ERROR -1
#define VERTEX_NUMBER 3
#define EDGES_NUMBER 3

void dfs(const int vertex, const int* const* const graph, bool** visited, const size_t vertexNumber)
{
    if ((*visited)[vertex])
    {
        return;
    }
    (*visited)[vertex] = true;
    printf("%d ", vertex);
    for (size_t i = 0; i < vertexNumber; ++i)
    {
        if (graph[vertex][i] == -1)
        {
            break;
        }
        dfs(graph[vertex][i], graph, visited, vertexNumber);
    }
}

int makeAdjacencyList(int*** adjacencyList, const size_t edgesNumber, const size_t vertexNumber, const int matrix[VERTEX_NUMBER][EDGES_NUMBER])
{
    int** graph = (int**)calloc(VERTEX_NUMBER, sizeof(int*));
    if (graph == NULL)
    {
        return -1;
    }
    for (size_t i = 0; i < VERTEX_NUMBER; ++i)
    {
        graph[i] = (int*)calloc(VERTEX_NUMBER, sizeof(int));
        if (graph[i] == NULL)
        {
            for (size_t j = 0; j < i; ++j)
            {
                free(graph[j]);
            }
            free(graph);
            return -1;
        }
        for (size_t j = 0; j < VERTEX_NUMBER; ++j)
        {
            graph[i][j] = -1;
        }
    }
    int** edges = (int**)calloc(edgesNumber, sizeof(int*));
    if (edges == NULL)
    {
        return MEMEORY_ERROR;
    }
    for (size_t i = 0; i < edgesNumber; ++i)
    {
        edges[i] = (int*)calloc(vertexNumber, sizeof(int));
        if (edges[i] == NULL)
        {
            for (size_t j = 0; j < i; ++j)
            {
                free(edges[j]);
            }
            free(edges);
            return MEMEORY_ERROR;
        }
        for (size_t j = 0; j < vertexNumber; ++j)
        {
            edges[i][j] = -1;
        }
    }
    for (size_t i = 0; i < vertexNumber; ++i)
    {
        for (size_t j = 0; j < edgesNumber; ++j)
        {
            if (matrix[i][j] == 1)
            {
                for (size_t k = 0; k < vertexNumber; ++k)
                {
                    if (edges[j][k] == -1)
                    {
                        edges[j][k] = i;
                        break;
                    }
                    else
                    {
                        for (size_t h = 0; h < vertexNumber; ++h)
                        {
                            if (graph[i][h] == -1)
                            {
                                graph[i][h] = edges[j][k];
                                break;
                            }
                        }
                        for (size_t h = 0; h < vertexNumber; ++h)
                        {
                            if (graph[edges[j][k]][h] == -1)
                            {
                                graph[edges[j][k]][h] = i;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    for (size_t i = 0; i < edgesNumber; ++i)
    {
        free(edges[i]);
    }
    free(edges);
    *adjacencyList = graph;
    return 0;
}

int main()
{
    const int matrix[VERTEX_NUMBER][EDGES_NUMBER] = { {1, 0, 0}, {1, 0, 0}, {0, 0, 0} };
    int** graph = NULL;
    if (makeAdjacencyList(&graph, EDGES_NUMBER, VERTEX_NUMBER, matrix) != 0)
    {
        for (size_t i = 0; i < VERTEX_NUMBER; ++i)
        {
            free(graph[i]);
        }
        free(graph);
        return MEMEORY_ERROR;
    }
    bool* visited = (bool*)calloc(VERTEX_NUMBER, sizeof(bool));
    size_t countComponents = 1;
    for (int i = 0; i < VERTEX_NUMBER; ++i)
    {
        if (visited[i])
        {
            continue;
        }
        printf("Component %d, vertexes - ", countComponents);
        dfs(i, graph, &visited, VERTEX_NUMBER);
        printf("\n");
        ++countComponents;
    }
    for (size_t i = 0; i < VERTEX_NUMBER; ++i)
    {
        free(graph[i]);
    }
    free(graph);
    free(visited);
}

