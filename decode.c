#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <dlfcn.h>
unsigned char* (*decode)(unsigned char*, size_t);

bool isCCode(char* codec) {
    return (strcmp(codec, "codecA") == 0 || strcmp(codec, "codecB") == 0);
}

int main(int argc, char** argv) {
    void* h = NULL;
    unsigned char* dec = NULL;
    size_t length = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <codec type> <text>\n", *(argv));
        return 1;
    }

    if (!isCCode(*(argv + 1))) {
        fprintf(stderr, "error - decode: illegal code. Must be codecA or codecB.\n");
        return 1;
    }

    if (!(length = strlen(*(argv + 2)))) {
        fprintf(stderr, "error - decode: text can't be empty.\n");
        return 1;
    }

    if ((h = dlopen((strcmp( *(argv + 1), "codecA") == 0 ? "./libcodecA.so":"./libcodecB.so"), RTLD_LAZY)) == NULL) {
        fprintf(stderr, "error - decode: %s\n", dlerror());
        return 1;
    }

    if ((dec = decode((unsigned char*)*(argv + 2), length)) == NULL) {
        fprintf(stderr, "error - decode: malloc failed.\n");
        return 1;
    }

    if ((dec = dlsym(h, "decode")) == NULL) {
        fprintf(stderr, "error - decode: %s\n", dlerror());
        return 1;
    }


    fprintf(stdout, "%s\n", dec);
    dlclose(h);
    free(dec);
    return 0;
}