#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "errors.h"
#include "graph.h"
#include "prim.h"

#define IsGoodError(ExitCode) (300 < ExitCode && ExitCode < 400)

int main(void) {
    int ExitCode = EXIT_SUCCESS;
    int V, E;

    if (1 != scanf("%i", &V)){
        ExitCode = READ_ERROR;
        goto exit_marker;
    }
    if (0 > V || V > 5000) {
        ExitCode = BAD_NUMBER_OF_VERTICES;
        goto exit_marker;
    }

    if (1 != scanf("%i", &E)){
        ExitCode = READ_ERROR;
        goto exit_marker;
    }
    if (0 > E || E > V * (V - 1) / 2) {
        ExitCode = BAD_NUMBER_OF_EDGES;
        goto exit_marker;
    }
    
	if ((E < V - 1) || (E == 0 && V == 0)) {
        ExitCode = NO_SPANNING_TREE;
        goto exit_marker;
    } else if (E == 0 && V == 1) {
        ExitCode = EXIT_SUCCESS;
        goto exit_marker;
    }

    Graph * graph = CreateGraph(V, E);
	if (graph == NULL) {
        ExitCode = MEMORY_ALLOCATION_ERROR;
		goto exit_marker;
	}

    for (int i = 0; i < E; i++){
		unsigned weight;
    	int src, dst;
        if (3 != scanf("%i %i %u", &src, &dst, &weight)){
            ExitCode = BAD_NUMBER_OF_LINES;
            free(graph->adjM);
            free(graph);
            goto exit_marker;
        }
        if ( (0 > src || src > V) || (0 > dst|| dst > V) ) {
            ExitCode = BAD_VERTEX;
            free(graph->adjM);
            free(graph);
            goto exit_marker;
        }
        if (weight > INT_MAX) {
            ExitCode = BAD_LENGTH;
            free(graph->adjM);
            free(graph);
            goto exit_marker;
        }

        src -= 1; // - Узлы будут нумероваться не с 1, а с 0
        dst -= 1;

	    graph->adjM[V * src + dst] = weight;
	    graph->adjM[V * dst + src] = weight;
    }

    ExitCode = Prim(graph);

    free(graph->adjM);
    free(graph);

	exit_marker:

    if (IsGoodError(ExitCode)) {
        switch (ExitCode) {
            case BAD_LENGTH:
                printf("bad length\n");
                break;
            case BAD_NUMBER_OF_EDGES:
                printf("bad number of edges\n");
                break;
            case BAD_NUMBER_OF_LINES:
                printf("bad number of lines\n");
                break;
            case BAD_NUMBER_OF_VERTICES:
                printf("bad number of vertices\n");
                break;
            case BAD_VERTEX:
                printf("bad vertex\n");
                break;
            case NO_SPANNING_TREE:
                printf("no spanning tree\n");
                break;
        }
        ExitCode = EXIT_SUCCESS;
    }

	return ExitCode;
}
