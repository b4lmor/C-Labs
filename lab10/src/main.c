#include <stdlib.h>
#include <stdio.h>

#include "GrahamScan.h"

int main(void) {
    int ExitCode = EXIT_SUCCESS;

    int N;
    if (1 != scanf("%i", &N)){
        ExitCode = BAD_NUMBER_OF_LINES;
        goto exit_marker;
    }
    if (N < 0 || N > 100000){
        ExitCode = BAD_NUMBER_OF_POINTS;
        goto exit_marker;

    }
    if (N == 0){
        ExitCode = EXIT_SUCCESS;
        goto exit_marker;
    }
    if (N == 1){
        int x, y;
        if (2 != scanf("%i %i", &x, &y)){
            ExitCode = BAD_NUMBER_OF_LINES;
            goto exit_marker;
        } else {
            printf("%i %i\n", x, y);
            ExitCode = EXIT_SUCCESS;
            goto exit_marker;
        }
    }

    Point * points = malloc(N * sizeof(Point));
    if (points == NULL) {
        ExitCode = MEMORY_ALLOCATION_ERROR;
        goto exit_marker;
    }

    for (int i = 0; i < N; i++){
        int x, y;
        if (2 != scanf("%i %i", &x, &y)){
            free(points);
            ExitCode = BAD_NUMBER_OF_LINES;
            goto exit_marker;
        }
        points[i].x = x;
        points[i].y = y;
    }

    /* === === ===
    M - Minimal
    C - Convex
    H - Hull
    === === === */
    int MCHLen = 0;
    Point * MCH = GrahamScan(points, N, &MCHLen);
    if (!MCH) {
        free(points);
        ExitCode = MEMORY_ALLOCATION_ERROR;
        goto exit_marker;
    } else {
        for (int i = 0; i < MCHLen; ++i) {
            printf("%d %d\n", MCH[i].x, MCH[i].y);
        }
        free(MCH);
        free(points);
    }

    exit_marker:

    switch (ExitCode) {
        case BAD_NUMBER_OF_LINES:
            printf("bad number of lines\n");
            ExitCode = EXIT_SUCCESS;
            break;
        
        case BAD_NUMBER_OF_POINTS:
            printf("bad number of points\n");
            ExitCode = EXIT_SUCCESS;
            break;
    }

    return ExitCode;
}
