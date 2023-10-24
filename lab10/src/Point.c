#include "Point.h"

void SwapPoints(Point * p1, Point * p2) {
    if (!p1 || !p2) {
        return;
    }

    Point tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

/* === === ===
Функция вернёт квадрат длины
вектора {x2 - x1 ; y2 - y1}.
=== === === */
double VectorLen(Point * p1, Point * p2) {
    return ((double)p2->x - p1->x) * ((double)p2->x - p1->x) +
           ((double)p2->y - p1->y) * ((double)p2->y - p1->y);
}

/* === === ===
Функция вернёт детерминант матрицы 
|x1 - x0   x2 - x0|
|y1 - y0   y2 - y0|
=== === === */
double Determinant(Point * p0, Point * p1, Point * p2) {
    return ((double)p1->x - p0->x) * ((double)p2->y - p0->y) -
           ((double)p2->x - p0->x) * ((double)p1->y - p0->y);
}
