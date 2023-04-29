#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <dlfcn.h>

typedef enum {
    SUCCESS = 0,
    FAIL = 1
} encode_res;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: ./encode <codec> <message>\n ");
        return FAIL;
    }
    
    char *method = argv[1];
    char *message = argv[2];
    
    if ( !strcmp(method, "codecA") ) {
        encodeA(message);
        printf( "%s\n", message );
    }

    else if ( !strcmp(method, "codecB") ) {
        encodeB(message);
        printf( "%s\n", message );
    }

    else {
        fprintf(stderr, "Usage: ./decode <codec> <message>\n");
        return FAIL;
    }

    return SUCCESS;
}


