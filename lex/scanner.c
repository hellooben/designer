/***
Ben Bailey
scanner.c
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexing.h"
#include "types.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Incorrect arguments. Exiting...\n");
        return 1;
    }

    FILE *fp = fopen(argv[argc-1], "r");

    LEXEME *l = lex(fp);
    while (!feof(fp)) {
        if (strcmp(getType(l), "UNKNOWN") == 0 || strcmp(getType(l), "BAD NUMBER") == 0) {
            printf("Error found on line number %d. Exiting...\n", getLEXEMEInt(l));
            return 1;
        }
        displayLEXEME(l);
        l = lex(fp);
    }
    printf("ENDofINPUT\n");
    return 0;
}
