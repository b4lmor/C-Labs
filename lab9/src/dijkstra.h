#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include "errors.h"
#include "heap_pq.h"
#include "graph.h"

int Dijkstra(int, Graph *, uint64_t *);

#endif
