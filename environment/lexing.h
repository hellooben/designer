/***
Ben Bailey
lexing.h
***/

#ifndef __LEXING_INCLUDED__
#define __LEXING_INCLUDED__

#include <stdio.h>

typedef struct lexeme LEXEME;

extern LEXEME *newLEXEME(char *);
extern LEXEME *newLEXEMEInt(char *, int);
extern LEXEME *newLEXEMEReal(char *, double);
extern LEXEME *newLEXEMEString(char *, char *);
extern LEXEME *lexNumber(FILE *);
extern LEXEME *lexVariableorKeyword(FILE *);
extern LEXEME *lexString(FILE *);
extern void skipWhiteSpace(FILE *);
extern LEXEME *lex(FILE *);
extern char *getType(LEXEME *);
extern int getLEXEMEInt(LEXEME *);
extern char *getLEXEMEString(LEXEME *);
extern int getLEXEMEline(LEXEME *);
extern void displayLEXEME(LEXEME *);

// New functions for environment
extern void setLEXEMEright(LEXEME *, LEXEME *);
extern void setLEXEMEleft(LEXEME *, LEXEME *);
extern LEXEME *getLEXEMEleft(LEXEME *);
extern LEXEME *getLEXEMEright(LEXEME *);
#endif
