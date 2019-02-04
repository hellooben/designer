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
extern void parse(FILE *);



extern void program();
extern void include();
extern void main();
extern void argList();
extern void block();
extern void statements();
extern void statement();
extern void expression();
extern void unary();
extern void varDef();
extern void ifStatement();
extern void optElse();
extern void whileLoop();
extern void forLoop();



extern int includesPending();
extern int optArgListPending();
extern int statementPending();
extern int expressionPending();
extern int unaryPending();
extern int returnPending();
extern int operatorPending();
