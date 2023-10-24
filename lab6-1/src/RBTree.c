#include <stdlib.h>

#include "RBTree.h"

static Node_t * CreateNode(const int data, const char color, 
                                const int i, Node_t * memory) {
    Node_t * node = &memory[i];
    node->data = data;
    node->color = color;
    node->left = node->right = NULL;
    return node;
}

static void ColorFlip(Node_t * node) {
    node->color = !(node->color);
    node->left->color = !(node->left->color);
    node->right->color = !(node->right->color);
}

static Node_t * Rotate(Node_t * node, const char dir) { // direction <-> {left, right}
    Node_t * tmp;
    if (dir){
        tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
    } else {
        tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
    }

    tmp->color = node->color;
    node->color = RED;

    return tmp;
}

static Node_t * DoubleRotate(Node_t * node, const char dir) {
    if (dir){
        node->left = Rotate(node->left, !dir);
    } else {
        node->right = Rotate(node->right, !dir);
    }
    return Rotate(node, dir);
}

static char IsRed(Node_t * node){
    if (node == NULL){
        return 0;
    }
    return node->color == RED;
}

static Node_t * FixUpTree(Node_t * node, const char dir) {
    if (dir) {
        if(IsRed(node->right)) {
            // Случай I : Оба наследника красные ==> есть 2 красных узла подряд (LL LR RR RL) ==> ColorFlip
            if(IsRed(node->left)) {
                if(IsRed(node->right->right) || IsRed(node->right->left)) {
                    ColorFlip(node);
                }
            } else {
                // Случай II : Оба наследника не красные
                if(IsRed(node->right->right)) {
                    // (LL RR) ==> Rotate
                    node = Rotate(node, !dir);
                } else if(IsRed(node->right->left)) {
                    // (LR RL) ==> DoubleRotate
                    node = DoubleRotate(node, !dir);
                }
            }
        }
    } else { // Аналогично для dir |-> !dir
        if(IsRed(node->left)) {
            if(IsRed(node->right)) {
                if(IsRed(node->left->left) || IsRed(node->left->right)) {
                    ColorFlip(node);
                }
            } else {
                if(IsRed(node->left->left)) {
                    node = Rotate(node, !dir);
                } else if(IsRed(node->left->right)) {
                    node = DoubleRotate(node, !dir);
                }
            }
        } 
    }
    return node;
}

static Node_t * RBTreeInsert(Node_t * node, const int data, 
                                const int i, Node_t * memory) {
    if(node == NULL){
        node = CreateNode(data, RED, i, memory);
        return node;
    }

    char dir = !!(data > node->data); // false ==> left ; true ==> right

    if (dir){
        node->right = RBTreeInsert(node->right, data, i, memory);
    } else {
        node->left = RBTreeInsert(node->left, data, i, memory);
    }

    Node_t * resp = FixUpTree(node, dir);

    return resp;
}

Node_t * Insert(Node_t * Root, const int data, 
                    const int i, Node_t * memory) {
    Root = RBTreeInsert(Root, data, i, memory);
    Root->color = BLACK;
    return Root;
}

int GetHeight(const Node_t * node) {
	if (node == NULL){
		return 1;
	}
	return !!(node->color == BLACK) + GetHeight(node->right);
}
