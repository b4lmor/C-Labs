#include "GrahamScan.h"

#include <stdio.h>

Point p0 = {0, 0}; // глобальная переменная необходима, чтобы передать её в компаратор.

static int ComparePoints(void const * p1_void, void const * p2_void) {
    Point * p1 = (Point *) p1_void;
    Point * p2 = (Point *) p2_void;

    const long double det = Determinant(&p0, p1, p2);
    if (det == 0.0) { // => векторы на одной прямой => сравниваем длины
        return VectorLen(&p0, p1) > VectorLen(&p0, p2);
    }

    return det < 0.0;
}

Point * GrahamScan(Point * points, int N, int * MCHLen) {

    for (int i = 1; i < N; i++) {
        if (
            points[i].x < points[0].x || 
            (points[i].x == points[0].x && points[i].y < points[0].y)
           ) {
            SwapPoints(&points[0], &points[i]);
        }
    }
    p0 = points[0];

    qsort(&points[1], N - 1, sizeof(Point), ComparePoints);

    Stack * stack = CreateStack(N);
    if (!stack) {
        return NULL;
    }

    if (Push(stack, p0) != EXIT_SUCCESS) {
        return NULL;
    }
    for (int i = 1; i < N; i++) {
        while (stack->size >= 2) {
            Point peek = Peek(stack);
            Point nextToPeek = NextToPeek(stack);

            if (Determinant(&nextToPeek, &peek, &points[i]) <= 0.0) {
                Pop(&stack);
            } else {
                break;
            }
        }
        Push(stack, points[i]);
    }

    *MCHLen = stack->size;
    Point * MCH = malloc(stack->size * sizeof(Point));
    if (!MCH) {
        FreeStack(&stack);
        return NULL;
    }
    MCH[0] = p0;

    for (int i = stack->size - 1; i > 0; i--) {
        MCH[i] = Pop(&stack);
    }

    FreeStack(&stack);
    return MCH;
}
