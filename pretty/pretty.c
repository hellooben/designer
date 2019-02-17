/***
Ben Bailey
pp.c
***/

#include "pretty.h"
#include "lexing.h"
#include "types.h"
#include "recognize.h"
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
        printf("%f", getLEXEMEReal(tree));
    }
    else if (getType(tree) == STRING) {
        //fixLine(tree);
        printf("\"");
        printf("%s", getLEXEMEString(tree));
        printf("\"");
    }
    else if (getType(tree) == VOID) {
        printf("void");
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
    else if (getType(tree) == DOT) printf(".");
    else if (getType(tree) == MOD) printf("%%");
    else if (getType(tree) == NOT) printf("NOT");

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
    else if (getType(tree) == OPTELSE) printOptElse(tree);
    else if (getType(tree) == WHILELOOP) printWhileLoop(tree);
    else if (getType(tree) == FORLOOP) printForLoop(tree);
    else if (getType(tree) == FORCHECK) printForCheck(tree);
    else if (getType(tree) == FOROP) printForOp(tree);
    else if (getType(tree) == FUNCDEF) printFuncDef(tree);
    else if (getType(tree) == FUNCCALL) printFuncCall(tree);
    else if (getType(tree) == RETURNSTATEMENT) printReturn(tree);

}

/** PRINT FUNCTIONS **/
extern void
printProgram(LEXEME *l) {
    // printf("in PRINTPROGRAM\n");
    // printf("type is: %s\n", getType(l));
    if (car(l)) pp(car(l)); //includes
    if (cdr(l)) pp(cdr(l)); //main
}

extern void
printIncludes(LEXEME *l) {
    // printf("in PRINTINCLUDES\n");
    // while (l != NULL) {
    //     pp(car(l)); //include
    //     l = cdr(l); //includes
    // }
    pp(car(l));
    if (cdr(l)) pp(cdr(l));
}

extern void
printInclude(LEXEME *l) {
    // printf("in PRINTINCLUDE\n");
    printf("#include ");
    if (car(l)) {
        // printf("%s", getLEXEMEString(l)); //#include "pp.h"
        pp(car(l)); //#include "pp.h"
    }
    else {
        printf("<");
        printf("%s.", getLEXEMEString(car(cdr(l))));
        printf("%s>", getLEXEMEString(cdr(cdr(l)))); //#include <stdio.h>
    }
    printf("\n");
}

extern void
printMain(LEXEME *l) {
    printf("main (");
    if (car(l)) {
        pp(car(l)); //argList
    }
    printf(")");
    pp(cdr(l)); //block
    printf("\n}");
}

extern void
printArgList(LEXEME *l) {
    pp(car(l)); //expression
    if (cdr(l)) {
        printf(",");
        pp(cdr(l)); //argList
    }
}

extern void
printBlock(LEXEME *l) {
    printf(" {");
    if (car(l)) pp(car(l)); //statements
}

extern void
printStatements(LEXEME *l) {
    printf("\n");
    pp(car(l)); //statement
    printf("!");
    if (cdr(l)) pp(cdr(l)); //statements
}

extern void
printStatement(LEXEME *l) {
    if (car(l)) pp(car(l)); //varDef, ifStatement, whileLoop, forLoop, funcDef, returnStatement, expression
}

extern void
printExpression(LEXEME *l) {
    pp(car(l)); //unary, funcCall
    if (car(cdr(l))) {
        pp(car(cdr(l))); //operator
        pp(cdr(cdr(l))); //expression
    }
}

extern void
printOperator(LEXEME *l) {
    if (car(l)) pp(car(l)); //operator
}

extern void
printUnary(LEXEME *l) {
    if (car(l)) pp(car(l)); //unary
}

extern void
printVarDef(LEXEME *l) {
    printf("var ");
    pp(car(l)); //variable name
    if (cdr(l)) {
        if (getType(cdr(l)) == ARGLIST) {
            printf("[");
            if (cdr(l)) pp(cdr(l)); //array list
            printf("]");
        }
        else {
            printf(" = ");
            pp(cdr(l)); //expression
        }
    }
    else {
        printf("[]");
    }
    // if (cdr(l)) pp(cdr(l)); //
}

extern void
printIfStatement(LEXEME *l) {
    printf("if (");
    if (car(l)) pp(car(l)); //expression
    printf(")");
    pp(car(cdr(l))); //block
    printf("\n}");
    if (cdr(cdr(l))) {
        pp(cdr(cdr(l))); //optElse
        // printf("\n}");
    }
}

extern void
printOptElse(LEXEME *l) {
    printf("\nelse ");
    if (getType(car(l)) == BLOCK) {
        pp(car(l)); //block
        printf("\n}");
    }
    else {
        pp(car(l));
        // printf("\n}");
    }
}

extern void
printWhileLoop(LEXEME *l) {
    printf("while (");
    pp(car(l)); //expression
    printf(")");
    pp(cdr(l)); //block
    printf("\n}");
}

extern void
printForLoop(LEXEME *l) {
    printf("for (");
    pp(car(car(car(l)))); //unary or variable
    printf(" = ");
    pp(cdr(car(car(l)))); //unary or variable
    printf("; ");
    pp(car(cdr(car(cdr(car(l)))))); //unary or variable
    pp(car(car(cdr(car(l))))); //forCheck
    pp(cdr(cdr(car(cdr(car(l)))))); //unary or variable
    printf("; ");
    pp(cdr(cdr(cdr(car(l))))); //unary or variable
    pp(car(cdr(cdr(car(l))))); //forOp
    printf(")");
    pp(cdr(l)); //block
    printf("\n}");
}

extern void
printFuncDef(LEXEME *l) {
    printf("method ");
    pp(car(car(l))); //function name
    printf("(");
    if (cdr(car(l))) pp(cdr(car(l)));
    printf(")");
    pp(car(cdr(l))); //block
    if (cdr(cdr(l))) pp(cdr(cdr(l))); //returnStatement
    printf("\n}");
}

extern void
printFuncCall(LEXEME *l) {
    // printf("printing a function call\n");
    pp(car(l)); //function name
    printf("(");
    if (cdr(l)) pp(cdr(l)); //argList
    printf(")");
}

extern void
printReturn(LEXEME *l) {
    if (car(l) || cdr(l)) {
        printf("return ");
        if (car(l)) pp(car(l)); //expression
        else pp(cdr(l)); //unary
    }
    else printf("return"); //neither
}

extern void
printForCheck(LEXEME *l) {
    pp(car(l)); //lessthan, greaterthan, LESSEQUALS, GREATEREQUALS
}

extern void
printForOp(LEXEME *l) {
    if (cdr(l)) {
        pp(car(l)); //operator
        pp(cdr(l)); //expression
    }
    else pp(car(l)); //operator
}
