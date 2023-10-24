#include <stdlib.h>
#include <stdio.h>

typedef struct AVL AVL;
struct AVL{
    int value;
    unsigned height;
    AVL * left;
    AVL * right;
};

unsigned height(AVL * p){
  return p ? p->height : 0;
}

int delta(AVL * p){
  return height(p->right) - height(p->left);
}

void FixHeight(AVL * p){
  unsigned hl = height(p->left);
  unsigned hr = height(p->right);
  p->height = (hl > hr ? hl : hr) + 1;
}

AVL * rotateright(AVL * p){
  AVL * q = p->left;
  p->left = q->right;
  q->right = p;
  FixHeight(p);
  FixHeight(q);
  return q;
}

AVL * rotateleft(AVL * q){
  AVL * p = q->right;
  q->right = p->left;
  p->left = q;
  FixHeight(q);
  FixHeight(p);
  return p;
}

AVL * balance(AVL * p){
  FixHeight(p);
  if( delta(p) == 2 ){
    if( delta(p->right) < 0 ){
      p->right = rotateright(p->right);
        }
    return rotateleft(p);
  }

  if( delta(p) == -2 ){
    if( delta(p->left) > 0  ){
      p->left = rotateleft(p->left);
        }
    return rotateright(p);
  }
  return p;
}

AVL * insert(AVL * p, int k, int i, AVL * base){
  if(!p){
        AVL * ans = &base[i];
        ans->value = k;
        ans->height = 1;
        ans->left = ans->right = NULL;
        return ans; 
    }
  if( k < p->value ){
    p->left = insert(p->left, k, i, base);
    }
  else{
    p->right = insert(p->right, k, i, base);
    }
  return balance(p);
}

int main(void) {

    int N;
    if (1 != scanf("%i", &N)){
        return EXIT_FAILURE;
    }
    if (N == 0){
        printf("0\n");
        return EXIT_SUCCESS;
    }

    AVL * base = malloc(N * sizeof(AVL));
    AVL * avl = NULL;
    int val;
    for(int i = 0; i < N; i++){
        if (1 != scanf("%i", &val)){
            printf("0\n");
            return EXIT_FAILURE;
        }
        avl = insert(avl, val, i, base);
    }
    printf("%u\n", avl->height);

    free(base);

    return EXIT_SUCCESS;
}
