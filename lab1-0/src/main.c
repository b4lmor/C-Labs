#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFERSIZE (256)

void ReadStr(FILE * file, unsigned char * buf, int bufsize){
    for (int i = 0; i < bufsize; i++){
        unsigned char c = fgetc(file);
        if (feof(file) || c == (unsigned char) '\n'){
            buf[i] = 0;
            return;
        }
        buf[i] = c;
    }
    buf[bufsize] = 0;
}

void InitShiftTable(char * shiftTable, unsigned char * pattern, char len){
    for (int i = 1; i < len; i++){
        shiftTable[(unsigned) pattern[len - 1 - i]] = shiftTable[(unsigned) pattern[len - 1 - i]] ?
                                                 shiftTable[(unsigned) pattern[len - 1 - i]] : i;
    }
    shiftTable[(unsigned) pattern[len - 1]] = shiftTable[(unsigned) pattern[len - 1]] ?
                                         shiftTable[(unsigned) pattern[len - 1]] : len;
    for (int i = 0; i < 256; i++){
        if (!shiftTable[i]){
            shiftTable[i] = len;
        }
    }
}

int GetLen(unsigned char * str){
    int len = 0;
    while (*str++){
        len++;
    }
    return len;
}

void BM(FILE * f){

    unsigned char pattern[17];
    ReadStr(f, pattern, 17);
    
    int lenP = GetLen(pattern);

    unsigned char text[BUFFERSIZE+1];
    int iter = 0;
    int lenT = fread(text, sizeof(char), BUFFERSIZE, f);

    if (lenT < lenP){
        return;
    }

    char shiftTable[256] = {0};
    InitShiftTable(shiftTable, pattern, lenP);

    while (lenT){
        
        long long int k = BUFFERSIZE * iter;
        text[lenT] = 0;
        int pos = lenP-1;

        while (1){

            if (pos >= lenT) {
                break;
            }
            printf("%lli ", pos+1+k);

            if (text[pos] != pattern[lenP-1]){

                pos += shiftTable[ (unsigned) text[pos] ];
                if (pos >= lenT) {
                    break;
                }
                continue;
            }

            int poscpy = pos-1, curIndex = lenP-2, flag = 1;
            while (curIndex+1){
                if (text[poscpy] == pattern[curIndex]){
                    printf("%lli ", poscpy+1+k);
                    poscpy--;
                    curIndex--;
                } else {
                    printf("%lli ", poscpy+1+k);
                    pos += shiftTable[ (unsigned) text[pos] ];
                    flag = 0;
                    break;
                }
            }

            pos += (lenP) * flag;
        }
        iter++;
        lenT = fread(text, sizeof(char), BUFFERSIZE, f);
    }
}

int main(void) {

    FILE * input = fopen("in.txt", "r");

    BM(input);

    fclose(input);
    return EXIT_SUCCESS;
}
