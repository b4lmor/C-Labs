#include "tree.h"
#include "qs.h"

static void swap(Node_t * * a, Node_t * * b){
    Node_t * t;
    t = *a, *a = *b, *b = t;
}

void QS(Node_t * * s_arr, int first, int last){
    if (first < last){
        int left = first, right = last, middle = s_arr[(left + right) / 2]->value;
        do{
            while (s_arr[left]->value < middle) left++;
            while (s_arr[right]->value > middle) right--;
            if (left <= right){
                swap(&s_arr[left], &s_arr[right]);
                left++;
                right--;
            }
        } while (left <= right);
        QS(s_arr, first, right);
        QS(s_arr, left, last);
    }
}
