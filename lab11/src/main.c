#include <stdlib.h>
#include <stdio.h>

#include "knapsackproblem.h"

#define MEMORY_ALLOCATION_ERROR -2
#define READ_ERROR -3

void PrintAnswer(int N, int summary, int * weights, int * prices, char * answer) {
    printf("%i\n", summary);

    for (int i = 0; i < N; i++){
        if (answer[i]){
            printf("%i %i\n", weights[i], prices[i]);
        }
    }
}

int main(void) {

    int N, capacity;

    if (2 != scanf("%i %i", &N, &capacity)){
        return READ_ERROR;
    }

    int * prices = malloc(N * sizeof(int));
    if (prices == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }
    int * weights = malloc(N * sizeof(int));
    if (weights == NULL) {
        free(prices);
        return MEMORY_ALLOCATION_ERROR;
    }

    for (int i = 0; i < N; i++){
        if (2 != scanf("%i %i", &weights[i], &prices[i])){
            return EXIT_FAILURE;
        }
    }

    char * answer = calloc(N, sizeof(char));
    if (answer == NULL) {
        free(prices);
        free(weights);
        return MEMORY_ALLOCATION_ERROR;
    } 

    int summary = PackKnapsack(N, capacity, weights, prices, answer);
    if (summary == MEMORY_ALLOCATION_ERROR) {
        free(prices);
        free(weights);
        free(answer);
        return MEMORY_ALLOCATION_ERROR;
    }

    PrintAnswer(N, summary, weights, prices, answer);

    free(prices);
    free(weights);
    free(answer);
    return EXIT_SUCCESS;
}
