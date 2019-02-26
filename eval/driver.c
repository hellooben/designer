/***
Ben Bailey
driver.c
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexing.h"
#include "types.h"
#include "environment.h"
#include "eval.h"
#include "recognize.h"
#include "pretty.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Incorrect arguments. Exiting...\n");
        return 1;
    }

    FILE *fp = fopen(argv[argc-1], "r");

    LEXEME *tree = parse(fp);

    pp(tree);
    printf("\n");
    LEXEME *env = create();
    printf("Environment created\n");
    insert(newLEXEMEString(VARIABLE, "print"), env, newLEXEMEBuiltin(evalPrint));
    insert(newLEXEMEString(VARIABLE, "printNewLine"), env, newLEXEMEBuiltin(evalPrintNewLine));
    printf("Inserted builtin functions\n");
    LEXEME *e = eval(tree, env);

    if (e) printf("hello\n");
}
