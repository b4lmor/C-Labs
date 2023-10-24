#ifndef TREE_H
#define TREE_H

typedef struct Node Node_t;
struct Node{
    Node_t * left;
    Node_t * right;
    int value;
    unsigned char letter;
    char IsSource;
};

typedef struct SNode SNode_t;
struct SNode{
    unsigned char letter;
    char IsSource;
};

Node_t * CreateNode(int, Node_t *, Node_t *, unsigned char, char);

void BuildHuffmanTree(Node_t * *, int);

SNode_t * ParseTree(Node_t *, char *, int *, int *, SNode_t *);

void FreeNodes(Node_t * Root);

#endif
