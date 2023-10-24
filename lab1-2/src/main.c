#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PATTERN_LEN (17)

void InitShiftTable(char * shiftTable, char * pattern, int len){
    int j = 0, i = 1;
    while (i < len){
        if (pattern[i] != pattern[j]){
            if (!j){
                shiftTable[i++] = 0;
            } else {
                j = shiftTable[j - 1];
            }
        } else {
            shiftTable[i] = ++j;
            i++;
        }
    }
}

void ReadStr(FILE * file, char * buf, int bufsize){
    for (int i = 0; i < bufsize; i++){
        char c = fgetc(file);
        if (feof(file) || c == '\n'){
            buf[i] = 0;
            return;
        }
        buf[i] = c;
    }
    buf[bufsize] = 0;
}

void PrintArr(char * Arr, int N){
    for (int i = 0; i < N; i++){
        printf("%i ", Arr[i]);
    }
    printf("\n");
}

void ReadBuf(FILE * in, char * buf, int pLen) {
    int i;
    for (i = 0; i < pLen; i++) {
        if (feof(in)) {
            buf[i] = 0;
            return;
        }
        buf[i] = fgetc(in);
    }
    buf[i] = 0;
}

char GetNextChar(FILE * in, char * str, int * pos, char Plen) {
    if (*pos == (int) strlen(str)) {
        ReadBuf(in, str, Plen);
        *pos = 0;
    }
    if (str[0] == 0) {
        return -1;
    }
    return str[(*pos)++];
}

void KMP(FILE * input){
    char pattern[MAX_PATTERN_LEN];
    char shiftTable[MAX_PATTERN_LEN - 1] = { 0 };
    char buf[MAX_PATTERN_LEN] = { 0 };

    ReadStr(input, pattern, MAX_PATTERN_LEN);

    int len = strlen(pattern);

    InitShiftTable(shiftTable, pattern, len);

    PrintArr(shiftTable, len);

    int i = 0;
    int j = 0;
    int pos = 0;
    char c = GetNextChar(input, buf, &pos, len);

    while (c != -1) {
        bool flag = false;
        while (pattern[j] == c && c != -1) {

            flag = true;
            i++;
            c = GetNextChar(input, buf, &pos, len);
            if (feof(input) && len > (int) (1 + j + strlen(buf) - pos) ) {
                return;
            }
            j++;

            if (j == len) {
                printf("%i %i ", i - j + 1, j);
                flag = false;

                j = shiftTable[j - 1];
            }
        }
        if (flag && c != -1) {
            printf("%i %i ", i - j + 1, j);
        }

        if (j > 0) {
            j = shiftTable[j - 1];
        } else {
            i++;
            c = GetNextChar(input, buf, &pos, len);
        }
        if (feof(input) && len > (int) (1 + j + strlen(buf) - pos) ) {
            return;
        }
    }
}

int main(void) {

    FILE * input = fopen("in.txt", "r");

    KMP(input);

    fclose(input);
    return EXIT_SUCCESS;
}
