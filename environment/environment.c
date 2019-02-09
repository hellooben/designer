/***
Ben Bailey
environment.c
***/

#include "environment.h"
#include <stdio.h>
#include "lexing.h"
#include "types.h"


extern LEXEME *
cons(char *type, LEXEME *left, LEXEME *right) {
    LEXEME *p = newLEXEME(type);
    setLEXEMEleft(p, left);
    setLEXEMEright(p, right);
    return p;
}

extern LEXEME *
car(LEXEME *p) {
    return getLEXEMEleft(p);
}

extern LEXEME *
cdr(LEXEME *p) {
    return getLEXEMEright(p);
}

extern LEXEME *
setCar(LEXEME *l, LEXEME *new) {
    setLEXEMEleft(l, new);
    return getLEXEMEleft(l);
}

extern LEXEME *
setCdr(LEXEME *l, LEXEME *new) {
    setLEXEMEright(l, new);
    return getLEXEMEright(l);
}
