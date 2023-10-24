#include <stdlib.h>

#include "errors.h"
#include "calculator.h"

int main(void) {

    FILE * input = fopen("in.txt", "r");

    int ExitCode = calculator(input);

    fclose(input); 

    switch (ExitCode) {
        case SYNTAX_ERROR:
            printf("syntax error\n");
            ExitCode = EXIT_SUCCESS;
            break;
        case DIVISION_BY_ZERO:
            printf("division by zero\n");
            ExitCode = EXIT_SUCCESS;
            break;
    }

    return ExitCode;
}
