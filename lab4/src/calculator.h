#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct RPN_elmt {
    int value;
    char oper;
    bool IsOper;
} RPN_elmt;

int calculator(FILE *);

#endif
