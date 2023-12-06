#include <stdio.h>
#include <stdlib.h>

#include "../BinaryHeap/BinaryHeap.h"

enum ErrorCode
{
    ok = 0,
    incorrectVariales = -1,
    fileDidNotOpened = -2,
    incorrectInputFile = -3,
    memoryError = -4
};

void dijkstra(int* starts, const size_t startsNumber, const int* const * const graph, const size_t* const * const edgesLength, const size_t* const neighboursNumber, int* const distances, int* const colours)
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
        for (size_t i = 0; i < neighboursNumber[vertex]; ++i)
        {
            const int neighbour = graph[vertex][i];
            const size_t edge = edgesLength[vertex][i];
            if (distance + edge < distances[neighbour] || distances[neighbour] == -1)
            {
                distances[neighbour] = distance + edge;
                colours[neighbour] = colours[vertex];
                add(heap, distances[neighbour], neighbour);
            }
        }
    }
}

int readData(char* fileName, size_t* const vertexNumber, int*** graph, size_t*** edges, size_t** neighbours, int** capitals, size_t* capitalsNumber)
{
    if (*graph != NULL || *edges != NULL || *neighbours != NULL || *capitals != NULL)
    {
        return incorrectVariales;
    }
    FILE* file = NULL;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        return fileDidNotOpened;
    }
    if (fscanf_s(file, "%lld", vertexNumber) == 0)
    {
        return incorrectInputFile;
    }
    size_t edgesNumber = 0;
    if (fscanf_s(file, "%lld", &edgesNumber) == 0)
    {
        return incorrectInputFile;
    }
    *graph = (int**)calloc(*vertexNumber, sizeof(int*));
    *edges = (size_t**)calloc(*vertexNumber, sizeof(size_t*));
    *neighbours = (size_t*)calloc(*vertexNumber, sizeof(size_t));
    if (*graph == NULL || *edges == NULL || *neighbours == NULL)
    {
        return memoryError;
    }
    for (size_t i = 0; i < *vertexNumber; ++i)
    {
        (*graph)[i] = (int*)calloc(*vertexNumber, sizeof(int));
        (*edges)[i] = (int*)calloc(*vertexNumber, sizeof(size_t));
        if ((*graph)[i] == NULL || (*edges)[i] == NULL)
        {
            return memoryError;
        }
    }
    for (size_t i = 0; i < edgesNumber; ++i)
    {
        int vertex1 = 0;
        int vertex2 = 0;
        size_t edgeLength = 0; 
        if (fscanf_s(file, "%d %d %lld", &vertex1, &vertex2, &edgeLength) != 3)
        {
            return incorrectInputFile;
        }
        --vertex1;
        --vertex2;
        (*graph)[vertex1][(*neighbours)[vertex1]] = vertex2;
        (*edges)[vertex1][(*neighbours)[vertex1]] = edgeLength;
        ++(*neighbours)[vertex1];
        (*graph)[vertex2][(*neighbours)[vertex2]] = vertex1;
        (*edges)[vertex2][(*neighbours)[vertex2]] = edgeLength;
        ++(*neighbours)[vertex2];
    }
    if (fscanf_s(file, "%lld", capitalsNumber) == 0)
    {
        return incorrectInputFile;
    }
    *capitals = (int*)calloc(*capitalsNumber, sizeof(int));
    if (capitals == NULL)
    {
        return memoryError;
    }
    for (size_t i = 0; i < *capitalsNumber; ++i)
    {
        int vertex = 0;
        if (fscanf_s(file, "%d", &vertex) == 0)
        {
            return incorrectInputFile;
        }
        (*capitals)[i] = vertex - 1;
    }
    return ok;
}

int main()
{
    int** graph = NULL;
    size_t vertexNumber = 0;
    size_t** edgesLength = NULL;
    size_t* neighbours = NULL;
    int* capitals = NULL;
    size_t capitalsNumber = 0;
    ErrorCode errorCode = readData("input.txt", &vertexNumber, &graph, &edgesLength, &neighbours, &capitals, &capitalsNumber);
    if (errorCode != ok)
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
    dijkstra(capitals, capitalsNumber, graph, edgesLength, neighbours, distances, colours);
    for (size_t capital = 0; capital < capitalsNumber; ++capital)
    {
        printf("State %lld: ", capital + 1);
        for (size_t node = 0; node < vertexNumber; ++node)
        {
            if (colours[node] == capital)
            {
                printf("%lld ", node);
            }
        }
        printf("\n");
    }
    for (size_t i = 0; i < vertexNumber; ++i)
    {
        free(graph[i]);
        free(edgesLength[i]);
    }
    free(graph);
    free(edgesLength);
    free(neighbours);
    free(capitals);
    free(distances);
    free(colours);
}
