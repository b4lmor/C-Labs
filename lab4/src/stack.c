#include "stack.h"

#include <stdlib.h>
#include "errors.h"

Stack * CreateStack(int elementsCount) {
    Stack * stack = malloc(sizeof(Stack));
    if (!stack) {
        return NULL;
    }

    stack->capacity = elementsCount;
    stack->size = 0;

    stack->values = calloc(elementsCount, sizeof(int));
    if (!stack->values) {
        free(stack);
        return NULL;
    }

    return stack;
}

int Pop(Stack * * stack) {
    int value = 0;

    if (!(*stack) || (*stack)->size <= 0) {
        return value;
    }

    value = (*stack)->values[(*stack)->size - 1];
    ((*stack)->size)--;

    return value;
}

void FreeStack(Stack * * stack) {
    if (!*stack) {
        return;
    }

    free((*stack)->values);
    (*stack)->values = NULL;

    free(*stack);
    (*stack) = NULL;
}

int Push(Stack * stack, int value) {
    if (stack->size + 1 >= stack->capacity) {
        stack->capacity *= 2;
        stack->values = realloc(stack->values, sizeof(int) * stack->capacity);
        if (!stack->values) {
            FreeStack(&stack);
            return MEMORY_ALLOCATION_ERROR;
        }
    }

    stack->values[stack->size] = value;
    (stack->size)++;
    return EXIT_SUCCESS;
}

int Peek(Stack * stack) {
    if (!stack || stack->size <= 0) {
        return 0;
    }

    int value = stack->values[stack->size - 1];
    return value;
}
