#ifndef STACK_H
#define STACK_H

#include "Point.h"
#include "errors.h"

typedef struct Stack {
    int size;
    int capacity;
    Point * points;
} Stack;

Stack * CreateStack(int elementsCount);

Point Pop(Stack * * stack);

void FreeStack(Stack * * stack);

int Push(Stack * stack, Point point);

Point GetByIndex(Stack * stack, int index);

Point Peek(Stack * stack);

Point NextToPeek(Stack * stack);

#endif
