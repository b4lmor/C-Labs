#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "errors.h"
#include "graph.h"
#include "dijkstra.h"

#define IsGoodError(error) (error > 300)

void PrintPathArray(int count, uint64_t * path, FILE * out) {
    for (int i = 0; i < count; i++) {
        if (path[i] == UINT64_MAX) {
            fprintf(out, "oo ");
        } else if (path[i] > INT_MAX) {
            fprintf(out, "INT_MAX+ ");
        } else {
            fprintf(out, "%d ", (int) path[i]);
        }
    }
}

int FindPrevVertex(int vertexNum, uint64_t * pathArray, Graph * graph) {
    for (int i = 0; i < graph->V; i++) {
        int length = graph->adjM[graph->V * i + vertexNum - 1];
        if (length != 0 && pathArray[vertexNum - 1] == length + pathArray[i]) {
            return i + 1;
        }
    }

    return 0;
}

bool IsOverflow(int vertexNum, int size, uint64_t * pathArray) {
    if (pathArray[vertexNum - 1] <= INT_MAX) {
        return false;
    }

    int count = 0;
    for (int i = 0; i < size; i++) {
        if (i != vertexNum - 1         && 
            pathArray[i] != UINT64_MAX &&
            pathArray[i] >= INT_MAX) {
            count++;
            if (count == 2) {
                return true;
            }
        }
    }
    return false;
}

void PrintShortestPath(int endVertex, uint64_t * pathArray, Graph * graph, FILE * out) {
    if (pathArray[endVertex - 1] == UINT64_MAX) {
        fprintf(out, "no path");
        return;
    } else if (IsOverflow(endVertex, graph->V, pathArray)) {
        fprintf(out, "overflow");
        return;
    }

    fprintf(out, "%d ", endVertex);

    while (pathArray[endVertex - 1] != 0) {
        endVertex = FindPrevVertex(endVertex, pathArray, graph);
        if (endVertex == 0) {
            return;
        }

        fprintf(out, "%d ", endVertex);
    }
}

int main(void) {

    FILE * in = fopen("in.txt", "r");
    FILE * out = fopen("out.txt", "w");

    int ExitCode = EXIT_SUCCESS;
    int V, E, start, end;

    if (1 != fscanf(in, "%i", &V)){
        ExitCode = READ_ERROR;
        goto exit_marker;
    }
    if (0 > V || V > 5000) {
        ExitCode = BAD_NUMBER_OF_VERTICES;
        goto exit_marker;
    }

    if (2 != fscanf(in, "%i %i", &start, &end)){
        ExitCode = READ_ERROR;
        goto exit_marker;
    }
    if (0 >= start || start > V ||
        0 >= end   || end   > V) {
        ExitCode = BAD_VERTEX;
        goto exit_marker;
    }

    if (1 != fscanf(in, "%i", &E)){
        ExitCode = READ_ERROR;
        goto exit_marker;
    }
    if (0 > E || E > V * (V - 1) / 2) {
        ExitCode = BAD_NUMBER_OF_EDGES;
        goto exit_marker;
    }

    Graph * graph = CreateGraph(V);
	if (graph == NULL) {
        ExitCode = MEMORY_ALLOCATION_ERROR;
		goto exit_marker;
	}

    for (int i = 0; i < E; i++){
    	int src, dst, weight;
        if (3 != fscanf(in, "%i %i %i", &src, &dst, &weight)){
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
        if (0 > weight) {
            ExitCode = BAD_LENGTH;
            free(graph->adjM);
            free(graph);
            goto exit_marker;
        }

        src -= 1; // - Вершины будут нумероваться не с 1, а с 0
        dst -= 1;

	    graph->adjM[V * src + dst] = weight;
	    graph->adjM[V * dst + src] = weight;
    }

    uint64_t * paths = calloc(graph->V, sizeof(uint64_t));
    if (paths == NULL) {
        free(graph->adjM);
        free(graph);
        ExitCode = MEMORY_ALLOCATION_ERROR;
        goto exit_marker;
    }
    for (int i = 0; i < V; i++) {
        if (i != start - 1) {
            paths[i] = UINT64_MAX;
        }
    }

    ExitCode = Dijkstra(start, graph, paths);

    if (ExitCode == EXIT_SUCCESS) {
        PrintPathArray(V, paths, out);
        fprintf(out, "\n");
        PrintShortestPath(end, paths, graph, out);
    }

    free(graph->adjM);
    free(graph);
    free(paths);

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
        }
        ExitCode = EXIT_SUCCESS;
    }

    fclose(out);
    fclose(in);
	return ExitCode;
}
