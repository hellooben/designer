/***
Ben Bailey
eval.c
***/

#include "eval.h"
#include "lexing.h"
#include "types.h"
#include "recognize.h"
#include "environment.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



extern LEXEME *
eval(LEXEME *tree, LEXEME *env) {
    // switch(getType(tree)) {
    if (getType(tree) == INTEGER) return tree;
    else if (getType(tree) == STRING) return tree;
    else if (getType(tree) == VARIABLE) {
        // printf("EVAL-ing A VARIABLE\n");
        return lookup(tree, env);
    }
    else if (getType(tree) == VOID) return tree;
    else if (getType(tree) == UNARY) return evalUnary(tree, env);
    //parenthesized expression
    // else if (getType(tree) == OPAREN) return eval(cdr(tree), env);
    //operatros: evaluate both sides
    else if (getType(tree) == OPERATOR) return evalOp(tree, env);
    else if (getType(tree) == PLUS) return evalOp(tree, env); //done
    else if (getType(tree) == MINUS) return evalOp(tree, env);
    else if (getType(tree) == TIMES) return evalOp(tree, env);
    else if (getType(tree) == DIVIDE) return evalOp(tree, env);
    else if (getType(tree) == PLUSPLUS) return evalOp(tree, env);
    else if (getType(tree) == MINUSMINUS) return evalOp(tree, env);
    else if (getType(tree) == PEQUALS) return evalOp(tree, env);
    else if (getType(tree) == MINUSEQUALS) return evalOp(tree, env);
    else if (getType(tree) == TIMESEQUALS) return evalOp(tree, env);
    else if (getType(tree) == DIVIDEEQUALS) return evalOp(tree, env);
    else if (getType(tree) == GREATERTHAN) return evalOp(tree, env);
    else if (getType(tree) == LESSTHAN) return evalOp(tree, env);
    else if (getType(tree) == GREATEREQUALS) return evalOp(tree, env);
    else if (getType(tree) == LESSEQUALS) return evalOp(tree, env);
    //AND and OR short-circuit
    // else if (getType(tree) == AND) return evalShortCircuitOp(tree, env);
    // else if (getType(tree) == OR) return evalShortCircuitOp(tree, env);
    //dor operator evals lhs, rhs as a variable
    // else if (getType(tree) == DOT) return evalDot(tree, env);
    //assign operator evals rhs for sure;
    //lhs is a variable or a dot operation
    else if (getType(tree) == ASSIGN) return evalAssign(tree, env); //done
    //variable and function definitions
    else if (getType(tree) == VARDEF) return evalVarDef(tree, env); //done
    else if (getType(tree) == FUNCDEF) return evalFuncDef(tree, env); //done
    else if (getType(tree) == LAMBDA) return evalLambda(tree, env); //done
    //imperative constructs
    else if (getType(tree) == PROGRAM) return evalProgram(tree, env); //done
    // else if (getType(tree) == INCLUDES) return evalIncludes(tree, env);
    // else if (getType(tree) == INCLUDE) return evalInclude(tree, env);
    else if (getType(tree) == MAINMETHOD) return evalMain(tree, env); //done
    else if (getType(tree) == ARGLIST) return evalArgList(tree, env); //done
    else if (getType(tree) == BLOCK) return evalBlock(tree, env); //done
    else if (getType(tree) == STATEMENTS) return evalStatements(tree, env); //done
    else if (getType(tree) == STATEMENT) return evalStatement(tree, env); //done
    else if (getType(tree) == EXPRESSION) return evalExpression(tree, env); //done
    // else if (getType(tree) == OPERATOR) return evalOperator(tree, env);
    // else if (getType(tree) == UNARY) return evalUnary(tree, env);
    else if (getType(tree) == IFSTATEMENT) return evalIf(tree, env); //done
    else if (getType(tree) == OPTELSE) return evalOptElse(tree, env); //done
    else if (getType(tree) == WHILELOOP) return evalWhileLoop(tree, env); //done
    else if (getType(tree) == FORLOOP) return evalForLoop(tree, env); //done
    // else if (getType(tree) == FORCHECK) return evalForCheck(tree, env);
    // else if (getType(tree) == FOROP) return evalForOp(tree, env);
    else if (getType(tree) == FUNCCALL) return evalFuncCall(tree, env); //done
    else if (getType(tree) == RETURNSTATEMENT) return evalReturn(tree, env); //done

    else {
        printf("bad expression\n");
        return NULL;
    }
}

extern LEXEME *
evalProgram(LEXEME *tree, LEXEME *env) {
    // printf("In EVALPROGRAM\n");
    // eval(car(tree), env);
    eval(cdr(tree), env);
    return NULL;
}
//
// extern void
// evalIncludes(LEXEME *tree, LEXEME *env) {
//     eval(car(tree));
//     if (cdr(tree)) eval(cdr(tree));
//     return NULL;
// }
//
// extern void
// evalInclude(LEXEME *tree, LEXEME *env) {
//     if (car(tree)) {
//         LEXEME *closure = cons(CLOSURE, )
//     }
// }

extern LEXEME *
evalUnary(LEXEME *tree, LEXEME *env) {
    // printf("in EVALUNARY\nleft type is %s\n", getType(car(tree)));
    return eval(car(tree), env);
}

extern LEXEME *
evalMain(LEXEME *tree, LEXEME *env) {
    // printf("In EVALMAIN\n");
    // LEXEME *arg;
    // if (car(tree)) arg = eval(car(tree)); //argList
    // LEXEME *mainEnv = extend(NULL, NULL, env); //variables, values, env

    LEXEME *main = eval(cdr(tree), env); //block
    // eval(cdr(tree)); //block
    return main;
}

extern LEXEME *
evalArgList(LEXEME *tree, LEXEME *env) {
    // printf("In EVALARGLIST\n");
    if (cdr(tree)) {
        // printf("right is there\n");
        return cons(GLUE, eval(car(tree), env), eval(cdr(tree), env));
    }
    else {
        return cons(GLUE, eval(car(tree), env), NULL);
    }
}

extern LEXEME *
evalBlock(LEXEME *tree, LEXEME *env) {
    // printf("In EVALBLOCK\n");
    return eval(car(tree), env); //statements
}

extern LEXEME *
evalStatements(LEXEME *tree, LEXEME *env) {
    // printf("In EVALSTATEMENTS\n");
    LEXEME *result = eval(car(tree), env); //statement
    if (cdr(tree)) eval(cdr(tree), env); //statements
    return result; //this might cause things to work in reverse
}

extern LEXEME *
evalStatement(LEXEME *tree, LEXEME *env) {
    // printf("In EVALSTATEMENT\n");
    return eval(car(tree), env); //varDef, ifStatement, whileLoop, forLoop, funcDef, returnStatement, expression
}

extern LEXEME *
evalExpression(LEXEME *tree, LEXEME *env) {
    // printf("In EVALEXPRESSION, left type is %s\n", getType(car(tree)));
    if (car(cdr(tree)) == NULL) { //if no operator
        // printf("NO OPERATOR\n");
        if (getType(car(tree)) == GLUE) { //it has a size: array
            // printf("IT IS AN ARRAY\n");
            if (cdr(car(tree)) != NULL) { //if size isn't null
                int index;
                if (getType(cdr(car(tree))) == VARIABLE) {
                    LEXEME *find = eval(cdr(car(tree)), env);
                    index = getLEXEMEInt(find);
                }
                else if (getType(cdr(car(tree))) == INTEGER) {
                    index = getLEXEMEInt(cdr(car(tree))); //get the index
                }
                else {
                    printf("INVALIED ARRAY INDEX\nFatal on line %d\n", getLEXEMEline(tree));
                    exit(1);
                }
                return evalGetArray(car(car(tree)), index, env); //evaluate with variable and index
            }
            else {
                printf("INVALIED ARRAY INDEX\nFatal on line %d\n", getLEXEMEline(tree));
                exit(1);
            }
        }
        else {
            // printf("gonna return here\nTYPE HERE IS: %s\n", getType(car(tree)));
            return eval(car(tree), env); //unary, variable, funcCall
        }
    }
    else { //if operator
        // printf("FOUND OPERATOR IN EXPRESSION\n");
        if (cdr(cdr(tree)) == NULL) { //if no expression after operator
            if (getType(car(tree)) == GLUE) { //it has a size: array
                int index = getLEXEMEInt(cdr(car(tree))); //get the index
                LEXEME *set = evalGetArray(car(car(tree)), index, env);
                // setCar(car(car(cdr(tree))), car(car(car(tree))));
                setCar(car(car(cdr(tree))), set);
            }
            else setCar(car(car(cdr(tree))), car(car(tree))); //set operator->left = variable
            // setCar(car(cdr(tree)), car(tree)); //set operator->left = variable
            return evalSelfOp(car(car(cdr(tree))), env); //eval operator
        }
        else {
            // printf("FOUND EXPRESSION AFTER OPERATOR\n");
            if (getType(car(tree)) == GLUE) { //it has a size: array
                int index = getLEXEMEInt(cdr(car(tree))); //get the index
                LEXEME *set = evalGetArray(car(car(tree)), index, env);
                // setCar(car(car(cdr(tree))), car(car(car(tree))));
                setCar(car(car(cdr(tree))), set);
            }
            else setCar(car(car(cdr(tree))), car(car(tree))); //operator->left = variable
            // setCar(car(cdr(tree)), car(tree)); //operator->left = variable
            setCdr(car(car(cdr(tree))), cdr(cdr(tree))); //operator->right = expr
            // setCdr(car(cdr(tree)), cdr(cdr(tree))); //operator->right = expr
            // printf("TYPE: %s\n", getType(car(cdr(tree))));
            return eval(car(car(cdr(tree))), env);
        }
    }
}

extern LEXEME *
evalVarDef(LEXEME *tree, LEXEME *env) {
    // printf("In EVALVARDEF\nright type: %s\n", getType(cdr(tree)));
    if (cdr(tree)) {
        if (getType(cdr(tree)) != ARGLIST) {
            // printf("Creating a non-list variable\n");
            return insert(car(tree), env, eval(cdr(tree), env));
        }
        else if (getType(cdr(tree)) == ARGLIST) {
            LEXEME *eargs = eval(cdr(tree), env); //evaluated expressions
            LEXEME *new = evalNewArray(eargs, getLEXEMEString(car(tree)));
            return insert(car(tree), env, new);
        }
    }
    else {
        LEXEME *eargs = eval(cdr(tree), env); //evaluated expressions
        LEXEME *new = evalNewArray(eargs, getLEXEMEString(car(tree)));
        return insert(car(tree), env, new);
    }

}

extern LEXEME *
evalNewArray(LEXEME *eargs, char *name) {
    // printf("In EVALNEWARRAY\n");
    int size = getListSize(eargs);
    // printf("SIZE: %d\n", size);
    LEXEME *a = newLEXEMEArray(ARRAY, size, name);
    // LEXEME **array = getLEXEMEarray(a);
    LEXEME *next = eargs;
    for (int i = 0; i<size; i++) {
        LEXEME *e = car(next);
        setLEXEMEarray(a, i, e);
        next = cdr(next);
    }
    assert(a != NULL);
    return a;
}

extern LEXEME *
evalGetArray(LEXEME *name, int index, LEXEME *env) {
    LEXEME *arr = eval(name, env);
    // printf("ARR TYPE: %s\n", getType(arr));
    if (arr != NULL) {
        if (index < getLEXEMEarraySize(arr)) {
            return getLEXEMEarrayVal(arr, index);
        }
        else {
            printf("INDEX RANGE OUT OF BOUNDS\nFatal on line %d\n", getLEXEMEline(arr));
            exit(1);
        }
    }
    else {
        printf("ARRAY WAS NOT FOUND\nFatal on line %d\n", getLEXEMEline(name));
        exit(1);
    }
}

extern int
getListSize(LEXEME *eargs) {
    if (eargs == NULL) return 0;
    LEXEME *e = car(eargs);
    char *type = getType(e);
    LEXEME *next = cdr(eargs);
    int size = 1;
    while (next != NULL) {
        e = car(next);
        if (strcmp(getType(e), type) != 0) {
            printf("ALL ARRAY ITEMS MUST BE OF SAME TYPE (%s this instance)\nFatal on line %d.\n", type, getLEXEMEline(e));
            exit(1);
        }
        size ++;
        next = cdr(next);
    }
    return size;
}

extern LEXEME *
evalFuncDef(LEXEME *tree, LEXEME *env) {
    LEXEME *closure = cons(CLOSURE, env, tree);
    return insert(car(car(tree)), env, closure);
}

extern LEXEME *
evalFuncCall(LEXEME *tree, LEXEME *env) {
    // printf("In EVALFUNCCALL\n");
    // LEXEME *closure = eval(car(tree), env); //search call name, should return funcDef
    // if (closure == NULL) {
    //     printf("THIS FUNCTIONS DOES NOT EXIST\nFatal on line %d\n", getLEXEMEline(tree));
    //     exit(1);
    // }
    // LEXEME *args = cdr(tree); //argList, or NULL
    // LEXEME *params = cdr(car(closure)); //funcDef argList
    // LEXEME *body = car(cdr(closure));
    // LEXEME *r;
    // if (cdr(cdr(closure))) r = cdr(cdr(closure)); //returnStatement
    // else r = NULL;
    // LEXEME *senv = car(closure); //closure's environment
    // LEXEME *eargs = eval(args, env);
    // LEXEME *xenv = extend(params, eargs, senv);
    //
    // //insert a variable that points to xenv
    // insert(newLEXEMEString(VARIABLE, "this"), xenv, xenv);
    //
    // LEXEME *res = eval(body, xenv);
    // if (r) return eval(r, xenv);
    // else return res;
    LEXEME *name = car(tree);
    LEXEME *args = cdr(tree); //arglist, or null
    // printf("got left and right of FUNCCALL\n");
    LEXEME *eargs;
    if (args) eargs = eval(args, env);
    else eargs = NULL;
    // printf("hello\n");
    LEXEME *closure = eval(name, env);
    // printf("TYPE OF CLOSURE: %s\n", getType(closure));
    if (closure == NULL) {
            printf("THIS FUNCTIONS DOES NOT EXIST\nFatal on line %d\n", getLEXEMEline(tree));
            exit(1);
    }
    else if (getType(closure) == BUILTIN) {
        // printf("It is a builtin\n");
        return evalBuiltin(name, eargs);
    }
    else {
        LEXEME *params = cdr(car(cdr(closure))); //funcDef argList
        LEXEME *body = car(cdr(cdr(closure))); //block
        LEXEME *r;
        if (cdr(cdr(cdr(closure)))) r = cdr(cdr(cdr(closure))); //returnStatement
        else r = NULL;
        LEXEME *senv = car(closure);
        LEXEME *xenv = extend(params, eargs, senv);

        // //insert a variable that points to xenv
        // insert(newLEXEMEString(VARIABLE, "this"), xenv, xenv);

        LEXEME *res = eval(body, xenv);
        if (r) return eval(r, xenv);
        else return res;
    }
}

extern LEXEME *
evalBuiltin(LEXEME *name, LEXEME *eargs) {
    // printf("In EVALBUILTIN\n");
    if (strcmp(getLEXEMEString(name), "print") == 0) {
        return evalPrint(eargs);
    }
    else if (strcmp(getLEXEMEString(name), "printNewLine") == 0) {
        return evalPrintNewLine(eargs);
    }
    else return NULL;
}

extern LEXEME *
evalPrint(LEXEME *eargs) {
    // printf("In EVALPRINT\n");
    if (eargs == NULL) {
        printf("\n");
        return NULL;
    }
    LEXEME *evaluated = car(car(car((eargs))));
    // printf("TYPE: %s\n", getType(evaluated));
    if (getType(evaluated) == STRING) {
        printf("%s", getLEXEMEString(evaluated));
    }
    else if (getType(evaluated) == INTEGER) {
        printf("%d", getLEXEMEInt(evaluated));
    }
    else if (getType(evaluated) == REAL) {
        printf("%lf", getLEXEMEReal(evaluated));
    }
    else if (getType(evaluated) == BOOLEAN) {
        if (getLEXEMEInt(evaluated) == 1) printf("true");
        else printf("false");
    }
    else {
        printf("CAN ONLY PRINT UNARIES\nFatal on line %d\n", getLEXEMEline(evaluated));
        exit(1);
    }
    return NULL;
}

extern LEXEME *
evalPrintNewLine(LEXEME *eargs) {
    if (eargs == NULL) printf("\n");
    else {
        printf("PRINTNEWLINE TAKES NO ARGUMENTS\nFatal BUILTIN error.\n");
        exit(1);
    }
    return NULL;
}

extern LEXEME *
evalReturn(LEXEME *tree, LEXEME *env) {
    if (car(tree)) {
        return eval(car(tree), env);
    }
    else if (cdr(tree)) {
        return eval(cdr(tree), env);
    }
    else return NULL;
}

extern LEXEME *
evalIf(LEXEME *tree, LEXEME *env) {
    LEXEME *ienv = extend(NULL, NULL, env);
    LEXEME *res = eval(car(tree), ienv); //should return a boolean lexeme
    if (getLEXEMEInt(res)) {
        return eval(car(cdr(tree)), env);
    }
    else return eval(cdr(cdr(tree)), env);
}

extern LEXEME *
evalOptElse(LEXEME *tree, LEXEME *env) {
    if (getType(car(tree)) == BLOCK) {
        LEXEME *eenv = extend(NULL, NULL, env);
        return evalBlock(car(tree), eenv);
    }
    else return evalIf(car(tree), env);
}

extern LEXEME *
evalWhileLoop(LEXEME *tree, LEXEME *env) {
    LEXEME *wenv = extend(NULL, NULL, env);
    LEXEME *res = eval(car(tree), wenv);
    LEXEME *done;
    while(getLEXEMEInt(res)) {
        done = eval(cdr(tree), wenv);
        res = eval(car(tree), wenv);
    }
    return res;
}

extern LEXEME *
evalForLoop(LEXEME *tree, LEXEME *env) {
    LEXEME *fenv = extend(NULL, NULL, env);
    eval(car(car(tree)), fenv); //varDef
    LEXEME *fc = eval(car(cdr(car(tree))), fenv); //forCheck aka expression
    while (getLEXEMEInt(fc)) {
        eval(cdr(tree), env); //block
        eval(cdr(cdr(car(tree))), fenv); //forOp aka expression
        fc = eval(car(cdr(car(tree))), fenv); //forCheck aka expression
    }
    return fc;
}

extern LEXEME *
evalLambda(LEXEME *tree, LEXEME *env) {
    return cons(CLOSURE, env, tree);
}

extern LEXEME *
evalSetArray(LEXEME *name, int index, LEXEME *new, LEXEME *env) {
    LEXEME *arr = eval(name, env);
    if (arr != NULL) {
        if (index < getLEXEMEarraySize(name)) {
            return setLEXEMEarray(arr, index, new);
        }
        else {
            printf("INDEX RANGE OUT OF BOUNDS\nFatal on line %d\n", getLEXEMEline(arr));
            exit(1);
        }
    }
    else {
        printf("ARRAY WAS NOT FOUND\nFatal on line %d\n", getLEXEMEline(name));
        exit(1);
    }
}



/** OPERATOR EVALUATORS **/
extern LEXEME *
evalSelfOp(LEXEME *tree, LEXEME *env) {
    if (getType(tree) == PLUSPLUS) return evalPlusPlus(tree, env);
    else if (getType(tree) == MINUSMINUS) return evalMinusMinus(tree, env);
    else return NULL;
}

extern LEXEME *
evalPlusPlus(LEXEME *tree, LEXEME *env) {
    if (getType(car(tree)) == GLUE) { //it's an array
        LEXEME *val = evalGetArray(car(car(tree)), getLEXEMEInt(cdr(car(tree))), env);
        if (getType(val) == INTEGER) return evalSetArray(car(car(tree)), getLEXEMEInt(cdr(car(tree))), newLEXEMEInt(INTEGER, getLEXEMEInt(val) + 1), env);
        else if (getType(val) == REAL) return evalSetArray(car(car(tree)), getLEXEMEInt(cdr(car(tree))), newLEXEMEReal(REAL, getLEXEMEReal(val) + 1.0), env);
        else {
            printf("CAN ONLY INCREMENT NUMBERS\nExit on line %d\n", getLEXEMEline(val));
            exit(1);
        }
    }
    else {
        LEXEME *val = eval(car(tree), env); //should return lookup(variable) which is a value
        if (getType(val) == INTEGER) return newLEXEMEInt(INTEGER, getLEXEMEInt(car(tree))+1);
        else if (getType(val) == REAL) return newLEXEMEReal(REAL, getLEXEMEReal(car(tree)) + 1.0);
        else {
            printf("CAN ONLY INCREMENT NUMBERS\nExit on line %d\n", getLEXEMEline(val));
            exit(1);
        }
    }
}

extern LEXEME *
evalMinusMinus(LEXEME *tree, LEXEME *env) {
    if (getType(car(tree)) == GLUE) { //it's an array
        LEXEME *val = evalGetArray(car(car(tree)), getLEXEMEInt(cdr(car(tree))), env);
        if (getType(val) == INTEGER) return evalSetArray(car(car(tree)), getLEXEMEInt(cdr(car(tree))), newLEXEMEInt(INTEGER, getLEXEMEInt(val) - 1), env);
        else if (getType(val) == REAL) return evalSetArray(car(car(tree)), getLEXEMEInt(cdr(car(tree))), newLEXEMEReal(REAL, getLEXEMEReal(val) - 1.0), env);
        else {
            printf("CAN ONLY DECREMENT NUMBERS\nExit on line %d\n", getLEXEMEline(val));
            exit(1);
        }
    }
    else {
        LEXEME *val = eval(car(tree), env);
        if (getType(val) == INTEGER) return newLEXEMEInt(INTEGER, getLEXEMEInt(car(tree))-1);
        else if (getType(val) == REAL) return newLEXEMEReal(REAL, getLEXEMEReal(car(tree)) - 1.0);
        else {
            printf("CAN ONLY DECREMENT NUMBERS\nExit on line %d\n", getLEXEMEline(val));
            exit(1);
        }
    }
}

extern LEXEME *
evalOp(LEXEME *tree, LEXEME *env) {
    // printf("in EVALOP\ntype of left is %s\n", getType(car(tree)));
    // if (cdr(tree)) printf("type of right is %s\n", getType(cdr(tree)));
    if (getType(tree) == PLUS) return evalPlus(tree, env); //done
    else if (getType(tree) == MINUS) return evalMinus(tree, env); //done
    else if (getType(tree) == TIMES) return evalTimes(tree, env); //done
    else if (getType(tree) == DIVIDE) return evalDivide(tree, env); //done
    else if (getType(tree) == GREATERTHAN) return evalGreaterThan(tree, env); //done
    else if (getType(tree) == LESSTHAN) return evalLessThan(tree, env); //done
    else if (getType(tree) == GREATEREQUALS) return evalGreaterEquals(tree, env); //done
    else if (getType(tree) == LESSEQUALS) return evalLessEquals(tree, env); //done
    else if (getType(tree) == MOD) return evalMod(tree, env); //done
    else if (getType(tree) == NOT) return evalNot(tree, env); //done
    else if (getType(tree) == ANDAND) return evalAndAnd(tree, env); //done
    else if (getType(tree) == OROR) return evalOrOr(tree, env); //done
    else if (getType(tree) == EQUALSEQUALS) return evalEqualsEquals(tree, env); //done
    else if (getType(tree) == PEQUALS) return evalPlusEquals(tree, env); //done
    else if (getType(tree) == MINUSEQUALS) return evalMinusEquals(tree, env); //done
    else if (getType(tree) == TIMESEQUALS) return evalTimesEquals(tree, env); //done
    else if (getType(tree) == DIVIDEEQUALS) return evalDivideEquals(tree, env); //done
    else if (getType(tree) == ASSIGN) return evalAssign(tree, env); //done
}

extern LEXEME *
evalPlus(LEXEME *tree, LEXEME *env) {
    // printf("in EVALPLUS\n");
    // printf("LEFT TYPE: %s\nRIGHT TYPE: %s\n", getType(car(tree)), getType(cdr(tree)));
    LEXEME *left = eval(car(tree), env);
    // printf("done with left. type: %s\n", getType(left));
    LEXEME *right = eval(cdr(tree), env);
    // printf("POST LEFT TYPE: %s\nPOST RIGHT TYPE: %s\n", getType(left), getType(right));
    if (getType(left) == INTEGER && getType(right) == INTEGER) return newLEXEMEInt(INTEGER, getLEXEMEInt(left) + getLEXEMEInt(right));
    else if (getType(left) == INTEGER && getType(right) == REAL) return newLEXEMEReal(REAL, getLEXEMEInt(left) + getLEXEMEReal(right));
    else if (getType(left) == REAL && getType(right) == INTEGER) return newLEXEMEReal(REAL, getLEXEMEReal(left) + getLEXEMEInt(right));
    else if (getType(left) == REAL && getType(right) == REAL) return newLEXEMEReal(REAL, getLEXEMEReal(left) + getLEXEMEReal(right));
    else if (getType(left) == STRING && getType(right) == STRING) return newLEXEMEString(STRING, strcat(getLEXEMEString(left), getLEXEMEString(right)));
    else {
        printf("CANNOT ADD THESE on line %d\n", getLEXEMEline(left));
        exit(1);
    }
}

extern LEXEME *
evalMinus(LEXEME *tree, LEXEME *env) {
    LEXEME *left = eval(car(tree), env);
    LEXEME *right = eval(cdr(tree), env);
    if (getType(left) == INTEGER && getType(right) == INTEGER) return newLEXEMEInt(INTEGER, getLEXEMEInt(left) - getLEXEMEInt(right));
    else if (getType(left) == INTEGER && getType(right) == REAL) return newLEXEMEReal(REAL, getLEXEMEInt(left) - getLEXEMEReal(right));
    else if (getType(left) == REAL && getType(right) == INTEGER) return newLEXEMEReal(REAL, getLEXEMEReal(left) - getLEXEMEInt(right));
    else if (getType(left) == REAL && getType(right) == REAL) return newLEXEMEReal(REAL, getLEXEMEReal(left) - getLEXEMEReal(right));
    else {
        printf("CAN ONLY SUBTRACT NUMBERS\nFatal on line %d\n", getLEXEMEline(left));
        exit(1);
    }
}

extern LEXEME *
evalTimes(LEXEME *tree, LEXEME *env) {
    LEXEME *left = eval(car(tree), env);
    LEXEME *right = eval(cdr(tree), env);
    if (getType(left) == INTEGER && getType(right) == INTEGER) return newLEXEMEInt(INTEGER, getLEXEMEInt(left) * getLEXEMEInt(right));
    else if (getType(left) == INTEGER && getType(right) == REAL) return newLEXEMEReal(REAL, getLEXEMEInt(left) * getLEXEMEReal(right));
    else if (getType(left) == REAL && getType(right) == INTEGER) return newLEXEMEReal(REAL, getLEXEMEReal(left) * getLEXEMEInt(right));
    else if (getType(left) == REAL && getType(right) == REAL) return newLEXEMEReal(REAL, getLEXEMEReal(left) * getLEXEMEReal(right));
    else {
        printf("CAN ONLY MULTIPLY NUMBERS\nFatal on line %d\n", getLEXEMEline(left));
        exit(1);
    }
}

extern LEXEME *
evalDivide(LEXEME *tree, LEXEME *env) {
    LEXEME *left = eval(car(tree), env);
    LEXEME *right = eval(cdr(tree), env);
    if (getType(left) == INTEGER && getType(right) == INTEGER) return newLEXEMEInt(INTEGER, getLEXEMEInt(left) / getLEXEMEInt(right));
    else if (getType(left) == INTEGER && getType(right) == REAL) return newLEXEMEReal(REAL, getLEXEMEInt(left) / getLEXEMEReal(right));
    else if (getType(left) == REAL && getType(right) == INTEGER) return newLEXEMEReal(REAL, getLEXEMEReal(left) / getLEXEMEInt(right));
    else if (getType(left) == REAL && getType(right) == REAL) return newLEXEMEReal(REAL, getLEXEMEReal(left) / getLEXEMEReal(right));
    else {
        printf("CAN ONLY DIVIDE NUMBERS\nFatal on line %d\n", getLEXEMEline(left));
        exit(1);
    }
}

extern LEXEME *
evalGreaterThan(LEXEME *tree, LEXEME *env) {
    LEXEME *left = eval(car(tree), env);
    LEXEME *right = eval(cdr(tree), env);
    if (getType(left) == INTEGER && getType(right) == INTEGER) {
        if (getLEXEMEInt(left) > getLEXEMEInt(right)) {
            return newLEXEMEInt(BOOLEAN, 1);
        }
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == INTEGER && getType(right) == REAL) {
        if (getLEXEMEInt(left) > getLEXEMEReal(right)) {
            return newLEXEMEInt(BOOLEAN, 1);
        }
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == REAL && getType(right) == INTEGER) {
        if (getLEXEMEReal(left) > getLEXEMEInt(right)) {
            return newLEXEMEInt(BOOLEAN, 1);
        }
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == REAL && getType(right) == REAL) {
        if (getLEXEMEReal(left) > getLEXEMEReal(right)) {
            return newLEXEMEInt(BOOLEAN, 1);
        }
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == STRING && getType(right) == STRING) {
        if (strcmp(getLEXEMEString(left), getLEXEMEString(right)) > 0) return newLEXEMEInt(BOOLEAN, 1);
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else {
        printf("CAN ONLY COMPARE STRINGS AND NUMBERS\nFatal on line %d\n", getLEXEMEline(left));
        exit(1);
    }
}

extern LEXEME *
evalLessThan(LEXEME *tree, LEXEME *env) {
    LEXEME *left = eval(car(tree), env);
    LEXEME *right = eval(cdr(tree), env);
    if (getType(left) == INTEGER && getType(right) == INTEGER) {
        if (getLEXEMEInt(left) < getLEXEMEInt(right)) {
            return newLEXEMEInt(BOOLEAN, 1);
        }
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == INTEGER && getType(right) == REAL) {
        if (getLEXEMEInt(left) < getLEXEMEReal(right)) {
            return newLEXEMEInt(BOOLEAN, 1);
        }
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == REAL && getType(right) == INTEGER) {
        if (getLEXEMEReal(left) < getLEXEMEInt(right)) {
            return newLEXEMEInt(BOOLEAN, 1);
        }
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == REAL && getType(right) == REAL) {
        if (getLEXEMEReal(left) < getLEXEMEReal(right)) {
            return newLEXEMEInt(BOOLEAN, 1);
        }
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == STRING && getType(right) == STRING) {
        if (strcmp(getLEXEMEString(left), getLEXEMEString(right)) < 0) return newLEXEMEInt(BOOLEAN, 1);
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else {
        printf("CAN ONLY COMPARE STRINGS AND NUMBERS\nFatal on line %d\n", getLEXEMEline(left));
        exit(1);
    }
}

extern LEXEME *
evalGreaterEquals(LEXEME *tree, LEXEME *env) {
    LEXEME *left = eval(car(tree), env);
    LEXEME *right = eval(cdr(tree), env);
    if (getType(left) == INTEGER && getType(right) == INTEGER) {
        if (getLEXEMEInt(left) >= getLEXEMEInt(right)) {
            return newLEXEMEInt(BOOLEAN, 1);
        }
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == INTEGER && getType(right) == REAL) {
        if (getLEXEMEInt(left) >= getLEXEMEReal(right)) {
            return newLEXEMEInt(BOOLEAN, 1);
        }
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == REAL && getType(right) == INTEGER) {
        if (getLEXEMEReal(left) >= getLEXEMEInt(right)) {
            return newLEXEMEInt(BOOLEAN, 1);
        }
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == REAL && getType(right) == REAL) {
        if (getLEXEMEReal(left) >= getLEXEMEReal(right)) {
            return newLEXEMEInt(BOOLEAN, 1);
        }
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == STRING && getType(right) == STRING) {
        if (strcmp(getLEXEMEString(left), getLEXEMEString(right)) >= 0) return newLEXEMEInt(BOOLEAN, 1);
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else {
        printf("CAN ONLY COMPARE STRINGS AND NUMBERS\nFatal on line %d\n", getLEXEMEline(left));
        exit(1);
    }
}

extern LEXEME *
evalLessEquals(LEXEME *tree, LEXEME *env) {
    LEXEME *left = eval(car(tree), env);
    LEXEME *right = eval(cdr(tree), env);
    if (getType(left) == INTEGER && getType(right) == INTEGER) {
        if (getLEXEMEInt(left) <= getLEXEMEInt(right)) {
            return newLEXEMEInt(BOOLEAN, 1);
        }
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == INTEGER && getType(right) == REAL) {
        if (getLEXEMEInt(left) <= getLEXEMEReal(right)) {
            return newLEXEMEInt(BOOLEAN, 1);
        }
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == REAL && getType(right) == INTEGER) {
        if (getLEXEMEReal(left) <= getLEXEMEInt(right)) {
            return newLEXEMEInt(BOOLEAN, 1);
        }
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == REAL && getType(right) == REAL) {
        if (getLEXEMEReal(left) <= getLEXEMEReal(right)) {
            return newLEXEMEInt(BOOLEAN, 1);
        }
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == STRING && getType(right) == STRING) {
        if (strcmp(getLEXEMEString(left), getLEXEMEString(right)) <= 0) return newLEXEMEInt(BOOLEAN, 1);
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else {
        printf("CAN ONLY COMPARE STRINGS AND NUMBERS\nFatal on line %d\n", getLEXEMEline(left));
        exit(1);
    }
}

extern LEXEME *
evalEqualsEquals(LEXEME *tree, LEXEME *env) {
    LEXEME *left = eval(car(tree), env);
    LEXEME *right = eval(cdr(tree), env);
    if (getType(left) == INTEGER && getType(right) == INTEGER) {
        if (getLEXEMEInt(left) == getLEXEMEInt(right)) {
            return newLEXEMEInt(BOOLEAN, 1);
        }
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == INTEGER && getType(right) == REAL) {
        if (getLEXEMEInt(left) == getLEXEMEReal(right)) {
            return newLEXEMEInt(BOOLEAN, 1);
        }
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == REAL && getType(right) == INTEGER) {
        if (getLEXEMEReal(left) == getLEXEMEInt(right)) {
            return newLEXEMEInt(BOOLEAN, 1);
        }
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == REAL && getType(right) == REAL) {
        if (getLEXEMEReal(left) == getLEXEMEReal(right)) {
            return newLEXEMEInt(BOOLEAN, 1);
        }
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == STRING && getType(right) == STRING) {
        if (strcmp(getLEXEMEString(left), getLEXEMEString(right)) == 0) return newLEXEMEInt(BOOLEAN, 1);
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else {
        printf("CAN ONLY COMPARE STRINGS AND NUMBERS\nFatal on line %d\n", getLEXEMEline(left));
        exit(1);
    }
}

extern LEXEME *
evalMod(LEXEME *tree, LEXEME *env) {
    LEXEME *left = eval(car(tree), env);
    LEXEME *right = eval(cdr(tree), env);
    if (getType(left) == INTEGER && getType(right) == INTEGER) return newLEXEMEInt(INTEGER, getLEXEMEInt(left) % getLEXEMEInt(right));
    else {
        printf("CAN ONLY MOD INTEGERS\nFatal on line %d\n", getLEXEMEline(left));
        exit(1);
    }
}

extern LEXEME *
evalNot(LEXEME *tree, LEXEME *env) {
    LEXEME *left = eval(car(tree), env);
    LEXEME *right = eval(cdr(tree), env);
    if (getType(left) == INTEGER && getType(right) == INTEGER) {
        if (getLEXEMEInt(left) == getLEXEMEInt(right)) {
            return newLEXEMEInt(BOOLEAN, 0);
        }
        else return newLEXEMEInt(BOOLEAN, 1);
    }
    else if (getType(left) == INTEGER && getType(right) == REAL) {
        if (getLEXEMEInt(left) == getLEXEMEReal(right)) {
            return newLEXEMEInt(BOOLEAN, 0);
        }
        else return newLEXEMEInt(BOOLEAN, 1);
    }
    else if (getType(left) == REAL && getType(right) == INTEGER) {
        if (getLEXEMEReal(left) == getLEXEMEInt(right)) {
            return newLEXEMEInt(BOOLEAN, 0);
        }
        else return newLEXEMEInt(BOOLEAN, 1);
    }
    else if (getType(left) == REAL && getType(right) == REAL) {
        if (getLEXEMEReal(left) == getLEXEMEReal(right)) {
            return newLEXEMEInt(BOOLEAN, 0);
        }
        else return newLEXEMEInt(BOOLEAN, 1);
    }
    else if (getType(left) == STRING && getType(right) == STRING) {
        if (strcmp(getLEXEMEString(left), getLEXEMEString(right)) == 0) return newLEXEMEInt(BOOLEAN, 1);
        else return newLEXEMEInt(BOOLEAN, 1);
    }
    else {
        printf("CAN ONLY COMPARE STRINGS AND NUMBERS\nFatal on line %d\n", getLEXEMEline(left));
        exit(1);
    }
}

extern LEXEME *
evalAndAnd(LEXEME *tree, LEXEME *env) {
    LEXEME *left = eval(car(tree), env);
    LEXEME *right = eval(cdr(tree), env);
    if (getType(left) == INTEGER && getType(right) == INTEGER) {
        if (getLEXEMEInt(left) == 1 && getLEXEMEInt(right) == 1) return newLEXEMEInt(BOOLEAN, 1);
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == INTEGER && getType(right) == BOOLEAN) {
        if (getLEXEMEInt(left) == 1 && getLEXEMEInt(right) == 1) return newLEXEMEInt(BOOLEAN, 1);
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == BOOLEAN && getType(right) == INTEGER) {
        if (getLEXEMEInt(left) == 1 && getLEXEMEInt(right) == 1) return newLEXEMEInt(BOOLEAN, 1);
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == BOOLEAN && getType(right) == BOOLEAN) {
        if (getLEXEMEInt(left) == 1 && getLEXEMEInt(right) == 1) return newLEXEMEInt(BOOLEAN, 1);
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else {
        printf("CAN ONLY BOOLEANS AND INTEGERS WITH &&\nFatal on line %d\n", getLEXEMEline(left));
        exit(1);
    }
}

extern LEXEME *
evalOrOr(LEXEME *tree, LEXEME *env) {
    LEXEME *left = eval(car(tree), env);
    LEXEME *right = eval(cdr(tree), env);
    if (getType(left) == INTEGER && getType(right) == INTEGER) {
        if (getLEXEMEInt(left) == 1 || getLEXEMEInt(right) == 1) return newLEXEMEInt(BOOLEAN, 1);
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == INTEGER && getType(right) == BOOLEAN) {
        if (getLEXEMEInt(left) == 1 || getLEXEMEInt(right) == 1) return newLEXEMEInt(BOOLEAN, 1);
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == BOOLEAN && getType(right) == INTEGER) {
        if (getLEXEMEInt(left) == 1 || getLEXEMEInt(right) == 1) return newLEXEMEInt(BOOLEAN, 1);
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else if (getType(left) == BOOLEAN && getType(right) == BOOLEAN) {
        if (getLEXEMEInt(left) == 1 || getLEXEMEInt(right) == 1) return newLEXEMEInt(BOOLEAN, 1);
        else return newLEXEMEInt(BOOLEAN, 0);
    }
    else {
        printf("CAN ONLY BOOLEANS AND INTEGERS WITH &&\nFatal on line %d\n", getLEXEMEline(left));
        exit(1);
    }
}

extern LEXEME *
evalPlusEquals(LEXEME *tree, LEXEME *env) {
    LEXEME *left = eval(car(tree), env);
    LEXEME *right = eval(cdr(tree), env);
    LEXEME *result;
    if (getType(left) == INTEGER && getType(right) == INTEGER) {
        result = newLEXEMEInt(INTEGER, getLEXEMEInt(left) + getLEXEMEInt(right));
        return update(car(tree), env, result);
    }
    else if (getType(left) == INTEGER && getType(right) == REAL) {
        result = newLEXEMEReal(REAL, getLEXEMEInt(left) + getLEXEMEReal(right));
        return update(car(tree), env, result);
    }
    else if (getType(left) == REAL && getType(right) == REAL) {
        result = newLEXEMEReal(REAL, getLEXEMEReal(left) + getLEXEMEReal(right));
        return update(car(tree), env, result);
    }
    else if (getType(left) == REAL && getType(right) == INTEGER) {
        result = newLEXEMEReal(INTEGER, getLEXEMEReal(left) + getLEXEMEInt(right));
        return update(car(tree), env, result);
    }
    else if (getType(left) == STRING && getType(right) == STRING) {
        result = newLEXEMEString(STRING, strcat(getLEXEMEString(left), getLEXEMEString(right)));
        return update(car(tree), env, result);
    }
    else {
        printf("CAN ONLY ADD STRINGS AND NUMBERS\nFatal on line %d\n", getLEXEMEline(left));
        exit(1);
    }
}

extern LEXEME *
evalMinusEquals(LEXEME *tree, LEXEME *env) {
    LEXEME *left = eval(car(tree), env);
    LEXEME *right = eval(cdr(tree), env);
    LEXEME *result;
    if (getType(left) == INTEGER && getType(right) == INTEGER) {
        result = newLEXEMEInt(INTEGER, getLEXEMEInt(left) - getLEXEMEInt(right));
        return update(car(tree), env, result);
    }
    else if (getType(left) == INTEGER && getType(right) == REAL) {
        result = newLEXEMEReal(REAL, getLEXEMEInt(left) - getLEXEMEReal(right));
        return update(car(tree), env, result);
    }
    else if (getType(left) == REAL && getType(right) == REAL) {
        result = newLEXEMEReal(REAL, getLEXEMEReal(left) - getLEXEMEReal(right));
        return update(car(tree), env, result);
    }
    else if (getType(left) == REAL && getType(right) == INTEGER) {
        result = newLEXEMEReal(INTEGER, getLEXEMEReal(left) - getLEXEMEInt(right));
        return update(car(tree), env, result);
    }
    // else if (getType(left) == STRING && getType(right) == STRING) {
    //     result = newLEXEMEString(STRING, strcat(getLEXEMEString(left), getLEXEMEString(right)));
    //     return update(car(tree), env, result);
    // }
    else {
        printf("CAN ONLY ADD STRINGS AND NUMBERS\nFatal on line %d\n", getLEXEMEline(left));
        exit(1);
    }
}

extern LEXEME *
evalTimesEquals(LEXEME *tree, LEXEME *env) {
    LEXEME *left = eval(car(tree), env);
    LEXEME *right = eval(cdr(tree), env);
    LEXEME *result;
    if (getType(left) == INTEGER && getType(right) == INTEGER) {
        result = newLEXEMEInt(INTEGER, getLEXEMEInt(left) * getLEXEMEInt(right));
        return update(car(tree), env, result);
    }
    else if (getType(left) == INTEGER && getType(right) == REAL) {
        result = newLEXEMEReal(REAL, getLEXEMEInt(left) * getLEXEMEReal(right));
        return update(car(tree), env, result);
    }
    else if (getType(left) == REAL && getType(right) == REAL) {
        result = newLEXEMEReal(REAL, getLEXEMEReal(left) * getLEXEMEReal(right));
        return update(car(tree), env, result);
    }
    else if (getType(left) == REAL && getType(right) == INTEGER) {
        result = newLEXEMEReal(INTEGER, getLEXEMEReal(left) * getLEXEMEInt(right));
        return update(car(tree), env, result);
    }
    // else if (getType(left) == STRING && getType(right) == STRING) {
    //     result = newLEXEMEString(STRING, strcat(getLEXEMEString(left), getLEXEMEString(right)));
    //     return update(car(tree), env, result);
    // }
    else {
        printf("CAN ONLY MULTIPLY NUMBERS\nFatal on line %d\n", getLEXEMEline(left));
        exit(1);
    }
}

extern LEXEME *
evalDivideEquals(LEXEME *tree, LEXEME *env) {
    LEXEME *left = eval(car(tree), env);
    LEXEME *right = eval(cdr(tree), env);
    LEXEME *result;
    if (getType(left) == INTEGER && getType(right) == INTEGER) {
        result = newLEXEMEInt(INTEGER, getLEXEMEInt(left) / getLEXEMEInt(right));
        return update(car(tree), env, result);
    }
    else if (getType(left) == INTEGER && getType(right) == REAL) {
        result = newLEXEMEReal(REAL, getLEXEMEInt(left) / getLEXEMEReal(right));
        return update(car(tree), env, result);
    }
    else if (getType(left) == REAL && getType(right) == REAL) {
        result = newLEXEMEReal(REAL, getLEXEMEReal(left) / getLEXEMEReal(right));
        return update(car(tree), env, result);
    }
    else if (getType(left) == REAL && getType(right) == INTEGER) {
        result = newLEXEMEReal(INTEGER, getLEXEMEReal(left) / getLEXEMEInt(right));
        return update(car(tree), env, result);
    }
    // else if (getType(left) == STRING && getType(right) == STRING) {
    //     result = newLEXEMEString(STRING, strcat(getLEXEMEString(left), getLEXEMEString(right)));
    //     return update(car(tree), env, result);
    // }
    else {
        printf("CAN ONLY MULTIPLY NUMBERS\nFatal on line %d\n", getLEXEMEline(left));
        exit(1);
    }
}

extern LEXEME *
evalAssign(LEXEME *tree, LEXEME *env) {
    printf("in EVALASSIGN\n");
    LEXEME *right = eval(cdr(tree), env);
    printf("RIGHT TYPE: %s\n", getType(right));
    if (getType(car(tree)) == GLUE) { //updating an array
        // LEXEME *val = evalGetArray(car(car(tree)), getLEXEMEInt(cdr(car(tree))), env);
        LEXEME *a = evalSetArray(car(car(tree)), getLEXEMEInt(cdr(car(tree))), right, env);
        return update(car(car(tree)), env, a);
    }
    else return update(car(tree), env, right);
}

// extern LEXEME *
// node(LEXEME *value, LEXEME *next) {
//
// }

// extern LEXEME *
// evalDot(LEXEME *tree, LEXEME *env) {
//     if (cdr(tree) == NULL) {
//         printf("INVALID DOT OPERATOR EXPRESSION\nFatal on line %d\n", getLEXEMEline(cdr(tree)));
//         exit(1);
//     }
//     LEXEME *object = eval(car(tree), env); //variable, evals to an object
//     return eval(cdr(tree), object);
// }
