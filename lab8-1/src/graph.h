#ifndef GRAPH_H
#define GRAPH_H

typedef struct Edge {
	int src;
	int dest;
	unsigned weight;
} Edge;

typedef struct Graph {
	unsigned * adjM;
	int V;
	int E;
} Graph;

Graph * CreateGraph(int, int);

#endif
