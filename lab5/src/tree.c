#include <stdlib.h>
#include <assert.h>

#include "tree.h"
#include "qs.h"

Node_t * CreateNode(int value, Node_t * left, Node_t * right, unsigned char letter, char IsSource){
    
    Node_t * node = malloc(sizeof(Node_t));
    assert( (node != NULL) && "MEMORY_ALLOCATION_ERROR"); // этот аллок я до мейна не выташу =/

    node->value = value;
    node->left = left;
    node->right = right;
    node->letter = letter;
    node->IsSource = IsSource;

    return node;
}

void BuildHuffmanTree(Node_t * * nodes, int c){
    int cnt = 0;
    while(c - cnt != 1) {
        QS(nodes, cnt, c-1);
        nodes[cnt+1] = CreateNode(
                                    (nodes[cnt]->value + nodes[cnt+1]->value),
                                    nodes[cnt],
                                    nodes[cnt+1],
                                    (unsigned char) 0,
                                    (char) 0
                                 );
        cnt++;
    }
}

SNode_t * ParseTree(Node_t * node, char * bitString, int * freqAr, int * totalBitStrLen, SNode_t * buf){
    int length = 0;
    Node_t * last = node;

    start:
    while (node->left){
        last = node;
        node = node->left;

        bitString[length++] = '0';
    }

    while (node->right){
        last = node;
        node = node->right;

        bitString[length++] = '1';
        goto start;
    }
    
    bitString[length] = 0;

    if (node->IsSource){
        for (int i = 0; i < 256; i++){
            if (freqAr[i] == node->value){
                *totalBitStrLen += length * freqAr[i];
                freqAr[i] = 0;
                break;
            }
        }
    }

    buf->IsSource = node->IsSource;
    buf->letter = node->letter;

    if (last->left == node){
        free(last->left);
        last->left = NULL;
    } else if (last->right == node){
        free(last->right);
        last->right = NULL;
    }
    return buf;
}

void FreeNodes(Node_t * Root){
    if (Root->left){
        FreeNodes(Root->left);
    }
    if (Root->right){
        FreeNodes(Root->right);
    }
    free(Root);
}
