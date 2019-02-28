/***
Ben Bailey
eval.h
***/

#ifndef __EVAL_INCLUDED__
#define __EVAL_INCLUDED__

#include <stdio.h>
#include "types.h"
#include "recognize.h"

extern LEXEME *eval(LEXEME *, LEXEME *);

// extern LEXEME *evalSimpleOp(LEXEME *, LEXEME *);
// extern LEXEME *evalShortCircuitOp(LEXEME *, LEXEME *);
// extern LEXEME *evalDot(LEXEME *, LEXEME *);
extern LEXEME *evalAssign(LEXEME *, LEXEME *);
extern LEXEME *evalVarDef(LEXEME *, LEXEME *);
extern LEXEME *evalFuncDef(LEXEME *, LEXEME *);
extern LEXEME *evalProgram(LEXEME *, LEXEME *);
// extern LEXEME *evalIncludes(LEXEME *, LEXEME *);
// extern LEXEME *evalInclude(LEXEME *, LEXEME *);
extern LEXEME *evalUnary(LEXEME *, LEXEME *);
extern LEXEME *evalOp(LEXEME *, LEXEME *);
extern LEXEME *evalMain(LEXEME *, LEXEME *);
extern LEXEME *evalArgList(LEXEME *, LEXEME *);
extern LEXEME *evalBlock(LEXEME *, LEXEME *);
extern LEXEME *evalStatements(LEXEME *, LEXEME *);
extern LEXEME *evalStatement(LEXEME *, LEXEME *);
extern LEXEME *evalExpression(LEXEME *, LEXEME *);
extern LEXEME *evalIf(LEXEME *, LEXEME *);
extern LEXEME *evalOptElse(LEXEME *, LEXEME *);
extern LEXEME *evalWhileLoop(LEXEME *, LEXEME *);
extern LEXEME *evalForLoop(LEXEME *, LEXEME *);
extern LEXEME *evalForCheck(LEXEME *, LEXEME *);
extern LEXEME *evalForOp(LEXEME *, LEXEME *);
extern LEXEME *evalFuncCall(LEXEME *, LEXEME *);
extern LEXEME *evalLambda(LEXEME *, LEXEME *);
extern LEXEME *evalReturn(LEXEME *, LEXEME *);

extern LEXEME *evalSelfOp(LEXEME *, LEXEME *);
extern LEXEME *evalPlusPlus(LEXEME *, LEXEME *);
extern LEXEME *evalMinusMinus(LEXEME *, LEXEME *);
extern LEXEME *evalPlus(LEXEME *, LEXEME *);
extern LEXEME *evalMinus(LEXEME *, LEXEME *);
extern LEXEME *evalTimes(LEXEME *, LEXEME *);
extern LEXEME *evalDivide(LEXEME *, LEXEME *);
extern LEXEME *evalGreaterThan(LEXEME *, LEXEME *);
extern LEXEME *evalLessThan(LEXEME *, LEXEME *);
extern LEXEME *evalGreaterEquals(LEXEME *, LEXEME *);
extern LEXEME *evalLessEquals(LEXEME *, LEXEME *);
extern LEXEME *evalEqualsEquals(LEXEME *, LEXEME *);
extern LEXEME *evalMod(LEXEME *, LEXEME *);
extern LEXEME *evalNot(LEXEME *, LEXEME *);
extern LEXEME *evalAndAnd(LEXEME *, LEXEME *);
extern LEXEME *evalOrOr(LEXEME *, LEXEME *);
extern LEXEME *evalPlusEquals(LEXEME *, LEXEME *);
extern LEXEME *evalMinusEquals(LEXEME *, LEXEME *);
extern LEXEME *evalTimesEquals(LEXEME *, LEXEME *);
extern LEXEME *evalDivideEquals(LEXEME *, LEXEME *);

extern LEXEME *evalNewArray(LEXEME *, char *);
extern LEXEME *evalGetArray(LEXEME *, int, LEXEME *);
extern int getListSize(LEXEME *);
extern LEXEME *evalSetArray(LEXEME *, int, LEXEME *, LEXEME *);

extern LEXEME *evalBuiltin(LEXEME *, LEXEME *);
extern LEXEME *evalPrint(LEXEME *);
extern LEXEME *evalPrintNewLine(LEXEME *);
extern LEXEME *evalOpenFile(LEXEME *);
extern LEXEME *evalReadInteger(LEXEME *);
extern LEXEME *evalAtFileEnd(LEXEME *);
extern LEXEME *evalCloseFile(LEXEME *);


extern LEXEME *evalReturn(LEXEME *, LEXEME *);


#endif
