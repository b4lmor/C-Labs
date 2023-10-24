#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "bits.h"

void WriteBit(FILE * file, char * buf, char * n, char bit){
    *buf = bit ? ( (*buf) | (1 << ((*n)++)) ) : ( (*buf) & ~(1 << ((*n)++)) );
    *n = ((*n) % 8) ? (*n) : 0;
    if (!(*n)){
        if (fwrite(buf, 1, 1, file) != 1){
            fprintf(stderr, "Error in WriteBit func!\n");
        }
    }
}

void WriteByte(FILE * file, char * buf, char * n, char byte){
    for (int i = 0; i < 8; i++){
        WriteBit(file, buf, n, ( (byte & (1 << i)) ? 1 : 0 ) );
    }
}

void WriteInt(FILE * file, char * buf, char * n, unsigned int integer){
    for (int i = 0; i < 32; i++){
        WriteBit(file, buf, n, (char) ( (integer & (((unsigned int) 1) << i)) ? 1 : 0 ) );
    }
}

void WriteBitTree(FILE * file, Node_t * node, char * buf, char * n){
    if (node){
        if (node->IsSource){
            WriteBit(file, buf, n, 1);
            WriteByte(file, buf, n, node->letter);
        } else {
            WriteBit(file, buf, n, 0);
        }
        WriteBitTree(file, node->left, buf, n);
        WriteBitTree(file, node->right, buf, n);
    } 
}

char ReadBit(FILE * file, char * buf, char * n){
    *n = ((*n) % 8) ? (*n) : 0;
    if (!(*n)){
        if (fread(buf, 1, 1, file) != 1){
            return EOF;
        }
    }
    return ( (*buf) & (1 << ((*n)++)) ) ? 1 : 0;
}

char ReadByte(FILE * file, char * buf, char * n){
    char resp = 0;
    for (int i = 0; i < 8; i++){
        char bit = ReadBit(file, buf, n);
        if (EOF == bit){
            return EOF;
        }
        resp = bit ? ( resp | (1 << i) ) : ( resp & ~(1 << i) );
    }
    return resp;
}

int ReadInt(FILE * file, char * buf, char * n){
    int resp = 0;
    for (int i = 0; i < 32; i++){
        char bit = ReadBit(file, buf, n);
        if (EOF == bit){
            return EOF;
        }
        resp = bit ? ( resp | (1 << i) ) : ( resp & ~(1 << i) );
    }
    return resp;
}

Node_t * ReadBitTree(FILE * file, char * buf, char * n){
    char bit;
    Node_t * node;
    bit = ReadBit(file, buf, n);
    if (!bit){
        Node_t * left, * right;
        left = ReadBitTree(file, buf, n);
        right = ReadBitTree(file, buf, n);
        node = CreateNode(0, left, right, 0, 0); 
    } else if (bit == EOF){
        return NULL;
    } else {
        char c = ReadByte(file, buf, n);
        node = CreateNode(0, NULL, NULL, c, 1); 
    }
    return node;
}
