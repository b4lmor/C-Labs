#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "errors.h"
#include "graph.h"

static int minKey(int V, unsigned int * keys, bool * mstUsed) {
    unsigned min = UINT_MAX;
    int min_index = 0;
    for (int v = 0; v < V; v++) {
        if (keys[v] < min && !mstUsed[v]) {
            min = keys[v];
            min_index = v;
        }
    }
    return min_index;
}

static void PrintMST(int V, int * destinations) {
    for (int i = 1; i < V; i++) {
        printf("%i %i\n", destinations[i] + 1, i + 1);
    }
}

int Prim(Graph * graph) {
    unsigned * keys = malloc(graph->V * sizeof(unsigned));
    if (keys == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }
    for (int i = 1; i < graph->V; i++) {
        keys[i] = UINT_MAX;
    }
    keys[0] = 0;

    int e = 0;
    int * destinations = malloc(graph->V * sizeof(int));
    if (destinations == NULL) {
        free(keys);
        return MEMORY_ALLOCATION_ERROR;
    }
    destinations[0] = -1;
    bool * mstUsed = calloc(graph->V, sizeof(bool));
    if (mstUsed == NULL) {
        free(keys);
        free(destinations);
        return MEMORY_ALLOCATION_ERROR;
    }

    for (int i = 0; i < graph->V; i++) {
        int u = minKey(graph->V, keys, mstUsed);
        e += !mstUsed[u];
        mstUsed[u] = true;
        for (int v = 0; v < graph->V; v++) {
            if (graph->adjM[graph->V * u + v] > 0 &&
                !mstUsed[v]                       &&
                keys[v] > graph->adjM[graph->V * u + v]) {
                    keys[v] = graph->adjM[graph->V * u + v];
                    destinations[v] = u;
                }
        }
    }
    if (e != graph->V) {
        free(keys);
        free(mstUsed);
        free(destinations);
        return NO_SPANNING_TREE;
    } else {
        PrintMST(graph->V, destinations);
        free(keys);
        free(mstUsed);
        free(destinations);
        return EXIT_SUCCESS;
    }
}
