#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Edge {
	int src;
	int dest;
	int weight;
} Edge;

typedef struct Graph {
	Edge * edge;
	int V;
	int E;
} Graph;

Graph * createGraph(int V, int E) {

	Graph * graph = malloc(sizeof(Graph));
	if (graph == NULL) {
		return NULL;
	}
	graph->V = V;
	graph->E = E;
	graph->edge = (struct Edge *) malloc(graph->E * sizeof(Edge));
	if (graph->edge == NULL) {
		free(graph);
		return NULL;
	}

	return graph;
}

typedef struct subset {
	int parent;
	int rank;
} subset;

int find(subset * subsets, int i){

	if (subsets[i].parent != i){
		subsets[i].parent = find(subsets, subsets[i].parent);
    }
	return subsets[i].parent;
}

void Union(subset * subsets, int x, int y) {
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);

	if (subsets[xroot].rank < subsets[yroot].rank) {
		subsets[xroot].parent = yroot;
	} else if (subsets[xroot].rank > subsets[yroot].rank) {
		subsets[yroot].parent = xroot;
	} else {
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}

int CompareEdges(const void * edge1_void, const void * edge2_void) {
    return ( ((const Edge *) edge1_void)->weight -
             ((const Edge *) edge2_void)->weight );
} 

void Kruskal(Graph * graph) {
	int V = graph->V;
	int E = graph->E;
	Edge * result = malloc((V - 1) * sizeof(Edge));
	if (result == NULL) {
		return;
	}

	int e = 0, i = 0;

	qsort(graph->edge, graph->E, sizeof(graph->edge[0]), CompareEdges);

	subset * subsets = malloc(V * sizeof(subset));
	if (subsets == NULL) {
		free(result);
		return;
	} 

	for (int v = 0; v < V; v++){
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}

	while ( (e < V - 1) && (i < E) ) {

		Edge next_edge = graph->edge[i++];

		int x = find(subsets, next_edge.src);
		int y = find(subsets, next_edge.dest);

		if (x != y) {
			result[e++] = next_edge;
			Union(subsets, x, y);
		}
	}

    if (e == V - 1) {
	    for (i = 0; i < e; i++){
	    	printf("%d %d\n", result[i].src + 1, result[i].dest + 1);
		}
    } else {
        printf("no spanning tree\n");
    }

	free(result);
	free(subsets);
}

int main(void) {
    int V, E;

    if (1 != scanf("%i", &V)){
        return EXIT_FAILURE;
    }
    if (0 > V || V > 5000) {
        printf("bad number of vertices\n");
        return EXIT_SUCCESS;
    }

    if (1 != scanf("%i", &E)){
        return EXIT_FAILURE;
    }
    if (0 > E || E > V * (V - 1) / 2) {
        printf("bad number of edges\n");
        return EXIT_SUCCESS;
    }
    
	if ((E < V - 1) || (E == 0 && V == 0)) {
        printf("no spanning tree\n");
        return EXIT_SUCCESS;
    }

    Graph * graph = createGraph(V, E);
	if (graph == NULL) {
		return EXIT_FAILURE;
	}

    for (int i = 0; i < E; i++){
		long long bufWeight;
    	int src, dst;
        if (3 != scanf("%i %i %lli", &src, &dst, &bufWeight)){
            printf("bad number of lines\n");
            goto exit_marker;
        }
        if ( (0 > src || src > V) || (0 > dst|| dst > V) ) {
            printf("bad vertex\n");
            goto exit_marker;
        }
        if (0 > bufWeight || bufWeight > INT_MAX) {
            printf("bad length\n");
            goto exit_marker;
        }

        graph->edge[i].src = src - 1;
	    graph->edge[i].dest = dst - 1;
	    graph->edge[i].weight = (int) bufWeight;
    }

	Kruskal(graph);

	exit_marker:

    free(graph->edge);
    free(graph);
	return EXIT_SUCCESS;
}
