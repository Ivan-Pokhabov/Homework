#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

int makeAdjacencyList(int*** graph, const size_t edgesNumber, const size_t vertexNumber, const int matrix[3][3])
{
    int** edges = (int**)calloc(edgesNumber, sizeof(int*));
    if (edges == NULL)
    {
        return -1;
    }
    for (size_t i = 0; i < edgesNumber; ++i)
    {
        edges[i] = (int*)calloc(vertexNumber, sizeof(int));
        if (edges[i] == NULL)
        {
            return -1;
        }
        for (size_t j = 0; j < vertexNumber; ++j)
        {
            edges[i][j] = -1;
        }
    }
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            if (matrix[i][j] == 1)
            {
                for (size_t k = 0; k < 3; ++k)
                {
                    if (edges[j][k] == -1)
                    {
                        edges[j][k] = i;
                        break;
                    }
                    else
                    {
                        for (size_t h = 0; h < 3; ++h)
                        {
                            if ((*graph)[i][h] == -1)
                            {
                                (*graph)[i][h] = edges[j][k];
                                break;
                            }
                        }
                        for (size_t h = 0; h < 3; ++h)
                        {
                            if ((*graph)[edges[j][k]][h] == -1)
                            {
                                (*graph)[edges[j][k]][h] = i;
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
}

int main()
{
    const int matrix[3][3] = { {1, 0, 0}, {1, 0, 0}, {0, 0, 0} };
    int** graph = (int**)calloc(3, sizeof(int*));
    if (graph == NULL)
    {
        return -1;
    }
    for (size_t i = 0; i < 3; ++i)
    {
        graph[i] = (int*)calloc(3, sizeof(int));
        if (graph[i] == NULL)
        {
            return -1;
        }
        for (size_t j = 0; j < 3; ++j)
        {
            graph[i][j] = -1;
        }
    }
    makeAdjacencyList(&graph, 3, 3, matrix);
    bool* visited = (bool*)calloc(3, sizeof(bool));
    size_t countComponents = 1;
    for (int i = 0; i < 3; ++i)
    {
        if (visited[i])
        {
            continue;
        }
        printf("Component %d, vertexes - ", countComponents + 1);
        dfs(i, graph, &visited, 3);
        printf("\n");
        ++countComponents;
    }
    for (size_t i = 0; i < 3; ++i)
    {
        free(graph[i]);
    }
    free(graph);
    free(visited)
}

