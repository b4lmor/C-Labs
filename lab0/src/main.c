#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#define MEMORY_ALLOCATION_ERROR 301
#define BAD_INPUT 302
#define READ_ERROR 303

typedef struct Number Number_t;
struct Number {
    int64_t intPart;
    int64_t numerator;
    int64_t denominator;
};

void ReverseString(char * str) {
    int len = strlen(str);
    for (int i = 0; i < len/2; ++i) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

int CharToDigit(int n, int * val) {
    if (isdigit(n)) {
        *val = n - '0';
        return EXIT_SUCCESS;
    }
    if (isalpha(n)) {
        n = tolower(n);
        *val = 10 + n - 'a';
        return EXIT_SUCCESS;
    }
    return BAD_INPUT;
}

int DigitToChar(int digit, char * c) {
    if (0 <= digit && digit <= 9) {
        *c = (char) ('0' + digit);
        return EXIT_SUCCESS;
    }
    if (digit >= 10) {
        *c = (char) ('a' + digit - 10);
        return EXIT_SUCCESS;
    }
    return BAD_INPUT;
}

int ParseString(char * str, int originalBase, Number_t * num) {
    num->intPart = num->numerator = 0;
    num->denominator = 1;
    char * ptr = str;

    if (*ptr == '.') {
        return BAD_INPUT;
    }

    while (*ptr != '.' && *ptr) {
        int digit;
        int ErrorCode = CharToDigit(*ptr, &digit);
        if (ErrorCode != EXIT_SUCCESS) {
            return ErrorCode;
        }
        if (digit >= originalBase) {
            return BAD_INPUT;
        }
        num->intPart = num->intPart * originalBase + digit;
        ++ptr;
    }

    if (*ptr == '.') {
        ++ptr;
        if (!(*ptr)) {
            return BAD_INPUT;
        }
        while (*ptr) {
            int digit;
            int ErrorCode = CharToDigit(*ptr, &digit);
            if (ErrorCode != EXIT_SUCCESS) {
                return ErrorCode;
            }
            if (digit >= originalBase) {
                return BAD_INPUT;
            }
            num->numerator = num->numerator * originalBase + digit;
            num->denominator *= originalBase;
            ++ptr;
        }
    }
    return EXIT_SUCCESS;
}

int Convert(Number_t * num, int targetBase, char * output) {

    char * ptr = output;
    do {
        char c;
        int ErrorCode = DigitToChar(num->intPart % targetBase, &c);
        if (ErrorCode != EXIT_SUCCESS) {
            return ErrorCode;
        }
        *ptr = c;
        num->intPart /= targetBase;
        ++ptr;
    } while (num->intPart > 0);

    ReverseString(output);

    if (num->numerator > 0) {
        *ptr = '.';
        int fractionalDigits = 0;
        while (num->numerator > 0 && fractionalDigits < 12) {
            ++ptr;
            ++fractionalDigits;
            num->numerator *= targetBase;
            char c;
            int ErrorCode = DigitToChar(num->numerator / num->denominator, &c);
            if (ErrorCode != EXIT_SUCCESS) {
                return ErrorCode;
            }
            *ptr = c;
            num->numerator %= num->denominator;
        }
    }

    return EXIT_SUCCESS;
}

int main(void) {
    int ExitCode = EXIT_SUCCESS;
    int originalBase, targetBase;
    char input[14];
    char output[100] = { 0 };
    Number_t * num = malloc(sizeof(Number_t));

    if (2 != scanf("%i %i", &originalBase, &targetBase)) {
        ExitCode = READ_ERROR;
        goto exit_marker;
        
    }
    if (originalBase< 2 || originalBase > 16 || targetBase < 2 || targetBase > 16){
        ExitCode = BAD_INPUT;
        goto exit_marker;
    }

    if (1 != scanf("%13s", input)) {
        ExitCode = READ_ERROR;
        goto exit_marker;
    }

    if (num == NULL) {
        ExitCode = MEMORY_ALLOCATION_ERROR;
        goto exit_marker;
    }

    ExitCode = ParseString(input, originalBase, num);
    if (ExitCode != EXIT_SUCCESS) {
        goto exit_marker;
    }
    ExitCode = Convert(num, targetBase, output);
    if (ExitCode != EXIT_SUCCESS) {
        goto exit_marker;
    }

    printf("%s\n", output);

    exit_marker:

    if (ExitCode == BAD_INPUT) {
        printf("bad input\n");
        ExitCode = EXIT_SUCCESS;
    }

    free(num);
    return ExitCode;
}
