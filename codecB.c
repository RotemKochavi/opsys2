#include <stdlib.h>
#include <stdio.h>
#include "codec.h"

void encodeB(char *c) {
    while( *c != '\0' )
    {
        *c += 3;
        c++;
    }
}

void decodeB(char *c) {
    while( *c != '\0' )
    {
        *c -= 3;
        c++;
    }
}
