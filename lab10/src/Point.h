#ifndef POINT_H
#define POINT_H

typedef struct Point {
    int x;
    int y;
} Point;

void SwapPoints(Point* p1, Point* p2);

double VectorLen(Point* p1, Point* p2);

double Determinant(Point* center, Point* p1, Point* p2);

#endif
