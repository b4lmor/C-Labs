#include "heap_pq.h"

int CreateHeap(int max, Heap * heap) {
    heap->Count = 0;
    heap->Max = max;
    heap->Vertex = NULL;
    heap->Key = NULL;

    if (max > 0) {
        heap->Vertex = calloc(max, sizeof(int));
        if (heap->Vertex == NULL) {
            return MEMORY_ALLOCATION_ERROR;
        }

        heap->Key = calloc(max, sizeof(uint64_t));
        if (heap->Key == NULL) {
            free(heap->Vertex);
            return MEMORY_ALLOCATION_ERROR;
        }
    }
    return EXIT_SUCCESS;
}

void InitHeap(Heap * heap) {
    for (int i = 0; i < heap->Max; i++) {
        heap->Vertex[i] = i + 1;
        heap->Key[i] = UINT64_MAX;
    }
    heap->Count = heap->Max;
}

static void Swap(void * value1, void * value2, int size) {
    for (int i = 0; i < size; i++) {
        char buffer = ((char *)value1)[i];
        ((char *)value1)[i] = ((char *)value2)[i];
        ((char *)value2)[i] = buffer;
    }
}

bool IsEmptyHeap(Heap heap) {
    return !!(heap.Count == 0);
}

void SiftDown(int index, Heap * heap) {
    while(true) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largestChild = index;

        if (leftChild < heap->Count && 
            heap->Key[heap->Vertex[leftChild] - 1] < heap->Key[heap->Vertex[largestChild] - 1]) {
            largestChild = leftChild;
        }

        if (rightChild < heap->Count && 
            heap->Key[heap->Vertex[rightChild] - 1] < heap->Key[heap->Vertex[largestChild] - 1]) {
            largestChild = rightChild;
        }

        if (largestChild == index) {
            break;
        }

        Swap(heap->Vertex + index, heap->Vertex + largestChild, sizeof(int));
        index = largestChild;
    }
}

void SiftUp(int index, Heap * heap) {
    while (true) {
        int parent = (index - 1) / 2;
        int parentVertex = heap->Vertex[parent];
        int indexVertex = heap->Vertex[index];

        if (heap->Key[indexVertex - 1] >= heap->Key[parentVertex - 1]) {
            break;
        }

        Swap(heap->Vertex + index, heap->Vertex + parent, sizeof(int));
        index = parent;
    }
}

int ExtractMin(Heap * heap) {
    if (IsEmptyHeap(*heap)) {
        return -1;
    }
    
    int result = *(heap->Vertex);
    Swap(heap->Vertex, heap->Vertex + heap->Count - 1, sizeof(int));
    --heap->Count;
    SiftDown(0, heap);

    return result;
}

int FindVertexIndex(int vertexNum, Heap heap) {
    for (int i = 0; i < heap.Count; i++) {
        if (heap.Vertex[i] == vertexNum) {
            return i;
        }
    }
    return -1;
}
