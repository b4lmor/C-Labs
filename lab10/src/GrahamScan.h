#ifndef GRAHAM_SCAN_H
#define GRAHAM_SCAN_H

#include "Stack.h"
#include <stdlib.h>

// int ComparePoints(void const* A, void const* B);

Point * GrahamScan(Point* points, int numOfPoints, int* numOfPointsInHull);

#endif
