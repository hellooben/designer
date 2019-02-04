/***
Ben Bailey
recognize.h
***/

#ifndef __RECOGNIZE_INCLUDED__
#define __RECOGNIZE_INCLUDED__

#include <stdio.h>
#include "types.h"
#include "lexing.h"

extern int check(char *);
extern void advance();
extern void match(char *);
extern void matchNoAdvance(char *);
extern int parse(FILE *);



extern int program();
extern void includes();
extern void include();
extern void mainMethod();
extern void argList();
extern void block();
extern void statements();
extern void statement();
extern void expression();
extern void operator();
extern void unary();
extern void varDef();
extern void ifStatement();
extern void optElse();
extern void whileLoop();
extern void forLoop();
extern void funcDef();
extern void funcCall();
extern void returnStatement();
extern void forCheck();
extern void forOp();



extern int includesPending();
extern int optArgListPending();
extern int statementPending();
extern int expressionPending();
extern int unaryPending();
extern int returnPending();
extern int operatorPending();
extern int functionCallPending();
extern int arrayPending();

#endif
