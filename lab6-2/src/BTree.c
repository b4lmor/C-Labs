#include "BTree.h"

static int GetChildIdx(const BTree * bT, int k) {
    int left = 0;
    int right = bT->n;
    while (left < right) {
        int mid = (left + right) / 2;
        if (k <= bT->key[mid]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return right;
} 

static bool IsLeaf(BTree *bT) {
    return !!(bT->child[0] == NULL);
}

static bool IsFull(BTree *bT, int T) {
    return !!(bT->n == 2 * T - 1);
}

static BTree * Create(int T) {

    BTree * tmp = malloc(sizeof(BTree));
    if (tmp == NULL) {
        return NULL;
    }

    tmp->child = malloc(2 * T * sizeof(BTree *));
    if (tmp->child == NULL) {
        free(tmp);
        return NULL;
    }

    tmp->n = 0;

    tmp->key = malloc(((2 * T - 1) * sizeof(int)));
    if (tmp->key == NULL) {
        free(tmp->child);
        free(tmp);
        return NULL;
    }

    return tmp;
}

static void MoveTail(BTree * src, int i, BTree * dst, int j) {
    int t = dst->n - j;
    memmove(dst->key + j,
            src->key + i,
            t * sizeof(int));
    memmove(dst->child + j,
            src->child + i,
            (t + 1) * sizeof(BTree*));
}

static void AddKey(BTree * bT, int k) {
    int c = GetChildIdx(bT, k);
    bT->n += 1;
    MoveTail(bT, c, bT, c + 1);
    bT->key[c] = k;
}

static int Split(int c, BTree * p, int T) {
    BTree * fc = p->child[c];
    BTree * nc = Create(T);
    if (nc == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }
    nc->n = T - 1;
    MoveTail(fc, T, nc, 0);
    fc->n = T - 1;
    p->n += 1;
    MoveTail(p, c, p, c + 1);
    p->key[c] = fc->key[T - 1];
    p->child[c + 1] = nc;
    return EXIT_SUCCESS;
}

static int InsertNonFull(BTree * bT, int k, int T) {
    if (IsLeaf(bT)) {
        AddKey(bT, k);
    } else {
        int c = GetChildIdx(bT, k);
        if (IsFull(bT->child[c], T)) {
            if (Split(c, bT, T) == MEMORY_ALLOCATION_ERROR) {
                return MEMORY_ALLOCATION_ERROR;
            }
            c = GetChildIdx(bT, k);
        }
        if (InsertNonFull(bT->child[c], k, T) == MEMORY_ALLOCATION_ERROR) {
            return MEMORY_ALLOCATION_ERROR;
        }
    }
    return EXIT_SUCCESS;
}

int Insert(BTree * * bT, int k, int T) {
    BTree * nonFull = Create(T);
    if (nonFull == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }

    nonFull->child[0] = *bT;
    InsertNonFull(nonFull, k, T);

    if (nonFull->n > 0) {
        *bT = nonFull;
    } else {
        free(nonFull->child);
        free(nonFull->key);
        free(nonFull);
    }
    return EXIT_SUCCESS;
}

int GetHeight(BTree * Root){
    int h = 1;
    while (!IsLeaf(Root)) {
        h++;
        Root = Root->child[0];
    }
    return h;
}

void FreeBTree(BTree * Root, int T) {
    if (Root == NULL) {
        return;
    } else if (!IsLeaf(Root)) {
        for (int i = 0; i < Root->n + 1; i++) {
            FreeBTree(Root->child[i], T);
        }
    }
    free(Root->key);
    free(Root->child);
    free(Root);
}
