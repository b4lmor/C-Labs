#include <stdlib.h>
#include <stdio.h>

#include "RBTree.h"
#include "errors.h"

int main(void) {

    int ExitCode = EXIT_SUCCESS;

    int N;
    if (1 != scanf("%i", &N)){
        ExitCode = READ_ERROR;
        goto exit_marker;
    }
    if (N == 0){
        printf("0\n");
        ExitCode = EXIT_SUCCESS;
        goto exit_marker;
    }

    Node_t * Root = NULL;
    Node_t * memoryStorage = malloc(N * sizeof(Node_t));
    if (memoryStorage == NULL) {
        ExitCode = MEMORY_ALLOCATION_ERROR;
        goto exit_marker;
    }
    
	int key;
	for (int i = 0; i < N; i++){
		if (1 != scanf("%i", &key)){
			ExitCode = READ_ERROR;
            goto exit_marker;
		}
		Root = Insert(Root, key, i, memoryStorage);
	}

	printf("%i\n", GetHeight(Root));

    free(memoryStorage);

    exit_marker:

    return ExitCode;
}
