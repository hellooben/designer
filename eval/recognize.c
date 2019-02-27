/***
Ben Bailey
recognize.c
***/

/** INCLUDES **/
#include "recognize.h"
#include "environment.h"
#include "lexing.h"
#include "types.h"
// #include "pp.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

LEXEME *currentLexeme;
LEXEME *prevLexeme;
FILE *fp;
int error = 0;

/** LEXICAL INTERFACE FUNCTIONS **/
extern int
check(char *type) {
    // printf("Checking if CURRENT( %s ) equals PASSED( %s )\n", getType(currentLexeme), type);
    if (getType(currentLexeme) == type) {
        return 1;
    }
    return 0;
}

extern LEXEME *
advance() {
    prevLexeme = currentLexeme;
    currentLexeme = lex(fp);
    return prevLexeme;
}

extern LEXEME *
match(char *type) {
    matchNoAdvance(type);
    return advance();
}

extern void
matchNoAdvance(char *type) {
    // printf("Trying to match CURRENT( %s ) and PASSED( %s )\n", getType(currentLexeme), type);
    if (check(type) == 0) {
        // printf("!!!!!!!!!!!!------- FOUND A SYNTAX ERROR -------!!!!!!!!!!!!\n\n\n\n");
        printf("FATAL: Syntax error before or on line %d\n", getLEXEMEline(currentLexeme));
        printf("Tried to match CURRENT( %s ) with EXPECTED( %s )\nILLEGAL\n", getType(currentLexeme), type);
        error = 1;
        exit(0);
    }
    // else {
    //     // printf("MATCHED %s\n", getType(currentLexeme));
    // }
}


// int sameVariable(LEXEME *l1, LEXEME *l2) {
//     if (strcmp(getType(l1), getType(l2)) == 0) {
//         if (strcmp(getLEXEMEString(l1), getLEXEMEString(l2)) == 0) {
//             return 1;
//         }
//     }
//     return 0;
// }
//
//
// /** TREE FUNCTIONS **/
// extern LEXEME *
// cons(char *type, LEXEME *left, LEXEME *right) {
//     LEXEME *p = newLEXEME(type);
//     setLEXEMEleft(p, left);
//     setLEXEMEright(p, right);
//     return p;
// }
//
// extern LEXEME *
// car(LEXEME *p) {
//     return getLEXEMEleft(p);
// }
//
// extern LEXEME *
// cdr(LEXEME *p) {
//     return getLEXEMEright(p);
// }
//
// extern LEXEME *
// setCar(LEXEME *l, LEXEME *new) {
//     setLEXEMEleft(l, new);
//     return getLEXEMEleft(l);
// }
//
// extern LEXEME *
// setCdr(LEXEME *l, LEXEME *new) {
//     setLEXEMEright(l, new);
//     return getLEXEMEright(l);
// }


/** MATCHING FUNCTIONS **/
extern LEXEME *
parse(FILE *file) {
    fp = file;
    LEXEME *returnable = advance();
    returnable = program();
    if (error) return NULL;
    return returnable;
}

extern LEXEME *
program() {
    LEXEME *i, *m;
    if (includesPending()) {
        i = includes();
    }
    else i = NULL;
    m = mainMethod();
    match(ENDOFINPUT);
    return cons(PROGRAM, i, m);
}

extern LEXEME *
includes() {
    LEXEME *i, *s;
    i = include();
    if (includesPending()) {
        s = includes();
    }
    else s = NULL;
    return cons(INCLUDES, i, s);
}

extern LEXEME *
include() {
    LEXEME *full, *ldot, *rdot;
    match(POUND);
    match(INCLUDE);
    if (check(LESSTHAN)) {
        match(LESSTHAN);
        ldot = match(VARIABLE);
        match(DOT);
        rdot = match(VARIABLE);
        match(GREATERTHAN);
        full = NULL;
    }
    else if (check(STRING)) {
        full = match(STRING);
        ldot = NULL;
        rdot = NULL;
    }
    else {
        printf("FATAL: Syntax error before or on line %d\nillegal\n", getLEXEMEline(currentLexeme));
        error = 1;
        exit(0);
        full = NULL;
        ldot = NULL;
        rdot = NULL;
    }
    return cons(INCLUDE, full, cons(GLUE, ldot, rdot));
}

extern LEXEME *
mainMethod() {
    LEXEME *arg, *b;
    match(MAIN);
    match(OPAREN);
    if (optArgListPending()) {
        arg = argList();
    }
    else arg = NULL;
    match(CPAREN);
    b = block();
    match(CBRACE);
    return cons(MAINMETHOD, arg, b);
}

extern LEXEME *
argList() {
    LEXEME *exp, *arg;
    exp = expression();
    if (check(COMMA)) {
        match(COMMA);
        arg = argList();
    }
    else arg = NULL;
    return cons(ARGLIST, exp, arg);
}

extern LEXEME *
paramList() {
    LEXEME *v, *p;
    v = match(VARIABLE);
    if (check(COMMA)) {
        match(COMMA);
        p = paramList();
    }
    else p = NULL;
    return cons(PARAMLIST, v, p);
}

extern LEXEME *
block() {
    LEXEME *s;
    match(OBRACE);
    s = statements();
    return cons(BLOCK, s, NULL);
}

extern LEXEME *
statements() {
    if (statementPending()) {
        LEXEME *s, *ss;
        s = statement();
        match(EXCL);
        ss = statements();
        return cons(STATEMENTS, s, ss);
    }
    else return NULL;
}

extern LEXEME *
statement() {
    LEXEME *statement;
    if (check(VAR)) {
        statement = varDef();
    }
    else if (check(IF)) {
        statement = ifStatement();
    }
    else if (check(WHILE)) {
        statement = whileLoop();
    }
    else if (check(FOR)) {
        statement = forLoop();
    }
    else if (check(METHOD)) {
        statement = funcDef();
    }
    else if (returnPending()) {
        statement = returnStatement();
    }
    else if (expressionPending()) {
        // printf("statement going for expression\n");
        statement = expression();
    }
    else statement = NULL;
    return cons(STATEMENT, statement, NULL);
}

extern LEXEME *
expression() {
    LEXEME *u, *o, *e, *f, *v, *i;
    if (unaryPending()) {
        // printf("found a unary\n");
        u = unary();
        if (operatorPending()) {
            o = operator();
            e = expression();
        }
        else {
            o = NULL;
            e = NULL;
        }
        return cons(EXPRESSION, u, cons(GLUE, o, e));
    }
    else {
        // printf("going for variable\n");
        v = match(VARIABLE);
        if (check(OPAREN)) {
            match(OPAREN);
            // printf("it's a function call\n");
            f = funcCall(v);
            if (operatorPending()) {
                o = operator();
                e = expression();
            }
            else {
                o = NULL;
                e = NULL;
            }
            return cons(EXPRESSION, f, cons(GLUE, o, e));
        }
        else if (check(OBRACKET)) {
            match(OBRACKET);
            if (check(INTEGER)) i = match(INTEGER);
            else if (check(VARIABLE)) i = match(VARIABLE);
            else i = NULL;
            match(CBRACKET);
            if (i != NULL && operatorPending()) {
                o = operator();
                if (expressionPending() || unaryPending()) e = expression();
                else e = NULL;
            }
            else {
                o = NULL;
                e = NULL;
            }
            return cons(EXPRESSION, cons(GLUE, v, i), cons(GLUE, o, e));
        }
        else if (operatorPending()) {
            // printf("in expression operator pending \n");
            o = operator();
            if (expressionPending() || unaryPending()) e = expression();
            else e = NULL;
        }
        else {
            o = NULL;
            e = NULL;
        }
        return cons(EXPRESSION, v, cons(GLUE, o, e));
    }
    // else if (expressionPending()) {
    //     printf("found a variable\n");
    //     v = expression();
    //     if (operatorPending()) {
    //         o = operator();
    //         e = expression();
    //     }
    //     else {
    //         o = NULL;
    //         e = NULL;
    //     }
    //     return cons(EXPRESSION, v, cons(GLUE, o, e));
    // }
    // else {
    //     printf("it's a funcion call\n");
    //     f = funcCall();
    //     if (operatorPending()) {
    //         o = operator();
    //         e = expression();
    //     }
    //     else {
    //         o = NULL;
    //         e = NULL;
    //     }
    //     return cons(EXPRESSION, f, cons(GLUE, o, e));
    // }
}

extern LEXEME *
operator() {
    LEXEME *op;
    if (check(PLUS)) op = match(PLUS);
    else if (check(MINUS)) op = match(MINUS);
    else if (check(TIMES)) op = match(TIMES);
    else if (check(DIVIDE)) op = match(DIVIDE);
    else if (check(ASSIGN)) op = match(ASSIGN);
    else if (check(GREATERTHAN)) op = match(GREATERTHAN);
    else if (check(LESSTHAN)) op = match(LESSTHAN);
    else if (check(GREATEREQUALS)) op = match(GREATEREQUALS);
    else if (check(LESSEQUALS)) op = match(LESSEQUALS);
    else if (check(DOT)) op = match(DOT);
    else if (check(MOD)) op = match(MOD);
    else if (check(NOT)) op = match(NOT);
    else if (check(EQUALSEQUALS)) op = match(EQUALSEQUALS);
    else if (check(PLUSPLUS)) op = match(PLUSPLUS);
    else if (check(MINUSMINUS)) op = match(MINUSMINUS);
    else if (check(PEQUALS)) op = match(PEQUALS);
    else if (check(MINUSEQUALS)) op = match(MINUSEQUALS);
    else if (check(TIMESEQUALS)) op = match(TIMESEQUALS);
    else if (check(DIVIDEEQUALS)) op = match(DIVIDEEQUALS);
    else if (check(ANDAND)) op = match(ANDAND);
    else if (check(OROR)) op = match(OROR);
    else op = NULL;
    return cons(OPERATOR, op, NULL);
}

extern LEXEME *
unary() {
    LEXEME *u;
    if (check(INTEGER)) u = match(INTEGER);
    else if (check(STRING)) u = match(STRING);
    else if (check(REAL)) u = match(REAL);
    else if (check(VOID)) u = match(VOID);
    else if (check(LAMBDA)) u = lambda();
    // else if (check(VARIABLE)) u = match(VARIABLE);
    else u = NULL;
    return cons(UNARY, u, NULL);
}

extern LEXEME *
lambda() {
    LEXEME *arg, *b;
    match(LAMBDA);
    match(OPAREN);
    if (optArgListPending()) arg = paramList();
    else arg = NULL;
    match(CPAREN);
    b = block();
    match(CBRACE);
    return cons(LAMBDA, NULL, cons(GLUE, arg, b));
}

extern LEXEME *
varDef() {
    LEXEME *var, *list, *expr;
    match(VAR);
    var = match(VARIABLE);
    if (arrayPending()) {
        match(OBRACKET);
        if (optArgListPending()) {
            list = argList();
        }
        else list = NULL;
        match(CBRACKET);
        return cons(VARDEF, var, list);
    }
    else if (check(ASSIGN)) {
        // printf("there is assign\n");
        match(ASSIGN);
        expr = expression();
        return cons(VARDEF, var, expr);
    }
    else {
        // printf("---- looks like variable definition. can't understand ----\n");

        printf("FATAL: Syntax error before or on line %d\nIllegal variable definition.\n", getLEXEMEline(currentLexeme));
        error = 1;
        exit(0);
    }
}

extern LEXEME *
ifStatement() {
    LEXEME *expr, *b, *o;
    match(IF);
    match(OPAREN);
    expr = expression();
    match(CPAREN);
    b = block();
    match(CBRACE);
    if (check(ELSE)) {
        o = optElse();
        // return cons(IFSTATEMENT, expr, cons(GLUE, b, o));
    }
    else o = NULL;
    return cons(IFSTATEMENT, expr, cons(GLUE, b, o));
    // else return cons(IFSTATEMENT, expr, b);
}

extern LEXEME *
optElse() {
    LEXEME *i, *b;
    match(ELSE);
    if (check(IF)) {
        // printf("found another if\n");
        i = ifStatement();
    }
    else i = NULL;
    if (i == NULL) {
        b = block();
        match(CBRACE);
        // printf("returning from optelse\n");
        return cons(OPTELSE, b, NULL);
    }
    else {
        b = NULL;
        return cons(OPTELSE, i, NULL);
    }

}

extern LEXEME *
whileLoop() {
    LEXEME *expr, *b;
    match(WHILE);
    match(OPAREN);
    expr = expression();
    match(CPAREN);
    b = block();
    match(CBRACE);
    return cons(WHILELOOP, expr, b);
}

extern LEXEME *
forLoop() {
    match(FOR);
    match(OPAREN);
    LEXEME *vd = varDef();
    match(SEMI);
    LEXEME *fc = expression();
    match(SEMI);
    LEXEME *fo = expression();
    match(CPAREN);
    LEXEME *b = block();
    match(CBRACE);
    return cons(FORLOOP, cons(GLUE, vd, cons(GLUE, fc, fo)), b);
}

extern LEXEME *
funcDef() {
    LEXEME *name, *arg, *b, *r;
    match(METHOD);
    name = match(VARIABLE);
    match(OPAREN);
    // if (optArgListPending()) {
    if (check(VARIABLE)) {
        // arg = argList();
        arg = paramList();
    }
    else arg = NULL;
    match(CPAREN);
    // printf("gonna do the block in funcdef\n");
    b = block();
    if (returnPending()) {
        r = returnStatement();
    }
    else r = NULL;
    match(CBRACE);
    return cons(FUNCDEF, cons(GLUE, name, arg), cons(GLUE, b, r));
}

extern LEXEME *
funcCall(LEXEME *name) {
    // printf("in funcall\n");
    // LEXEME *name, *arg, *call;
    LEXEME *arg;
    // name = match(VARIABLE);
    // match(OPAREN);
    // printf("here\n");
    if (optArgListPending()) {
        arg = argList();
    }
    else arg = NULL;
    match(CPAREN);
    return cons(FUNCCALL, name, arg);

    // if (check(OPAREN)) {
    //     match(OPAREN);
    //     if (optArgListPending()) {
    //         arg = argList();
    //     }
    //     else arg = NULL;
    //     if (check(OPAREN)) {
    //         match(OPAREN);
    //         call = funcCall();
    //     }
    //     else call = NULL;
    //     match(CPAREN);
    // }
    // else {
    //     arg = NULL;
    //     call = NULL;
    // }
    // return cons(FUNCCALL, name, cons(GLUE, arg, call));
}

extern LEXEME *
returnStatement() {
    LEXEME *expr, *u;
    match(RETURN);
    if (expressionPending()) {
        expr = expression();
        u = NULL;
    }
    else if (unaryPending()) {
        u = unary();
        expr = NULL;
    }
    else {
        expr = NULL;
        u = NULL;
    }
    return cons(RETURNSTATEMENT, expr, u);
}

extern LEXEME *
forCheck() {
    LEXEME *f;
    if (check(LESSTHAN)) f = match(LESSTHAN);
    else if (check(GREATERTHAN)) f = match(GREATERTHAN);
    else if (check(LESSEQUALS)) f = match(LESSEQUALS);
    else f = match(GREATEREQUALS);
    return cons(FORCHECK, f, NULL);
}

extern LEXEME *
forOp() {
    LEXEME *op = NULL;
    LEXEME *u = NULL;
    LEXEME *e = NULL;
    if (check(PLUSPLUS)) op = match(PLUSPLUS);
    else if (check(MINUSMINUS)) op = match(MINUSMINUS);
    else if (check(ASSIGN)) {
        op = match(ASSIGN);
        if (unaryPending()) u = unary();
        else e = expression();
    }
    else if (check(PEQUALS)) {
        op = match(PEQUALS);
        if (unaryPending()) u = unary();
        else e = expression();
    }
    else if (check(MINUSEQUALS)) {
        op = match(MINUSEQUALS);
        if (unaryPending()) u = unary();
        else e = expression();
    }
    else if (check(TIMESEQUALS)) {
        op = match(MINUSEQUALS);
        if (unaryPending()) u = unary();
        else e = expression();
    }
    else {
        op = match(DIVIDEEQUALS);
        if (unaryPending()) u = unary();
        else e = expression();
    }

    if (u) return cons(FOROP, op, u);
    else if (e) return cons(FOROP, op, e);
    else return cons(FOROP, op, NULL);
}



/** PENDING FUNCTIONS **/
extern int
includesPending() {
    return check(POUND);
}

extern int
optArgListPending() {
    return unaryPending() || check(VARIABLE);
}

extern int
statementPending() {
    return expressionPending() || check(VAR) || check(IF) || check(WHILE) || check(FOR) || check(METHOD) || check(RETURN);
}

extern int
expressionPending() {
    return check(VARIABLE) || check(LAMBDA);
}

extern int
unaryPending() {
    return check(INTEGER) || check(STRING) || check(REAL) || check(VOID) || check(LAMBDA);
}

extern int
returnPending() {
    return check(RETURN);
}

extern int
operatorPending() {
    return check(PLUS) || check(MINUS) || check(TIMES) || check(DIVIDE) || check(ASSIGN) || check(GREATERTHAN) || check(LESSTHAN) || check(GREATEREQUALS) || check(LESSEQUALS) || check(DOT) || check(MOD) || check(NOT) || check(ANDAND) || check(OROR) || check(EQUALSEQUALS) || check(PLUSPLUS) || check(MINUSMINUS) || check(TIMESEQUALS) || check(DIVIDEEQUALS) || check(PEQUALS) || check(MINUSEQUALS);
}

extern int
functionCallPending() {
    return check(OPAREN);
}

extern int
arrayPending() {
    return check(OBRACKET);
}
