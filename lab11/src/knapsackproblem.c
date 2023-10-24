#include <stdlib.h>
#include <stdio.h>

#include "knapsackproblem.h"

#define MEMORY_ALLOCATION_ERROR -2

#define MAX(a, b) ( ((a) > (b)) ? (a) : (b) )

static void BuildTable(int * * table, const int N, const int capacity, const int * weights, const int * prices) {
    for (int i = 1; i < N + 1; i++){
        for (int w = 1; w < capacity + 1; w++){
            if (weights[i-1] > w) {
                table[i][w] = table[i-1][w];
            } else {
                table[i][w] = MAX(
                                    table[i-1][w],
                                    table[i-1][w - weights[i-1]] + prices[i-1]
                                 );
            }
        }
    }
}

static void SelectItems(char * answer, const int * * table, const int * prices, const int capacity, int row) {
    int ind = capacity;
    int c = table[row][capacity];
    while (row){
        if (table[row][ind] != table[row-1][ind]){
            c -= prices[row-1];
            answer[row-1] = 1;
            for (int i = 0; i < capacity + 1; i++){
                if (table[row-1][i] == c){
                    ind = i;
                    break;
                }
            }
        }
        row--;
    }
}

int PackKnapsack(const int N, const int capacity, const int * weights, const int * prices, char * answer){
    int * * table = malloc((N + 1) * sizeof(int *));
    if (table == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }
    for (int i = 0; i < N + 1; i++) {
        table[i] = calloc((capacity + 1), sizeof(int));
        if (table[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(table[i]);
            }
            free(table);
            return MEMORY_ALLOCATION_ERROR;
        }
    }

    BuildTable(table, N, capacity, weights, prices);

    SelectItems(answer, (const int * *) table, prices, capacity, N);

    int summary = table[N][capacity];

    for (int i = 0; i < N + 1; i++){
        free(table[i]);
    }
    free(table);

    return summary;
}
