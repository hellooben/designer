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

extern LEXEME *evalSimpleOp(LEXEME *, LEXEME *);
// extern LEXEME *evalShortCircuitOp(LEXEME *, LEXEME *);
extern LEXEME *evalDot(LEXEME *, LEXEME *);
extern LEXEME *evalAssign(LEXEME *, LEXEME *);
extern LEXEME *evalVarDef(LEXEME *, LEXEME *);
extern LEXEME *evalFuncDef(LEXEME *, LEXEME *);
extern LEXEME *evalProgram(LEXEME *, LEXEME *);
extern LEXEME *evalIncludes(LEXEME *, LEXEME *);
extern LEXEME *evalInclude(LEXEME *, LEXEME *);
extern LEXEME *evalMain(LEXEME *, LEXEME *);
extern LEXEME *evalArgList(LEXEME *, LEXEME *);
extern LEXEME *evalBlock(LEXEME *, LEXEME *);
extern LEXEME *evalIf(LEXEME *, LEXEME *);
extern LEXEME *evalOptElse(LEXEME *, LEXEME *);
extern LEXEME *evalWhileLoop(LEXEME *, LEXEME *);
extern LEXEME *evalForLoop(LEXEME *, LEXEME *);
extern LEXEME *evalForCheck(LEXEME *, LEXEME *);
extern LEXEME *evalForOp(LEXEME *, LEXEME *);
extern LEXEME *evalFuncCall(LEXEME *, LEXEME *);
extern LEXEME *evalReturn(LEXEME *, LEXEME *);


#endif
