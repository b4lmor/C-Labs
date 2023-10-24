#ifndef STACK_H
#define STACK_H

typedef struct Stack {
    int size;
    int capacity;
    int * values;
} Stack;

Stack * CreateStack(int);

int Pop(Stack * *);

void FreeStack(Stack * *);

int Push(Stack *, int);

int Peek(Stack *);

#endif
