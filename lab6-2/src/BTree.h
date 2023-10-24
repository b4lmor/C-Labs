#ifndef BTREE_H
#define BTREE_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"

typedef struct BTree {
    int * key; // [2 * T - 1]
    struct BTree * * child; // [2 * T]
    int n;
} BTree;

int Insert(BTree * *, int, int);

int GetHeight(BTree *);

void FreeBTree(BTree *, int);

#endif
