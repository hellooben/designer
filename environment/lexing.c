/***
Ben Bailey
lexing.c
***/

#include "lexing.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

int isWhiteSpace(char, FILE *);
void skipComment(FILE *);
int checkDoubleOperator(int, FILE *);

int LINECOUNT = 1;

struct lexeme {
    char *type;
    int intVal;
    double realVal;
    char *stringVal;
    int lineNum;
    // char *name;

    LEXEME *left;
    LEXEME *right;
};

extern LEXEME *
newLEXEME(char *type) {
    LEXEME *l = malloc(sizeof(LEXEME));
    assert(l != 0);
    l->type = type;
    l->intVal = 0;
    l->realVal = 0.0;
    l->stringVal = "";
    l->lineNum = LINECOUNT;
    // l->name = "";
    l->left = l;
    l->right = l;
    return l;
}

// extern LEXEME *
// newLEXEMEvar(char *type, char *name) {
//     LEXEME *l = malloc(sizeof(LEXEME));
//     assert(l != 0);
//     l->type = type;
//     l->intVal = 0;
//     l->realVal = 0.0;
//     l->stringVal = "";
//     l->lineNum = LINECOUNT;
//     l->name = name;
//     l->left = l;
//     l->right = l;
//     return l;
// }

extern LEXEME *
newLEXEMEInt(char *type, int intVal) {
    LEXEME *l = malloc(sizeof(LEXEME));
    assert(l != 0);
    l->type = type;
    l->intVal = intVal;
    l->realVal = 0.0;
    l->stringVal = "";
    l->lineNum = LINECOUNT;
    // l->name = "";
    l->left = l;
    l->right = l;
    return l;
}

extern LEXEME *
newLEXEMEReal(char *type, double realVal) {
    LEXEME *l = malloc(sizeof(LEXEME));
    assert(l != 0);
    l->type = type;
    l->intVal = 0;
    l->realVal = realVal;
    l->stringVal = "";
    l->lineNum = LINECOUNT;
    // l->name = "";
    l->left = l;
    l->right = l;
    return l;
}

extern LEXEME *
newLEXEMEString(char *type, char *stringVal) {
    LEXEME *l = malloc(sizeof(LEXEME));
    assert(l != 0);
    l->type = type;
    l->intVal = 0;
    l->realVal = 0.0;
    l->stringVal = stringVal;
    l->lineNum = LINECOUNT;
    // l->name = "";
    l->left = l;
    l->right = l;
    return l;
}

extern void
setLEXEMEleft(LEXEME *l, LEXEME *set) {
    l->left = set;
}

extern void
setLEXEMEright(LEXEME *l, LEXEME *set) {
    l->right = set;
}

extern LEXEME *
getLEXEMEleft(LEXEME *l) {
    return l->left;
}

extern LEXEME *
getLEXEMEright(LEXEME *l) {
    return l->right;
}

extern LEXEME *
lexNumber(FILE *fp) {
    int real = 0;
    int length = 32;
    int index = 0;
    char *buffer = malloc(sizeof(char) * length + 1);
    int ch = fgetc(fp);
    while (!feof(fp) && (isdigit(ch) || ch == '.')) {
        if (index == length) {
            buffer = realloc(buffer, sizeof(char) * length * 2 + 1);
            length *= 2;
        }
        buffer[index++] = ch;
        buffer[index] = '\0';
        if (ch == '.' && real) {
            return newLEXEMEInt(BADNUMBER, LINECOUNT);
        }
        if (ch == '.') {
            real = 1;
        }
        ch = fgetc(fp);
    }
    ungetc(ch, fp);
    if (real) {
        return newLEXEMEReal(REAL, atof(buffer));
    }
    else {
        return newLEXEMEInt(INTEGER, atoi(buffer));
    }
}

extern LEXEME *
lexVariableorKeyword(FILE *fp) {
    int length = 32;
    int index = 0;
    char *buffer = malloc(sizeof(char) * length + 1);
    int ch = fgetc(fp);

    while (isdigit(ch) || isalpha(ch)) {
        if (index == length) {
            buffer = realloc(buffer, sizeof(char) * length * 2 + 1);
            length *= 2;
        }
        buffer[index++] = ch;
        buffer[index] = '\0';
        ch = fgetc(fp);
    }
    ungetc(ch, fp);

    if (strcmp(buffer, "if") == 0) return newLEXEME(IF);
    else if (strcmp(buffer, "else") == 0) return newLEXEME(ELSE);
    else if (strcmp(buffer, "for") == 0) return newLEXEME(FOR);
    else if (strcmp(buffer, "while") == 0) return newLEXEME(WHILE);
    else if (strcmp(buffer, "NOT") == 0) return newLEXEME(NOT);
    else if (strcmp(buffer, "include") == 0) return newLEXEME(INCLUDE);
    else if (strcmp(buffer, "main") == 0) return newLEXEME(MAIN);
    else if (strcmp(buffer, "return") == 0) return newLEXEME(RETURN);
    else if (strcmp(buffer, "method") == 0) return newLEXEME(METHOD);
    else if (strcmp(buffer, "var") == 0) return newLEXEME(VAR);
    else if (strcmp(buffer, "struct") == 0) return newLEXEME(STRUCT);
    else if (strcmp(buffer, "VOID") == 0 || strcmp(buffer, "void") == 0) return newLEXEME(VOID);
    else {
        return newLEXEMEString(VARIABLE, buffer);
    }
}

extern LEXEME *
lexString(FILE *fp) {
    int length = 32;
    int index = 0;
    char *buffer = malloc(sizeof(char) * length + 1);
    int ch = fgetc(fp);

    while (ch != '\"') {
        if (index == length) {
            buffer = realloc(buffer, sizeof(char) * length * 2 + 1);
            length *= 2;
        }
        buffer[index++] = ch;
        buffer[index] = '\0';
        ch = fgetc(fp);
    }

    return newLEXEMEString(STRING, buffer);
}

int
isWhiteSpace(char ch, FILE *fp) {
    if (ch == 10) {
        LINECOUNT ++;
        return 1;
    }
    else if (ch >= 64) return 0;
    else if (ch == 0) return 0;
    else if (ch >=33 && ch <= 62) return 0;
    else if (ch == '?') {
        skipComment(fp);
        return 1;
    }
    else {
        return 1;
    }
}

void
skipComment(FILE *fp) {
    int ch = fgetc(fp);

    while (ch != '?') {
        if (ch == 10) {
            LINECOUNT ++;
        }
        ch = fgetc(fp);
    }
}

extern void
skipWhiteSpace(FILE *fp) {
    int ch;

    while ((ch = fgetc(fp)) != EOF && isWhiteSpace(ch, fp))
        continue;

    if (ch != EOF) ungetc(ch, fp);
}

int
checkDoubleOperator(int cNum, FILE *fp) {
    int ch = fgetc(fp);
    if (cNum == '=' && ch == '=') {
        return 1;
    }
    else if (cNum == '<' && ch == '=') {
        return 1;
    }
    else if (cNum == '>' && ch == '=') {
        return 1;
    }
    else if (cNum == '+' && ch == '+') {
        return 1;
    }
    else if (cNum == '-' && ch == '-') {
        return 1;
    }
    else if (cNum == '+' && ch == '=') {
        // printf("helloooooooooo\n");
        return 2;
    }
    else if (cNum == '-' && ch == '=') {
        return 2;
    }
    else if (cNum == '&' && ch == '&') {
        return 1;
    }
    else if (cNum == '|' && ch == '|') {
        return 1;
    }
    else if (cNum == '*' && ch == '=') {
        return 1;
    }
    else if (cNum == '/' && ch == '=') {
        return 1;
    }
    else {
        // printf("gotta unget\n");
        ungetc(ch, fp);
        return 0;
    }
}

extern LEXEME *
lex(FILE *fp) {
    skipWhiteSpace(fp);
    int ch = fgetc(fp);
    int dub;

    if (feof(fp)) {
        return newLEXEME(ENDOFINPUT);
    }

    switch(ch) {
        case '#' : return newLEXEME(POUND);
        case '<' :
            if (checkDoubleOperator(ch, fp)) {
                return newLEXEME(LESSEQUALS);
            }
            else return newLEXEME(LESSTHAN);
        case '>' :
            if (checkDoubleOperator(ch, fp)) {
                return newLEXEME(GREATEREQUALS);
            }
            else return newLEXEME(GREATERTHAN);
        case '(' : return newLEXEME(OPAREN);
        case ')' : return newLEXEME(CPAREN);
        case '{' : return newLEXEME(OBRACE);
        case '}' : return newLEXEME(CBRACE);
        case '[' : return newLEXEME(OBRACKET);
        case ']' : return newLEXEME(CBRACKET);
        case '!' : return newLEXEME(EXCL);
        case ';' : return newLEXEME(SEMI);
        case ':' : return newLEXEME(COLON);
        case '=' :
            if (checkDoubleOperator(ch, fp)) {
                return newLEXEME(EQUALSEQUALS);
            }
            else return newLEXEME(ASSIGN);
        case '+' :
            dub = checkDoubleOperator(ch, fp);
            if (dub == 0) return newLEXEME(PLUS);
            else if (dub == 1) return newLEXEME(PLUSPLUS);
            else return newLEXEME(PEQUALS);
        case '-' :
            dub = checkDoubleOperator(ch, fp);
            if (dub == 0) return newLEXEME(MINUS);
            else if (dub == 1) return newLEXEME(MINUSMINUS);
            else return newLEXEME(MINUESEQUALS);
        case '/' :
            if (checkDoubleOperator(ch, fp)) {
                return newLEXEME(DIVIDEEQUALS);
            }
            else return newLEXEME(DIVIDE);
        case '*' :
            if (checkDoubleOperator(ch, fp)) {
                return newLEXEME(TIMESEQUALS);
            }
            else return newLEXEME(TIMES);
        case '.' : return newLEXEME(DOT);
        case ',' : return newLEXEME(COMMA);
        case '&' :
            if (checkDoubleOperator(ch, fp)) {
                return newLEXEME(ANDAND);
            }
            else return newLEXEME(MOD);
        case '|':
            if (checkDoubleOperator(ch, fp)) {
                return newLEXEME(OROR);
            }
            else return newLEXEME(DIVIDE);
        case '?' : return newLEXEME(QUESTION);

        default :
            if (isdigit(ch)) {
                ungetc(ch, fp);
                return lexNumber(fp);
            }
            else if (isalpha(ch)) {
                ungetc(ch, fp);
                return lexVariableorKeyword(fp);
            }
            else if (ch == '\"') {
                return lexString(fp);
            }
            else {
                return newLEXEMEInt(UNKNOWN, LINECOUNT);
            }
    }
}

extern char *
getType(LEXEME *l) {
    return l->type;
}

extern int
getLEXEMEInt(LEXEME *l) {
    return l->intVal;
}

extern char *
getLEXEMEString(LEXEME *l) {
    return l->stringVal;
}

extern int
getLEXEMEline(LEXEME *l) {
    return l->lineNum;
}

extern void
displayLEXEME(LEXEME *l) {
    if (strcmp(getType(l), VARIABLE) == 0) {
        printf("IDENTIFIER %s\n", l->stringVal);
    }
    else if (strcmp(getType(l), STRING) == 0) {
        printf("STRING \"%s\"\n", l->stringVal);
    }
    else if (strcmp(getType(l), INTEGER) == 0) {
        printf("INT %d\n", l->intVal);
    }
    else if (strcmp(getType(l), REAL) == 0) {
        printf("DOUBLE %lf\n", l->realVal);
    }
    else {
        printf("%s\n", getType(l));
    }
}
