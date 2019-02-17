/***
Ben Bailey
pp.c
***/

#include "pp.h"
#include "lexing.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void
pp(LEXEME *tree) {
    if (getType(tree) == INTEGER) {
        //fixLine(tree);
        printf("%d", getLEXEMEInt(tree));
    }
    else if (getType(tree) == REAL) {
        //fixLine(tree);
        printf("%lf", getLEXEMEReal(tree));
    }
    else if (getType(tree) == STRING) {
        //fixLine(tree);
        printf("\"");
        printf("%s", getLEXEMEString(tree));
        printf("\"");
    }
    else if (getType(tree) == VARIABLE) {
        //fixLine(tree);
        printf("%s", getLEXEMEString(tree));
    }
    else if (getType(tree) == POUND) printf("#");
    else if (getType(tree) == LESSTHAN) printf("<");
    else if (getType(tree) == GREATERTHAN) printf(">");
    else if (getType(tree) == GREATEREQUALS) printf(">=");
    else if (getType(tree) == LESSEQUALS) printf("<=");
    else if (getType(tree) == ASSIGN) printf("=");
    else if (getType(tree) == PLUS) printf("+");
    else if (getType(tree) == MINUS) printf("-");
    else if (getType(tree) == DIVIDE) printf("/");
    else if (getType(tree) == TIMES) printf("*");
    else if (getType(tree) == ANDAND) printf("&&");
    else if (getType(tree) == OROR) printf("||");
    else if (getType(tree) == EQUALSEQUALS) printf("==");
    else if (getType(tree) == PLUSPLUS) printf("++");
    else if (getType(tree) == MINUSMINUS) printf("--");
    else if (getType(tree) == PEQUALS) printf("+=");
    else if (getType(tree) == MINUESEQUALS) printf("-=");
    else if (getType(tree) == TIMESEQUALS) printf("*=");
    else if (getType(tree) == DIVIDEEQUALS) printf("/=");

    else if (getType(tree) == PROGRAM) printProgram(tree);
    else if (getType(tree) == INCLUDES) printIncludes(tree);
    else if (getType(tree) == INCLUDE) printInclude(tree);
    else if (getType(tree) == MAINMETHOD) printMain(tree);
    else if (getType(tree) == ARGLIST) printArgList(tree);
    else if (getType(tree) == BLOCK) printBlock(tree);
    else if (getType(tree) == STATEMENTS) printStatements(tree);
    else if (getType(tree) == STATEMENT) printStatement(tree);
    else if (getType(tree) == EXPRESSION) printExpression(tree);
    else if (getType(tree) == OPERATOR) printOperator(tree);
    else if (getType(tree) == UNARY) printUnary(tree);
    else if (getType(tree) == VARDEF) printVarDef(tree);
    else if (getType(tree) == IFSTATEMENT) printIfStatement(tree);
    else if (getType(tree) == WHILELOOP) printWhileLoop(tree);
    else if (getType(tree) == FORLOOP) printForLoop(tree);
    else if (getType(tree) == FUNCDEF) printFuncDef(tree);
    else if (getType(tree) == FUNCCALL) printFuncCall(tree);
    else if (getType(tree) == RETURNSTATEMENT) printReturn(tree);

}
