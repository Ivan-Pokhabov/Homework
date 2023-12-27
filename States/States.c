#include <stdio.h>
#include <stdlib.h>

#include "../BinaryHeap/BinaryHeap.h"
#include "Graph.h"
#include "List.h"

void dijkstra(const int* const starts, const size_t startsNumber, Graph* graph, int* const distances, int* const colours)
{
    BinaryHeap* heap = createHeap();
    for (size_t i = 0; i < startsNumber; ++i)
    {
        colours[starts[i]] = starts[i];
        distances[starts[i]] = 0;
        add(heap, 0, starts[i]);
    }
    while (!isEmpty(heap))
    {
        int vertex = 0;
        int distance = 0;
        pop(heap, &distance, &vertex);
        if (distance > distances[vertex])
        {
            continue;
        }
        List* neighbours = getNeighbours(graph, vertex);
        ListElement* neighbour = getFirst(neighbours);
        while (neighbour != NULL)
        {
            int neighbourNumber = 0;
            int length = 0;
            getData(neighbour, &neighbourNumber, &length);
            if (distances[neighbourNumber] > distance + length || distances[neighbourNumber] == -1)
            {
                add(heap, distance + length, neighbourNumber);
                distances[neighbourNumber] = distance + length;
                colours[neighbourNumber] = colours[vertex];
            }
            neighbour = nextElement(neighbour);
        }
    }
    deleteHeap(&heap);
}

int readData(char* fileName, size_t* const vertexNumber, Graph** graph, int** capitals, size_t* const capitalsNumber)
{
    if (*capitals != NULL || *graph != NULL)
    {
        return -1;
    }
    FILE* file = NULL;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        return -2;
    }
    if (fscanf_s(file, "%lld", vertexNumber) == 0)
    {
        return -3;
    }
    size_t edgesNumber = 0;
    if (fscanf_s(file, "%lld", &edgesNumber) == 0)
    {
        return -3;
    }
    *graph = createGraph(*vertexNumber);
    for (size_t i = 0; i < edgesNumber; ++i)
    {
        int vertex1 = 0;
        int vertex2 = 0;
        size_t edgeLength = 0; 
        if (fscanf_s(file, "%d %d %lld", &vertex1, &vertex2, &edgeLength) != 3)
        {
            return -3;
        }
        --vertex1;
        --vertex2;
        addEdge(*graph, vertex1, vertex2, edgeLength);
        addEdge(*graph, vertex2, vertex1, edgeLength);
    }
    if (fscanf_s(file, "%lld", capitalsNumber) == 0)
    {
        return -3;
    }
    *capitals = (int*)calloc(*capitalsNumber, sizeof(int)); 
    if (*capitals == NULL)
    {
        return -4;
    }
    for (size_t i = 0; i < *capitalsNumber; ++i)
    {
        int vertex = 0;
        if (fscanf_s(file, "%d", &vertex) == 0)
        {
            return -3;
        }
        (*capitals)[i] = vertex - 1;
    }
    return 0;
    fclose(file);
}

int main()
{
    Graph* graph = NULL;
    size_t vertexNumber = 0;
    int* capitals = NULL;
    size_t capitalsNumber = 0;
    ErrorCode errorCode = readData("input.txt", &vertexNumber, &graph, &capitals, &capitalsNumber);
    if (errorCode != 0)
    {
        return errorCode;
    }
    int* distances = (int*)calloc(vertexNumber, sizeof(int));
    int* colours = (int*)calloc(vertexNumber, sizeof(int));
    for (size_t i = 0; i < vertexNumber; ++i)
    {
        distances[i] = -1;
        colours[i] = -1;
    }
    dijkstra(capitals, capitalsNumber, graph, distances, colours);
    for (size_t capital = 0; capital < capitalsNumber; ++capital)
    {
        printf("State %lld: ", capital + 1);
        for (size_t node = 0; node < vertexNumber; ++node)
        {
            if (colours[node] == capital)
            {
                printf("%lld ", node + 1);
            }
        }
        printf("\n");
    }
    free(capitals);
    free(distances);
    free(colours);
    deleteGraph(&graph);
}
