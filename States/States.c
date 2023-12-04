﻿#include <stdio.h>
#include <stdlib.h>

#include "../BinaryHeap/BinaryHeap.h"

#define VERTEX_NUMBER 100

void dijkstra(int start, const int graph[][VERTEX_NUMBER], const size_t edgesLength[][VERTEX_NUMBER], const size_t* const neighboursNumber, int* const distances, int* const from)
{
    distances[start] = 0;
    from[start] = start;
    BinaryHeap* heap = createHeap();
    add(heap, 0, start);
    while (!isEmpty(heap))
    {
        int vertex = 0;
        int distance = 0;
        pop(heap, &distance, &vertex);
        if (distance > distances[vertex])
        {
            continue;
        }
        for (size_t i = 0; i < neighboursNumber[vertex]; ++i)
        {
            const int neighbour = graph[vertex][i];
            const size_t edge = edgesLength[vertex][i];
            if (distance + edge < distances[neighbour] || distances[neighbour] == -1)
            {
                distances[neighbour] = distance + edge;
                from[neighbour] = vertex;
                add(heap, distances[neighbour], neighbour);
            }
        }
    }
}

int main()
{
    int graph[VERTEX_NUMBER][VERTEX_NUMBER] = { {1, 3}, {0, 4, 2}, {1, 3, 4}, {0, 2}, {1, 2} };
    size_t roads[VERTEX_NUMBER][VERTEX_NUMBER] = { {2, 1}, {2, 5, 4}, {4, 3, 1}, {1, 3}, {5, 1} };
    int distances[VERTEX_NUMBER] = { -1, -1, -1, -1, -1 };
    size_t neighbours[VERTEX_NUMBER] = { 2, 3, 3, 2, 2 };
    int from[VERTEX_NUMBER] = { -1, -1, -1, -1, -1 };
    dijkstra(0, graph, roads, neighbours, distances, from);
    int vertex = 4;
    int way[VERTEX_NUMBER] = { -1, -1, -1, -1, -1 };
    size_t wayIndex = 0;
    while (vertex != from[vertex] && from[vertex] != -1)
    {
        way[wayIndex] = vertex;
        vertex = from[vertex];
        ++wayIndex;
    }
    way[wayIndex] = vertex;
    for (size_t i = wayIndex; i + 1 >= 1; --i)
    {
        printf("%d ", way[i] + 1);
    }
}
