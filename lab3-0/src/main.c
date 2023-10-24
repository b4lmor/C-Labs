#include <stdlib.h>
#include <stdio.h>

void Swap(int *a, int *b){
    int t;
    
    t = *a, *a = *b, *b = t;
}

int Left(int i){
    return (2 * i + 1);
}

int Right(int i){
    return (2 * i + 2);
}

void Heapify(int A[], int i, int N){

    int left = Left(i);
    int right = Right(i);

    int largest = i;

    if (left < N && A[left] > A[i]){
        largest = left;
    }

    if (right < N && A[right] > A[largest]){
        largest = right;
    }

    if (largest != i){
        Swap(&A[i], &A[largest]);
        Heapify(A, largest, N);
    }
}

void BuildHeap(int A[], int N){
    int i = (N - 2) / 2;
    while (i >= 0){
        Heapify(A, i--, N);
    }
}

void Heapsort(int A[], int N){

    BuildHeap(A, N);

    while (N != 1){
        Swap(&A[0], &A[N - 1]);

        N--;

        Heapify(A, 0, N);
    }
}

int main(void){
    int N;

    if (1 != scanf("%i", &N)){
        return EXIT_FAILURE;
    }
    
    if (N == 0){
        return EXIT_SUCCESS;
    }

    int *Ar = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++){
        if (1 != scanf("%i", &Ar[i])){
            return EXIT_FAILURE;
        }
    }

    Heapsort(Ar, N);

    for (int i = 0; i < N-1; i++){
        printf("%d ", Ar[i]);
    }

    printf("%d\n", Ar[N-1]);
    free(Ar);

    return EXIT_SUCCESS;
}
