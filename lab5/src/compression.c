#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "compression.h"
#include "tree.h"
#include "frequency.h"
#include "bits.h"

#define BUFFSIZE (256)
#define ALPHABET_SIZE (256)

enum errorCodes {
    MEMORY_ALLOCATION_ERROR = 201,
    STRNCPY_ERROR,
};

static void compress_OneLetterCase(FILE * output, int * freqArr) {
        char n = 0, l = 0, buf;
        int totalBitStrLen = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++){
            if (freqArr[i]){
                l = (char) i;
                totalBitStrLen = freqArr[i];
                break;
            }
        }

        WriteBit(output, &buf, &n, 1);
        WriteByte(output, &buf, &n, l);
        WriteInt(output, &buf, &n, totalBitStrLen);
        if (n){
            fwrite(&buf, 1, 1, output);
        }
}

int compress(FILE * input, FILE * output, _Bool isArgFiles){

    int freqArr[ALPHABET_SIZE] = {0};
    int c = InitFreqAr(input, freqArr);

    if (!c){
        return EXIT_SUCCESS;
    } else if (c == 1) {
        compress_OneLetterCase(output, freqArr);
        return EXIT_SUCCESS;
    }

    unsigned char * lettersArr = malloc(c * sizeof(unsigned char));
    if (lettersArr == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }
    lettersArr = CreateLettersArr(freqArr, lettersArr);

    Node_t * * nodes = malloc(c * sizeof(Node_t *));
    if (nodes == NULL){
        return MEMORY_ALLOCATION_ERROR;
    }
    for (int i = 0; i < c; i++){
        nodes[i] = CreateNode(GetFreqByNum(freqArr, i), NULL, NULL, lettersArr[i], 1);
    }
    free(lettersArr);

    BuildHuffmanTree(nodes, c);
    Node_t * Root = nodes[c-1];
    free(nodes);

    char buf, n = 0;
    WriteBitTree(output, Root, &buf, &n);

    char * codes[ALPHABET_SIZE] = {NULL};
    char bufBitStr[ALPHABET_SIZE + 1];
    int totalBitStrLen = 0;

    SNode_t * node = malloc(sizeof(SNode_t));
    if (node == NULL){
        return MEMORY_ALLOCATION_ERROR;
    }

    while(Root->left || Root->right){
        node = ParseTree(Root, bufBitStr, freqArr, &totalBitStrLen, node);
        if (!node->IsSource){
            continue;
        }
        codes[node->letter] = malloc(ALPHABET_SIZE);
        if (codes[node->letter] == NULL){
            return MEMORY_ALLOCATION_ERROR;
        }
        if ( !(strncpy(codes[node->letter], bufBitStr, BUFFSIZE)) ){
            return STRNCPY_ERROR; 
        }
    }
    
    free(Root);
    free(node);

    WriteInt(output, &buf, &n, (unsigned int) totalBitStrLen);

    rewind(input);
    unsigned char l;
    if (!isArgFiles){
        l = fgetc(input);
    } // to skip mode-symb;
    while (fread(&l, sizeof(unsigned char), 1, input) > 0){
        unsigned char i = 0;
        char k;
        while ( (k = codes[l][i++]) ){
            WriteBit(output, &buf, &n, (k - '0'));
        }
    } if (n){
        fwrite(&buf, 1, 1, output);
    }

    for(int i = 0; i < 256; i++){
        if(codes[i]){
            free(codes[i]);
        }
    }
    return EXIT_SUCCESS;
}
