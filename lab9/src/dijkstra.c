#include "dijkstra.h"
#include "errors.h"

int Dijkstra(int beginVertex, Graph * graph, uint64_t * paths) {
    bool * used = calloc(graph->V, sizeof(bool));
    if (used == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }

    Heap heap;
    if (CreateHeap(graph->V, &heap) != EXIT_SUCCESS) {
        free(used);
        return MEMORY_ALLOCATION_ERROR;
    }
    InitHeap(&heap);
    heap.Key[beginVertex - 1] = 0;
    SiftUp(beginVertex - 1, &heap);

    int vertex = ExtractMin(&heap);
    if (vertex == -1) {
        free(used);
        free(heap.Vertex);
        free(heap.Key);
        return EMPTY_HEAP_EXTRACTION;
    }
    used[vertex - 1] = true;
    
    while (!IsEmptyHeap(heap)) {
        for (int i = 0; i < graph->V; i++) {
            if (used[i]) {
                continue;
            }

            int length = graph->adjM[graph->V * i + vertex - 1];
            if (length == 0) {
                continue;
            } 

            if (heap.Key[vertex - 1] + length < heap.Key[i]) {
                heap.Key[i] = heap.Key[vertex - 1] + length;
                paths[i] = heap.Key[vertex - 1] + length;

                int index = FindVertexIndex(i + 1, heap);
                if (index == -1) {
                    free(used);
                    free(heap.Vertex);
                    free(heap.Key);
                    return INDEX_ERROR;
                }

                SiftUp(index, &heap);
            }
        } 

        vertex = ExtractMin(&heap);
        if (vertex == -1) {
            free(used);
            free(heap.Vertex);
            free(heap.Key);
            return EMPTY_HEAP_EXTRACTION;
        }
        used[vertex - 1] = true;
    }

    free(used);
    free(heap.Vertex);
    free(heap.Key);

    return EXIT_SUCCESS;
}
