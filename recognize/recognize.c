/***
Ben Bailey
recognize.c
***/

/** INCLUDES **/
#include "recognize.h"
#include "lexing.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

LEXEME *currentLexeme;
FILE *fp;
int error = 0;

/** LEXICAL INTERFACE FUNCTIONS **/
extern int
check(char *type) {
    printf("Checking if CURRENT( %s ) equals PASSED( %s )\n", getType(currentLexeme), type);
    if (getType(currentLexeme) == type) {
        return 1;
    }
    return 0;
}

extern void
advance() {
    currentLexeme = lex(fp);
    printf("CURRENT LEXEME : %s\n", getType(currentLexeme));
}

extern void
match(char *type) {
    matchNoAdvance(type);
    advance();
}

extern void
matchNoAdvance(char *type) {
    printf("Trying to match CURRENT( %s ) and PASSED( %s )\n", getType(currentLexeme), type);
    if (check(type) == 0) {
        printf("!!!!!!!!!!!!------- FOUND A SYNTAX ERROR -------!!!!!!!!!!!!\n\n\n\n");
        error = 1;
    }
    else {
        printf("MATCHED %s\n", getType(currentLexeme));
    }
}

/** GRAMMAR RULES **/
extern int
program() {
    if (includesPending()) {
        includes();
        // program();
    }
    mainMethod();
    match(ENDOFINPUT);
    // printf("RETURNING FROM PROGRAAAAAAAAAMMMMMMMMMMMMMMMM\n\n\n");
    return error;
}

extern void
includes() {
    include();
    if (includesPending()) {
        includes();
    }
}

extern void
include() {
    match(POUND);
    match(INCLUDE);
    if (check(LESSTHAN)) {
        match(LESSTHAN);
        match(VARIABLE);
        match(DOT);
        match(VARIABLE);
        match(GREATERTHAN);
    }
    else if (check(STRING)) {
        match(STRING);
    }
}

extern void
mainMethod() {
    match(MAIN);
    match(OPAREN);
    if (optArgListPending()) {
        argList();
    }
    match(CPAREN);
    block();
    // if (returnPending()) {
    //     returnStatement();
    // }
    match(CBRACE);
}

extern void
argList() {
    // unary();
    expression();
    if (check(COMMA)) {
        match(COMMA);
        argList();
    }
}

extern void
block() {
    match(OBRACE);
    statements();
}

extern void
statements() {
    if (statementPending()) {
        statement();
        match(EXCL);
        statements();
    }
}

extern void
statement() {
    // if (functionCallPending()) {
    //     printf("going to function call!\n\n");
    //     funcCall();
    // }
    if (check(VAR)) {
        varDef();
    }
    else if (check(IF)) {
        ifStatement();
    }
    else if (check(WHILE)) {
        whileLoop();
    }
    else if (check(FOR)) {
        forLoop();
    }
    else if (check(METHOD)) {
        funcDef();
    }
    else if (returnPending()) {
        returnStatement();
    }
    else if (expressionPending()) {
        expression();
    }
}

extern void
expression() {
    if (unaryPending()) {
        unary();
        if (operatorPending()) {
            operator();
            expression();
        }
    }
    else {
        funcCall();
        if (operatorPending()) {
            operator();
            expression();
        }
    }
}

extern void
operator() {
    if (check(PLUS)) match(PLUS);
    else if (check(MINUS)) match(MINUS);
    else if (check(TIMES)) match(TIMES);
    else if (check(DIVIDE)) match(DIVIDE);
    else if (check(ASSIGN)) match(ASSIGN);
    else if (check(GREATERTHAN)) match(GREATERTHAN);
    else if (check(LESSTHAN)) match(LESSTHAN);
    else if (check(GREATEREQUALS)) match(GREATEREQUALS);
    else if (check(LESSEQUALS)) match(LESSEQUALS);
    else if (check(DOT)) match(DOT);
    else if (check(MOD)) match(MOD);
    else if (check(NOT)) match(NOT);
    else if (check(EQUALSEQUALS)) match(EQUALSEQUALS);
    else if (check(PLUSPLUS)) match(PLUSPLUS);
    else if (check(MINUSMINUS)) match(MINUSMINUS);
    else if (check(PEQUALS)) match(PEQUALS);
    else if (check(MINUESEQUALS)) match(MINUESEQUALS);
    else if (check(TIMESEQUALS)) match(TIMESEQUALS);
    else if (check(DIVIDEEQUALS)) match(DIVIDEEQUALS);
    else if (check(ANDAND)) match(ANDAND);
    else if (check(OROR)) match(OROR);
}

extern void
unary() {
    if (check(INTEGER)) match(INTEGER);
    else if (check(STRING)) match(STRING);
    else if (check(REAL)) match(REAL);
    else if (check(VOID)) match(VOID);
}

extern void
varDef() {
    match(VAR);
    match(VARIABLE);
    if (arrayPending()) {
        match(OBRACKET);
        if (optArgListPending()) {
            argList();
        }
        match(CBRACKET);
    }
    else if (check(ASSIGN)) {
        match(ASSIGN);
        expression();
    }
    else {
        printf("---- looks like variable definition. can't understand ----\n");
        error = 1;
    }
}

extern void
ifStatement() {
    match(IF);
    match(OPAREN);
    expression();
    match(CPAREN);
    block();
    match(CBRACE);
    if (check(ELSE)) {
        optElse();
    }
}

extern void
optElse() {
    match(ELSE);
    if (check(IF)) {
        ifStatement();
    }
    else {
        block();
        match(CBRACE);
    }
}

extern void
whileLoop() {
    match(WHILE);
    match(OPAREN);
    expression();
    match(CPAREN);
    block();
    match(CBRACE);
}

extern void
forLoop() {
    match(FOR);
    match(OPAREN);
    unary();
    match(ASSIGN);
    match(INTEGER);
    match(SEMI);
    unary();
    forCheck();
    match(INTEGER);
    match(SEMI);
    unary();
    forOp();
    match(CPAREN);
    block();
    match(CBRACE);
}

extern void
funcDef() {
    match(METHOD);
    match(VARIABLE);
    match(OPAREN);
    if (optArgListPending()) {
        argList();
    }
    match(CPAREN);
    block();
    if (returnPending()) {
        returnStatement();
    }
    match(CBRACE);
}

extern void
funcCall() {
    match(VARIABLE);
    if (check(OPAREN)) {
        match(OPAREN);
        if (optArgListPending()) {
            argList();
        }
        if (check(OPAREN)) {
            match(OPAREN);
            funcCall();
        }
        match(CPAREN);
    }
    // unary();
    // if (check(OPAREN)) {
    //     match(OPAREN);
    //     if (optArgListPending()) {
    //         argList();
    //     }
    //     if (check(OPAREN)) {
    //         match(OPAREN);
    //         funcCall();
    //     }
    //     match(CPAREN);
    // }
    // else if (operatorPending()){
    //     operator();
    //     funcCall();
    // }
    // else {
    //     match(CPAREN);
    // }
}

extern void
returnStatement() {
    match(RETURN);
    if (expressionPending()) {
        expression();
    }
    else if (unaryPending()) {
        unary();
    }
    // match(EXCL);
}

extern void
forCheck() {
    if (check(LESSTHAN)) match(LESSTHAN);
    else if (check(GREATERTHAN)) match(GREATERTHAN);
    else if (check(LESSEQUALS)) match(LESSEQUALS);
    else match(GREATEREQUALS);
}

extern void
forOp() {
    if (check(PLUSPLUS)) match(PLUSPLUS);
    else if (check(MINUSMINUS)) match(MINUSMINUS);
    else if (check(PEQUALS)) {
        match(PEQUALS);
        unary();
    }
    else if (check(MINUESEQUALS)) {
        match(MINUESEQUALS);
        unary();
    }
    else if (check(TIMESEQUALS)) {
        match(MINUESEQUALS);
        unary();
    }
    else {
        match(DIVIDEEQUALS);
        unary();
    }
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
    return check(VARIABLE);
}

extern int
unaryPending() {
    return check(INTEGER) || check(STRING) || check(REAL) || check(VOID);
}

extern int
returnPending() {
    return check(RETURN);
}

extern int
operatorPending() {
    return check(PLUS) || check(MINUS) || check(TIMES) || check(DIVIDE) || check(ASSIGN) || check(GREATERTHAN) || check(LESSTHAN) || check(GREATEREQUALS) || check(LESSEQUALS) || check(DOT) || check(MOD) || check(NOT) || check(ANDAND) || check(OROR) || check(EQUALSEQUALS) || check(PLUSPLUS) || check(MINUSMINUS) || check(TIMESEQUALS) || check(DIVIDEEQUALS);
}

extern int
functionCallPending() {
    return check(OPAREN);
}

extern int
arrayPending() {
    return check(OBRACKET);
}

/** THE PARSING FUNCTION **/
extern int
parse(FILE *file) {
    fp = file;
    advance();
    int p =  program();
    printf("RETURNING FROM PARSE\n\n\n");
    return p;
}
