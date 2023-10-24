#ifndef HEAP_H
#define HEAP_H

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "errors.h"

typedef struct Heap {
    int Count;
    int Max;
    int * Vertex;
    uint64_t * Key;
} Heap;

int CreateHeap(int max, Heap *);
void InitHeap(Heap * heap);
bool IsEmptyHeap(Heap heap);
void SiftDown(int index, Heap * heap);
void SiftUp(int index, Heap * heap);
int ExtractMin(Heap * heap);
int FindVertexIndex(int vertexNum, Heap heap);

#endif
