#include "Stack.h"
#include <stdlib.h>

Stack * CreateStack(int elementsCount) {
    Stack * stack = malloc(sizeof(Stack));
    if (!stack) {
        return NULL;
    }

    stack->capacity = elementsCount;
    stack->size = 0;

    stack->points = calloc(elementsCount, sizeof(Point));
    if (!stack->points) {
        free(stack);
        return NULL;
    }

    return stack;
}

Point Pop(Stack * * stack) {
    Point point = {0, 0};

    if (!(*stack) || (*stack)->size <= 0) {
        return point;
    }

    point = (*stack)->points[(*stack)->size - 1];
    ((*stack)->size)--;

    return point;
}

void FreeStack(Stack * * stack) {
    if (!*stack) {
        return;
    }

    free((*stack)->points);
    (*stack)->points = NULL;

    free(*stack);
    (*stack) = NULL;
}

int Push(Stack * stack, Point point) {
    if (stack->size + 1 >= stack->capacity) {
        stack->capacity *= 2;
        stack->points = realloc(stack->points, sizeof(Point) * stack->capacity);
        if (!stack->points) {
            FreeStack(&stack);
            return MEMORY_ALLOCATION_ERROR;
        }
    }

    stack->points[stack->size] = point;
    (stack->size)++;
    return EXIT_SUCCESS;
}

Point GetByIndex(Stack * stack, int index) {
    if (stack->size < 1 || index < 0) {
        Point point = {0, 0};
        return point;
    }

    return stack->points[index];
}

Point Peek(Stack * stack) {
    Point point = {0, 0};
    if (!stack || stack->size <= 0) {
        return point;
    }

    point = stack->points[stack->size - 1];
    return point;
}

Point NextToPeek(Stack * stack) {

    if (!stack) {
        Point point = {0, 0};
        return point;
    }

    return GetByIndex(stack, stack->size - 2);
}
