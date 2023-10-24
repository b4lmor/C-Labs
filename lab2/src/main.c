#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

#define MAX_ASCII_LETTER (256)

#define READ_ERROR 101
#define BAD_INPUT 102

void swap(char * a, char * b){
    char t = *a;
    *a = *b;
    *b = t;
}

int NextPermutation(char string[]) {

    int length = strlen(string);

	if (!length){
		return EXIT_FAILURE;
    }

	int i = length - 1;
	while (i && string[i - 1] >= string[i]){
		i--;
    }
	if (!i){
		return EXIT_FAILURE;
    }
	
	int j = length - 1;
	while (string[j] <= string[i - 1]){
		j--;
    }

    swap(&string[j], &string[i-1]);

	j = length - 1;
	while (i < j) {
		swap(&string[j--], &string[i++]);
	}

	return EXIT_SUCCESS;
}

char NoDuplicates(char string[]){

    char asciiLetters[MAX_ASCII_LETTER] = { 0 };

    char * ptr = string;
    while(*ptr) {
        if(asciiLetters[(unsigned) *ptr]){
            return FALSE;
        }
        asciiLetters[(unsigned) *ptr++] = 1;
    }
    return TRUE;
}

char AllDigits(char string[]){

    char * ptr = string;
    while(*ptr) {
        if ( !isdigit(*ptr++) ){
            return FALSE;
        }
    }
    return TRUE;
}

int main(){

    int ExitCode = EXIT_SUCCESS;
    char str[14];
    int N;

    if (1 != scanf("%12[^\n]", str)) {
        ExitCode = READ_ERROR;
        goto exit_marker;
    }
    if (1 != scanf("%i", &N)) {
        ExitCode = READ_ERROR;
        goto exit_marker;
    }

    if (FALSE == NoDuplicates(str)) {
        ExitCode = BAD_INPUT;
        goto exit_marker;
    }
    if ( FALSE == AllDigits(str) ) {
        ExitCode = BAD_INPUT;
        goto exit_marker;
    }

    for(int i = 0; i < N; i++){
        if (EXIT_SUCCESS == NextPermutation(str)){
            printf("%s\n", str);
        } else {
            break;
        }
    }

    exit_marker:

    if (ExitCode == BAD_INPUT) {
        printf("bad input\n");
        ExitCode = EXIT_SUCCESS;
    }

    return ExitCode;
}
