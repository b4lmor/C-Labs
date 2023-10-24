#include <stdlib.h>

#include "graph.h"

Graph * CreateGraph(int V, int E) {
	Graph * graph = malloc(sizeof(Graph));
	if (graph == NULL) {
		return NULL;
	}

	graph->V = V;
	graph->E = E;
	graph->adjM = calloc(V * V, sizeof(int));
	if (graph->adjM == NULL) {
		free(graph);
		return NULL;
	}

	return graph;
}
