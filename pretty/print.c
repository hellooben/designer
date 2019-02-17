/***
Ben Bailey
print.c
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recognize.h"
#include "types.h"
#include "pp.h"
#include "lexing.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Incorrect arguments. Exiting...\n");
        return 1;
    }

    FILE *fp = fopen(argv[argc-1], "r");
    LEXEME *tree = parse(fp);
    if (tree) printf("TREE BUILT\n");

    return 0;
}
