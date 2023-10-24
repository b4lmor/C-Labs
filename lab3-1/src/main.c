#include <stdlib.h>
#include <stdio.h>

void swap(int *a, int *b){
    int t;
    t = *a, *a = *b, *b = t;
}

void QS(int *s_arr, int first, int last){
    if (first < last){
        int left = first, right = last, middle = s_arr[(left + right) / 2];
        do{
            while (s_arr[left] < middle) left++;
            while (s_arr[right] > middle) right--;
            if (left <= right){
                swap(&s_arr[left], &s_arr[right]);
                left++;
                right--;
            }
        } while (left <= right);
        QS(s_arr, first, right);
        QS(s_arr, left, last);
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

    QS(Ar, 0, N-1);
    
    for (int i = 0; i < N; i++){
        printf("%d ", Ar[i]);
    }
    printf("\n");

    free(Ar);
    return  EXIT_SUCCESS;
}
