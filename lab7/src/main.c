#include <stdlib.h>
#include <stdio.h>

#define Height (2000) // 8 | Height
#define Length (Height / 8)

char Any(char Mx[Height][Length], int Col){
    for (int j = 0; j < Length; j++){
        if (Mx[Col][j]){
            return 1;
        }
    }
    return 0;
}

void PrintArray(int * A, int N){
    for (int j = 0; j < N; j++){
        printf("%i ", A[j]);
    }
    printf("\n");
}

char TopSort(char Mx[Height][Length], int N, int * ans){
    char * markers = calloc(N, sizeof(char));
    int c = 0;
    while (1){
        char flag = 1; 
        for (int k = 0; k < N; k++){
            if ( !(Any(Mx, k) || markers[k]) ){
                ans[c++] = k+1;
                markers[k] = 1;
                if (c == N){
                    free(markers);
                    return 1;
                }
                for(int j = 0; j < N; j++){
                    Mx[j][k/8] &= ~(1 << (k%8));
                }
                flag = 0;
            }
        }
        if (flag){
            free(markers);
            return 0;
        }
    }
}

int main(void){
    int N;
    if (1 != scanf("%i", &N)){
        printf("bad number of lines\n");
        return EXIT_SUCCESS;
    }
    if (N < 0 || N > 2000){
        printf("bad number of vertices\n");
        return EXIT_SUCCESS;
    }
    
    int M;
    if (1 != scanf("%i", &M)){
        printf("bad number of lines");
        return EXIT_SUCCESS;
    }
    if (M < 0 || M > (N * (N - 1) / 2) ){ // " если M не от 0 до N * (N + 1) / 2, то "bad number of edges" " - from TODO
        printf("bad number of edges\n");
        return EXIT_SUCCESS;
    }
    
    char Mx[Height][Length] = {{ 0 }};

    for (int i = 0; i < M; i++){
        int j, k;
        if (2 != scanf("%i %i", &j, &k)){
            printf("bad number of lines\n");
            return EXIT_SUCCESS;
        }
        if ((0 >= j || j > N) || (0 >= k || k > N)){
            printf("bad vertex\n");
            return EXIT_SUCCESS;
        }
        if (j == k){
            printf("impossible to sort\n");
            return EXIT_SUCCESS;
        }

        j = j - 1;
        k = k - 1;
        Mx[k][j/8] |= (1 << (j%8));
    }

    int * answer = (int *) calloc(N, sizeof(int));
    if (TopSort(Mx, N, answer)){
        PrintArray(answer, N);
    }
    else{
        printf("impossible to sort\n");
    }

    free(answer);
    return EXIT_SUCCESS;
}
