#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "compression.h"
#include "decompression.h"

#define INPUT_NAME ("in.txt")
#define OUTPUT_NAME ("out.txt")

enum errorCodes {
    BAD_PARAMETERS = 101,
    OPEN_FILE_ERROR,
    CLOSE_FILE_ERROR,
    UNKNOWN_MODE,

    MEMORY_ALLOCATION_ERROR = 201,
    STRNCPY_ERROR,
};

int main(int argc, char * argv[]) {

    FILE * input;
    FILE * output;

    int ExitCode = EXIT_SUCCESS;
    _Bool IsArgFiles; 

    char * inputName;
    char * outputName;

    switch (argc) {
        case 1:
            inputName = INPUT_NAME;
            outputName = OUTPUT_NAME;
            IsArgFiles = false;
            break;
        case 4:
            inputName = argv[1];
            outputName = argv[2];
            IsArgFiles = true;
            break;
        default:
            ExitCode = BAD_PARAMETERS;
            goto exit_marker;
            break;
    }

    if ( (input = fopen(inputName, "rb")) == NULL ){
        ExitCode = OPEN_FILE_ERROR;
        goto exit_marker;
    }
    if ( (output = fopen(outputName, "wb")) == NULL ){
        if (fclose(input)){
            ExitCode = CLOSE_FILE_ERROR;
            goto exit_marker;
        }
        ExitCode = OPEN_FILE_ERROR;
        goto exit_marker;
    }

    char mode = IsArgFiles ? argv[3][0] : fgetc(input);

    switch (mode) {
        case 'c':
            compress(input, output, IsArgFiles);
            break;
        case 'd':
            ExitCode = decompress(input, output);
            break;
        default:
            ExitCode = UNKNOWN_MODE;
    }

    if (fclose(input) || fclose(output)){
        ExitCode = CLOSE_FILE_ERROR;
    }

    exit_marker:

    return ExitCode;
}
