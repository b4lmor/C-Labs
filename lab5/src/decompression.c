#include <stdio.h>
#include <stdlib.h>

#include "decompression.h"
#include "tree.h"
#include "bits.h"

int decompress(FILE * input, FILE * output){

    char buf, n = 0; 

    Node_t * Root = ReadBitTree(input, &buf, &n);

    int totalBitStrLen = ReadInt(input, &buf, &n);
    if (totalBitStrLen == EOF){
        return EXIT_SUCCESS;
    }

    if (!Root->left && !Root->right){
        for (int i = 0; i < totalBitStrLen; i++){
            fprintf(output, "%c", Root->letter);
        }
        FreeNodes(Root);
        return EXIT_SUCCESS;
    }

    Node_t * node = Root;
    for (int i = 0; i < totalBitStrLen; i++){
        char bit = ReadBit(input, &buf, &n);
        node = bit ? node->right : node->left;
        if (node->IsSource){
            fprintf(output, "%c", node->letter);
            node = Root;
        }
    }

    FreeNodes(Root);

    return EXIT_SUCCESS;
}
