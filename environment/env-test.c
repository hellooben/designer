/***
Ben Bailey
env-test.c
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexing.h"
#include "types.h"
#include "environment.h"

int main() {
    printf("Creating a new environment\n");
    LEXEME *env = create();

    printf("Adding variable x with value 3.\n");
    LEXEME *x = newLEXEMEString(VARIABLE, "x");
    LEXEME *x3 = newLEXEMEInt(INTEGER, 3);
    LEXEME *inserted = insert(x, env, x3);
    printf("Adding variable y with value 69.\n");
    LEXEME *y = newLEXEMEString(VARIABLE, "y");
    LEXEME *y69 = newLEXEMEInt(INTEGER, 69);
    inserted = insert(y, env, y69);

    printf("The environment ENV1:\n");
    display(env);

    printf("Looking up x\n");
    LEXEME *find = lookup(x, env);
    if (find) {
        printf("Found ");
        displayLEXEME(find);
        printf("\n");
    }

    printf("Adding variable str with value \"string boy\"\n");
    LEXEME *str = newLEXEMEString(VARIABLE, "str");
    LEXEME *stringboy = newLEXEMEString(STRING, "string boy");
    inserted = insert(str, env, stringboy);

    printf("The environment ENV1:\n");
    display(env);

    printf("Updating the variable x to 0\n");
    LEXEME *x0 = newLEXEMEInt(INTEGER, 0);
    LEXEME *updated = update(x, env, x0);
    if (updated) printf("Updated!\n");

    printf("The environment ENV1:\n");
    display(env);

    printf("Extending the environment ENV1 with ENV2\n");
    LEXEME *env2 = extend(car(car(env)), cdr(car(env)), env);
    if (env2) printf("Extended\n");

    printf("The environment ENV2:\n");
    display(env2);

    printf("Adding variable z with value 3.3.\n");
    LEXEME *z = newLEXEMEString(VARIABLE, "z");
    LEXEME *zNum = newLEXEMEReal(REAL, 3.3);
    inserted = insert(z, env2, zNum);

    printf("The environment ENV2:\n");
    display(env2);

    // printf("The local environment for env:\n");
    // displayLocal(env);


    printf("Extending the environment ENV2 with ENV3\n");
    LEXEME *env3 = extend(car(car(env2)), cdr(car(env2)), env2);
    if (env3) printf("Extended\n");

    printf("Adding variable new with value 420.\n");
    LEXEME *new = newLEXEMEString(VARIABLE, "new");
    LEXEME *new420 = newLEXEMEInt(INTEGER, 420);
    inserted = insert(new, env3, new420);

    printf("The environment:\n");
    display(env3);
    printf("The local environment ENV3:\n");
    displayLocal(env3);
}
