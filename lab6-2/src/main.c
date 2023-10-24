#include <stdlib.h>
#include <stdio.h>

#include "BTree.h"
#include "errors.h"

int main(void) {

    FILE * in = fopen("in.txt", "r");
    FILE * out = fopen("out.txt", "w");

    int ExitCode = EXIT_SUCCESS;

    int T;
    if (1 != fscanf(in, "%i", &T)){
        ExitCode = READ_ERROR;
        goto exit_marker;
    }
    if (2000 < T || T < 2){
        ExitCode = BAD_DEGREE;
        goto exit_marker;
    }

    int N;
    if (1 != fscanf(in, "%i", &N)){
        ExitCode = BAD_NUMBER_OF_KEYS;
        goto exit_marker;
    }
    if (N == 0){
        fprintf(out, "0\n");
        ExitCode = EXIT_SUCCESS;
        goto exit_marker;
    } 

    BTree * Root = NULL;
    
	int key;
	for (int i = 0; i < N; i++){
		if (1 != fscanf(in, "%i", &key)){
			ExitCode = READ_ERROR;
            goto exit_marker;
		}
        
        ExitCode = Insert(&Root, key, T);
		if (ExitCode == MEMORY_ALLOCATION_ERROR) {
            FreeBTree(Root, T);
            goto exit_marker;
        }
	}

	fprintf(out, "%i\n", GetHeight(Root));

    FreeBTree(Root, T);

    exit_marker:

    fclose(in);
    fclose(out);

    return ExitCode;
}
