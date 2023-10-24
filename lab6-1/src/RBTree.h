#ifndef RBTREE_H
#   define RBTREE_H
#endif

enum Colors {
    BLACK,
    RED,
};

typedef struct Node Node_t;
struct Node {
    Node_t * left; 
    Node_t * right;
    int data;
    char color;
};

Node_t * Insert(Node_t *, const int, const int, Node_t *);

int GetHeight(const Node_t *);
