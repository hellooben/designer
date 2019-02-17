/***
Ben Bailey
recognize.h
***/

#ifndef __RECOGNIZE_INCLUDED__
#define __RECOGNIZE_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "lexing.h"
#include "pp.h"

extern int check(char *);
extern LEXEME *advance();
extern LEXEME *match(char *);
extern void matchNoAdvance(char *);

extern LEXEME *cons(char *, LEXEME *, LEXEME *);
extern LEXEME *car(LEXEME *);
extern LEXEME *cdr(LEXEME *);
extern LEXEME *setCar(LEXEME *, LEXEME *);
extern LEXEME *setCdr(LEXEME *, LEXEME *);

extern LEXEME *program();
extern LEXEME *includes();
extern LEXEME *include();
extern LEXEME *mainMethod();
extern LEXEME *argList();
extern LEXEME *block();
extern LEXEME *statements();
extern LEXEME *statement();
extern LEXEME *expression();
extern LEXEME *operator();
extern LEXEME *unary();
extern LEXEME *varDef();
extern LEXEME *ifStatement();
extern LEXEME *optElse();
extern LEXEME *whileLoop();
extern LEXEME *forLoop();
extern LEXEME *funcDef();
extern LEXEME *funcCall();
extern LEXEME *returnStatement();
extern LEXEME *forCheck();
extern LEXEME *forOp();



extern int includesPending();
extern int optArgListPending();
extern int statementPending();
extern int expressionPending();
extern int unaryPending();
extern int returnPending();
extern int operatorPending();
extern int functionCallPending();
extern int arrayPending();

extern LEXEME *parse(FILE *);

#endif
