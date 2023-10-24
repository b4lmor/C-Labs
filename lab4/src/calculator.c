#include "calculator.h"
#include "errors.h"
#include "stack.h"

#define BUFSIZE 11
#define MAX_INPUT_SIZE 1000

static int MyAtoi(char * str) {
    if (*str == 0) {
        return -1;
    }
    return atoi(str);
}

static bool IsOperator(char c) {
    if (c == '+' ||
        c == '-' ||
        c == '*' ||
        c == '/' ||
        c == '(' ||
        c == ')' ) {
            return true;
        }
    return false;
}

static int ReadNext(FILE * input, RPN_elmt * elmt) {
    
    static char c = 0;
    if (c) {
        goto marker;
    }

    char buf[BUFSIZE];
    int i = 0;

    while (isdigit(c = fgetc(input))) {
        buf[i++] = c;
    } buf[i] = 0;

    if (!IsOperator(c) && c != '\n') {
        return SYNTAX_ERROR;
    } else if (c == '\n' && i == 0) {
        return EOF;
    }

    int val = MyAtoi(buf);
    if (val == -1) {
        elmt->IsOper = true;
        elmt->oper = c;
        c = 0;
    } else {
        elmt->IsOper = false;
        elmt->value = val;
    }

    return EXIT_SUCCESS;

    marker:
    if (!IsOperator(c) && c != '\n') {
        return SYNTAX_ERROR;
    } else if (c == '\n') {
        return EOF;
    } else {
        elmt->IsOper = true;
        elmt->oper = c;
    }
    c = 0;
    return EXIT_SUCCESS;
}

static int UseOperator(int * resp, int b, int a, char operator) {
    switch(operator) {
        case '+':
            *resp = a + b;
            break;
        case '-':
            *resp = a - b;
            break;
        case '*':
            *resp = a * b;
            break;
        case '/':
            if (b == 0) {
                return DIVISION_BY_ZERO;
            }
            *resp = a / b;
            break;
    }
    return EXIT_SUCCESS;
}

static int GetPriority(char oper) {
    switch (oper) {
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        default:
            return 0;
    }
}

static int BuildRPN(RPN_elmt * RPN, int * i, FILE * input) {

    int status = EXIT_SUCCESS;
    RPN_elmt elmt;
    Stack * stack = CreateStack(MAX_INPUT_SIZE);
    if (stack == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }

    RPN_elmt prev = {0, 0, 0};
    while (true) {
        status = ReadNext(input, &elmt);
        if (status == SYNTAX_ERROR) {
            FreeStack(&stack);
            return SYNTAX_ERROR;
        } else if (status == EOF) {
            break;
        }

        if (elmt.IsOper && prev.IsOper) {
            if (elmt.oper == ')' && prev.oper == '(') { // "...()..." case
                FreeStack(&stack);
                return SYNTAX_ERROR;

            } else if ( elmt.oper == '+' ||   // "...+-...", "...(*..." etc. cases
                        elmt.oper == '-' ||
                        elmt.oper == '/' ||
                        elmt.oper == '*' ) {
                FreeStack(&stack);
                return SYNTAX_ERROR;
            }
        }

        if (!elmt.IsOper) {
            RPN[(*i)++] = elmt;
        } else {
            priority_poper:
            if (elmt.oper != '(' && elmt.oper != ')' && GetPriority(elmt.oper) <= GetPriority((char) Peek(stack))) {
                RPN_elmt elmt2 = {.IsOper = true, .oper = (char) Pop(&stack), .value = 0};
                RPN[(*i)++] = elmt2;
                goto priority_poper;
            } 

            if (elmt.oper == ')') {
                bracket_remover:

                if (stack->size == 0) {
                    FreeStack(&stack);
                    return SYNTAX_ERROR;
                }

                if ((char) Peek(stack) != '(') {
                    RPN_elmt elmt2 = {.IsOper = true, .oper = (char) Pop(&stack), .value = 0};
                    RPN[(*i)++] = elmt2;
                    goto bracket_remover;
                    
                } else {
                    status = Pop(&stack); // remove '(' from the stack, 
                    continue;             // don't push ')' into the stack
                }
            }
            Push(stack, elmt.oper);
        }

        prev = elmt;
    }

    if (prev.IsOper && prev.oper != ')') {
        FreeStack(&stack);
        return SYNTAX_ERROR;
    }

    while (stack->size) {
        char oper = (char) Pop(&stack);
        if (oper == '(') {           // the stack must not contain '('
            FreeStack(&stack);
            return SYNTAX_ERROR;
        }
        RPN_elmt elmt2 = {.IsOper = true, .oper = oper, .value = 0};
        RPN[(*i)++] = elmt2;
    }

    if (*i == 0) {
        FreeStack(&stack);
        return SYNTAX_ERROR;
    }

    FreeStack(&stack);
    return EXIT_SUCCESS;
}

static int CalcRPN(RPN_elmt * RPN, int i, int * ans) {
    if (i == 1) {
        *ans = RPN[0].value;
        return EXIT_SUCCESS;
    }

    int answer = 0;

    Stack * stack = CreateStack(MAX_INPUT_SIZE);
    if (stack == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }

    for (int j = 0; j < i; j++) {
        if (!RPN[j].IsOper) {
            Push(stack, RPN[j].value);
        } else {
            int a = Pop(&stack);
            int b = Pop(&stack);
            if (DIVISION_BY_ZERO == UseOperator(&answer, a, b, RPN[j].oper)) {
                FreeStack(&stack);
                return DIVISION_BY_ZERO;
            }
            Push(stack, answer);
        }
    }
    *ans = answer;
    FreeStack(&stack);
    return EXIT_SUCCESS;
}

int calculator(FILE * input) {

    RPN_elmt RPN[MAX_INPUT_SIZE];
    int i = 0;
    
    // Step I : Build Reverse Polish Notation (RPN) :

    int status = BuildRPN(RPN, &i, input);
    if (status != EXIT_SUCCESS) {
        return status;
    }

    // Step II : Process the RPN and print answer

    int answer;

    status = CalcRPN(RPN, i, &answer);
    if (status != EXIT_SUCCESS) {
        return status;
    }

    printf("%i\n", answer);

    return EXIT_SUCCESS;
}
