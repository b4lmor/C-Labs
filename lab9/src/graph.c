#include "graph.h"

Graph * CreateGraph(int V) {
	Graph * graph = malloc(sizeof(Graph));
	if (graph == NULL) {
		return NULL;
	}

	graph->V = V;
	graph->adjM = calloc(V * V, sizeof(int));
	if (graph->adjM == NULL) {
		free(graph);
		return NULL;
	}

	return graph;
}
