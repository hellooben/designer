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
        print("Incorrect arguments. Exiting...\n");
        return 1;
    }

    FILE *fp = fopen(argc[argc-1], "r");
    parse(fp);

    return 0;
}
