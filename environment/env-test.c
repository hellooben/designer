/***
Ben Bailey
env-test.c
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexing.h"
#include "types.h"
#include "environment.h"

int main() {
    LEXEME *env = create();
    display(env);
}
