#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include "errors.h"

typedef struct Graph {
    int V;
    int * adjM;
} Graph;

Graph * CreateGraph(int);

#endif
