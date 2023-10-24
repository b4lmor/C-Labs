#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define BUFFERSIZE (225)

int Hash(char * line){
    int hash = 0;
    for (int i = strlen(line) - 1; i+1; i--){
        hash = hash * 3 + (unsigned char) line[i] % 3;
    }
    return hash;
}

int SimplePow(const int a, const int x){
    int res = 1;
    for (int i = 0; i < x; i++){
        res *= a;
    }
    return res;
}

int NextHash(const int hash, const unsigned char start, const unsigned char end, const int THREE_IN_MAX){
    return (hash - start % 3) / 3 + end % 3 * THREE_IN_MAX;
}

void CompareLinesSymbBySymb(const char * text, const char * pattern, const int index, const int lenP, const int iteration){
    int iter = 0;
    long long int k = BUFFERSIZE * iteration;
    for (int i = index; i < index + lenP; i++){
        printf("%lli ", (i+1) + k);
        if (! (text[i] == pattern[iter]) ){
            break;
        }
        iter++;
    }
}

int main(void) {

    FILE * f = fopen("in.txt", "r");

    char pattern[17];
    int patternLen = 0;

    char input;

    while (fread(&input, 1, 1, f) == 1 && input != '\n'){
        pattern[patternLen] = input;
        patternLen++;
    }
    pattern[patternLen] = 0;

    char text[BUFFERSIZE+1];

    const int lenP = strlen(pattern);
    const int THREE_IN_MAX = SimplePow(3, lenP-1);

    const int hashP = Hash(pattern);
    printf("%i ", hashP);

    char * subtext = (char *) malloc( (lenP + 1) * sizeof(char));

    int iter = 0;
    int lenT = fread(text, sizeof(unsigned char), BUFFERSIZE, f);
    while (lenT){
        text[lenT] = 0;

        for (int i = 0; i < lenP; i++){
            subtext[i] = text[i];
        }
        subtext[lenP] = 0;

        int hashT = Hash(subtext);

        for (int i = lenP; i < lenT; i++){

            if (hashT == hashP){
                CompareLinesSymbBySymb(text, pattern, i-lenP, lenP, iter);
            }

            int start = text[i - lenP];
            int end = text[i];

            hashT = NextHash(hashT, start, end, THREE_IN_MAX);
            
        } 
        
        if (hashT == hashP){
            CompareLinesSymbBySymb(text, pattern, lenT-lenP, lenP, iter);
        }
        iter++;
        lenT = fread(text, sizeof(unsigned char), BUFFERSIZE, f);
    }

    free(subtext);
    fclose(f);
    return EXIT_SUCCESS;
}
