#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>


void checker(_Bool cond, char * resp){
    if(cond){
        printf("%s", resp);
        exit(0);
    }
}


long long int summa(int * Array, int Lenght){
    long long int cur_sum = 0LL;

    for(int i = 0; i < Lenght; i++){
        cur_sum += Array[i];
    }

    return cur_sum;
}


int main(void) {

    int N;
    
    if(1 != scanf("%i", &N)){
        return 0;
    }

    checker(
            (10 < N || 1 > N),
            "bad input"
           );

    int * Ar = (int *)malloc(N * sizeof(int));

    for(int i = 0; i < N; i++){

        long long int input_value = 0LL;
        int input_lenght = scanf("%lli", &input_value);

        checker(
                (input_lenght != 1 || (int) input_value != input_value),
                "bad input"
              );
        
        Ar[i] = input_value;

    }

    long long int cur_sum = summa(Ar, N);

    checker(
            cur_sum > INT_MAX || cur_sum < INT_MIN,
            "overflow"
          );
    
    printf("%lli", cur_sum);
    
    free(Ar);

    return 0;
}

