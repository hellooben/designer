/***
Ben Bailey
environment.c
***/

#include "environment.h"
#include <stdio.h>
#include <string.h>
#include "lexing.h"
#include "types.h"

extern int sameVariable(LEXEME *l1, LEXEME *l2) {
    // printf("IN sameVariable\nl1: %s || l2: %s\n", getType(l1), getType(l2));
    if (strcmp(getType(l1), getType(l2)) == 0) {
        // printf("SAME TYPES\nl1: %s || l2: %s\n", getLEXEMEString(l1), getLEXEMEString(l2));
        if (strcmp(getLEXEMEString(l1), getLEXEMEString(l2)) == 0) {
            return 1;
        }
    }
    return 0;
}


extern LEXEME *
cons(char *type, LEXEME *left, LEXEME *right) {
    LEXEME *p = newLEXEME(type);
    setLEXEMEleft(p, left);
    setLEXEMEright(p, right);
    return p;
}

extern LEXEME *
car(LEXEME *p) {
    return getLEXEMEleft(p);
}

extern LEXEME *
cdr(LEXEME *p) {
    return getLEXEMEright(p);
}

extern LEXEME *
setCar(LEXEME *l, LEXEME *new) {
    setLEXEMEleft(l, new);
    return getLEXEMEleft(l);
}

extern LEXEME *
setCdr(LEXEME *l, LEXEME *new) {
    setLEXEMEright(l, new);
    return getLEXEMEright(l);
}





extern LEXEME *
create() {
    return cons(ENV, cons(TABLE, NULL, NULL), NULL);
}

extern LEXEME *
lookup(LEXEME *variable, LEXEME *env) {
    // printf("INLOOKUP\nVARIABLE TYPE: %s\n", getType(variable));
    while (env != NULL) {
        LEXEME *table = car(env);
        LEXEME *vars = car(table);
        LEXEME *vals = cdr(table);
        while (vars != NULL) {
            if (sameVariable(variable, car(vars))) {
                // printf("Gonna return from lookup\n");
                return car(vals);
            }
            vars = cdr(vars);
            vals = cdr(vals);
        }
        env = cdr(env);
    }
    printf("Variable reference from line %d is undefined! Cannot access.\n", getLEXEMEline(variable));
    return NULL;
}

extern LEXEME *
update(LEXEME *variable, LEXEME *env, LEXEME *new) {
    while (env != NULL) {
        LEXEME *table = car(env);
        LEXEME *vars = car(table);
        LEXEME *vals = cdr(table);
        while (vars != NULL) {
            if (sameVariable(variable, car(vars))) {
                return setCar(vals, new);
            }
            vars = cdr(vars);
            vals = cdr(vals);
        }
        env = cdr(env);
    }
    printf("Variable reference from line %d is undefined! Cannot update.\n", getLEXEMEline(variable));
    return NULL;
}

extern LEXEME *
insert(LEXEME *variable, LEXEME *env, LEXEME *value) {
    LEXEME *table = car(env);
    setCar(table, cons(JOIN, variable, car(table)));
    setCdr(table, cons(JOIN, value, cdr(table)));
    return value;
}

extern LEXEME *
extend(LEXEME *variables, LEXEME *values, LEXEME *env) {
    return cons(ENV, cons(TABLE, variables, values), env);
}

extern void
display(LEXEME *env) {
    int tables = 0;
    while (env != NULL) {
        // printf("env is not null\n");
        if (tables == 0) printf("Table %d (local):\n", tables);
        else printf("Table %d:\n", tables);
        // displayLEXEME(env);
        LEXEME *table = car(env);
        // printf("got table: %s\n", getType(table));
        LEXEME *vars = car(table);
        // printf("got vars: %s\n", getType(car(vars)));
        LEXEME *vals = cdr(table);
        // printf("got vals: %s\n", getType(car(vals)));
        while (vars != NULL) {
            printf("    ");
            displayLEXEME(car(vars));
            printf(" = ");
            displayLEXEME(car(vals));
            printf("\n");
            vars = cdr(vars);
            vals = cdr(vals);
        }
        env = cdr(env);
        tables ++;
    }
    printf("\n\n");
}

extern void
displayLocal(LEXEME *env) {
    // printf("Table %d:\n", tables);
    // displayLEXEME(env);
    LEXEME *table = car(env);
    LEXEME *vars = car(table);
    LEXEME *vals = cdr(table);
    while (vars != NULL) {
        printf("    ");
        displayLEXEME(car(vars));
        printf(" = ");
        displayLEXEME(car(vals));
        printf("\n");
        vars = cdr(vars);
        vals = cdr(vals);
    }
    printf("\n\n");
}
