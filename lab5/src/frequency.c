#include <stdio.h>
#include <stdlib.h>

#include "frequency.h"

#define ALPHABET_SIZE 256

int InitFreqAr(FILE * file, int * freq){
    unsigned char symb;
    int c = 0;
    while (fread(&symb, 1, 1, file) > 0){
        c += !(freq[symb]++);
    }
    return c;
}

int GetFreqByNum(int * array, int num){
    int c = 0;
    for (int i = 0; i < 256; i++){
        if (array[i]){
            if (c++ == num){
                return array[i];
            }
        }
    }
    return 0; // impossible case
}

unsigned char * CreateLettersArr(int * freqArr, unsigned char * lettersArr){
    int ind = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++){
        if (freqArr[i]){
            lettersArr[ind++] = i;
        }
    }
    return lettersArr;
}
