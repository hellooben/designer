/***
Ben Bailey
environment.h
***/

#ifndef __ENVIRONMENT_INCLUDED__
#define __ENVIRONMENT_INCLUDED__

#include <stdio.h>
#include "lexing.h"
#include "types.h"


extern LEXEME *cons(char *, LEXEME *, LEXEME *);
extern LEXEME *car(LEXEME *);
extern LEXEME *cdr(LEXEME *);
extern LEXEME *setCar(LEXEME *, LEXEME *);
extern LEXEME *setCdr(LEXEME *, LEXEME *);
extern int sameVariable(LEXEME *, LEXEME *);


extern LEXEME *create();
extern LEXEME *lookup(LEXEME *, LEXEME *);
extern LEXEME *update(LEXEME *, LEXEME *, LEXEME *);
extern LEXEME *insert(LEXEME *, LEXEME *, LEXEME *);
extern LEXEME *extend(LEXEME *, LEXEME *, LEXEME *);

extern void display(LEXEME *);
extern void displayLocal(LEXEME *);

#endif
