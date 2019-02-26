/***
Ben Bailey
pp.h
***/

#ifndef __PRETTY_INCLUDED__
#define __PRETTY_INCLUDED__

#include <stdio.h>
#include "lexing.h"
#include "types.h"

extern void pp(LEXEME *);

extern void printProgram(LEXEME *);
extern void printIncludes(LEXEME *);
extern void printInclude(LEXEME *);
extern void printMain(LEXEME *);
extern void printArgList(LEXEME *);
extern void printBlock(LEXEME *);
extern void printStatements(LEXEME *);
extern void printStatement(LEXEME *);
extern void printExpression(LEXEME *);
extern void printOperator(LEXEME *);
extern void printUnary(LEXEME *);
extern void printLambda(LEXEME *);
extern void printVarDef(LEXEME *);
extern void printIfStatement(LEXEME *);
extern void printOptElse(LEXEME *);
extern void printWhileLoop(LEXEME *);
extern void printForLoop(LEXEME *);
extern void printFuncCall(LEXEME *);
extern void printFuncDef(LEXEME *);
extern void printReturn(LEXEME *);
extern void printForCheck(LEXEME *);
extern void printForOp(LEXEME *);

#endif
