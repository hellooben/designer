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
    if (argc != 2) {
        printf("Incorrect arguments. Exiting...\n");
        return 1;
    }

    FILE *fp = fopen(argv[argc-1], "r");
    int res = parse(fp);

    printf("RESULT : %d\n", res);
    return 0;
}
