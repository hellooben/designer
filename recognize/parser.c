/***
Ben Bailey
parser.c
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recognize.h"
#include "types.h"

int main(int argc, char **argv) {
    printf("hellooo\n");
    if (argc != 2) {
        printf("Incorrect arguments. Exiting...\n");
        return 1;
    }

    FILE *fp = fopen(argv[argc-1], "r");
    int res = parse(fp);

    if (res == 0) printf("legal\n");
    else printf("illegal\n");
    return 0;
}
