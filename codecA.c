#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "codec.h"

void encodeA(char *c) {
    while( *c != '\0') 
    {
        if( islower(*c) ) // islower = check is the character is lowercase alphabet
            *c = toupper(*c);

        else if( isupper(*c) ) // isupper = check is the character is an uppercase alphabet
            *c = tolower(*c);

        c++;
    }
}

void decodeA(char *c) {
    encodeA(c);
}