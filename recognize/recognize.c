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

/** LEXICAL INTERFACE FUNCTIONS **/
extern int
check(char *type) {
    if (getType(currentLexeme) == type) {
        return 1;
    }
    return 0;
}

extern void
advance() {
    currentLexeme = lex(fp);
}

extern void
match(char *type) {
    matchNoAdvance(type);
    advance();
}

extern void
matchNoAdvance(char *type) {
    if (check(type) == 0) {
        printf("FOUND A SYNTAX ERROR\n");
    }
}

/** GRAMMAR RULES **/
extern void
program() {
    if (includesPending()) {
        include();
        program();
    }
    main();
}

extern void
include() {
    match(POUND);
    match(INCLUDE);
    if (check(LESSTHAN)) {
        match(LESSTHAN);
        match(IDENTIFIER);
        match(DOT);
        match(GREATERTHAN);
    }
    else if (check(STRING)) {
        match(STRING);
    }
}

extern void
main() {
    match(MAIN);
    match(OPAREN);
    if (optArgListPending()) {
        argList();
    }
    match(CPAREN);
    block();
}

extern void
argList() {
    // match(IDENTIFIER);
    unary();
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
    if (expressionPending()) {
        expression();
    }
    else if (check(VAR)) {
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
    else if (functionCallPending()) {
        funcCall();
    }
    else {
        printf("---- unknown expression ----\n");
    }
}

extern void
expression() {
    unary();
    if (operatorPending()) {
        operator();
        expression();
    }
}

extern void
operator() {
    if (check(PLUS)) match(PLUS);
    else if (check(MINUS)) match(MINUS);
    else if (check(TIMES)) match(TIMES);
    else if (check(DIVIDE)) match(DIVIDE);
    else if (check(EQUALS)) match(EQUALS);
    else if (check(GREATERTHAN)) match(GREATERTHAN);
    else if (check(LESSTHAN)) match(LESSTHAN);
    else if (check(GREATEREQUALS)) match(GREATEREQUALS);
    else if (check(LESSEQUALS)) match(LESSEQUALS);
    else if (check(DOT)) match(DOT);
    else if (check(MOD)) match(MOD);
    else match(NOT);

}

extern void
unary() {
    if (check(IDENTIFIER)) match(IDENTIFIER);
    else if (check(INTEGER)) match(INTEGER);
    else if (check(STRING)) match(STRING);
    else match(REAL);
}

extern void
varDef() {
    match(VAR);
    match(IDENTIFIER);
    if (arrayPending()) {
        match(OBRACKET);
        if (optArgListPending()) {
            argList();
        }
    }
    else if (check(EQUALS)) {
        match(EQUALS);
        expression();
    }
    else {
        printf("---- looks like variable definition. can't understand ----\n");
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
    match(EQUALS);
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
    match(IDENTIFIER);
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
    unary();
    if (check(OPAREN)) {
        match(OPAREN);
        if (optArgListPending()) {
            argList();
        }
        match(CPAREN);
    }
    else {
        operator();
        funcCall();
    }
}

extern void
returnStatement() {
    match(RETURN);
    if (expressionPending()) {
        expression();
    }
    match(EXCL);
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
    return unaryPending();
}

extern int
statementPending() {
    return expressionPending() || check(VAR) || check(IF) || check(WHILE) || check(FOR) || check(METHOD) || returnPending();
}

extern int
expressionPending() {
    return unaryPending();
}

extern int
unaryPending() {
    return check(IDENTIFIER) || check(INTEGER) || check(STRING) || check(REAL);
}

extern int
returnPending() {
    return check(RETURN);
}

extern int
operatorPending() {
    return check(PLUS) || check(MINUS) || check(TIMES) || check(DIVIDE) || check(EQUALS) || check(GREATERTHAN) || check(LESSTHAN) || check(GREATEREQUALS) || check(LESSEQUALS) || check(DOT) || check(MOD) || check(NOT);
}

extern int
functionCallPending() {
    return unaryPending();
}

/** THE PARSING FUNCTION **/
extern void
parse(FILE *file) {
    fp = file;
    advance();
    program();
}
