evalOp/***
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



extern LEXEME *
eval(LEXEME *tree, LEXEME *env) {
    switch(getType(tree)) {
        case INTEGER: return tree;
        case STRING: return tree;
        case VARIABLE: return lookup(tree, env);
        case VOID: return tree;
        //parenthesized expression
        // case OPAREN: return eval(cdr(tree), env);
        //operatros: evaluate both sides
        case PLUS: return evalOp(tree, env); //done
        case MINUS: return evalOp(tree, env);
        case TIMES: return evalOp(tree, env);
        case DIVIDE: return evalOp(tree, env);
        case PLUSPLUS: return evalOp(tree, env);
        case MINUSMINUS: return evalOp(tree, env);
        case PEQUALS: return evalOp(tree, env);
        case MINUSEQUALS: return evalOp(tree, env);
        case TIMESEQUALS: return evalOp(tree, env);
        case DIVIDEEQUALS: return evalOp(tree, env);
        case GREATERTHAN: return evalOp(tree, env);
        case LESSTHAN: return evalOp(tree, env);
        case GREATEREQUALS: return evalOp(tree, env);
        case LESSEQUALS: return evalOp(tree, env);
        //AND and OR short-circuit
        // case AND: return evalShortCircuitOp(tree, env);
        // case OR: return evalShortCircuitOp(tree, env);
        //dor operator evals lhs, rhs as a variable
        case DOT: return evalDot(tree, env);
        //assign operator evals rhs for sure;
        //lhs is a variable or a dot operation
        case ASSIGN: return evalAssign(tree, env); //done
        //variable and function definitions
        case VARDEF: return evalVarDef(tree, env); //done
        case FUNCDEF: return evalFuncDef(tree, env); //done
        //imperative constructs
        case PROGRAM: return evalProgram(tree, env); //done
        // case INCLUDES: return evalIncludes(tree, env);
        // case INCLUDE: return evalInclude(tree, env);
        case MAINMETHOD: return evalMain(tree, env); //done
        case ARGLIST: return evalArgList(tree, env); //done
        case BLOCK: return evalBlock(tree, env); //done
        case STATEMENTS: return evalStatements(tree, env); //done
        case STATEMENT: return evalStatement(tree, env); //done
        case EXPRESSION: return evalExpression(tree, env); //done
        // case OPERATOR: return evalOperator(tree, env);
        // case UNARY: return evalUnary(tree, env);
        case IFSTATEMENT: return evalIf(tree, env); //done
        case OPTELSE: return evalOptElse(tree, env); //done
        case WHILELOOP: return evalWhileLoop(tree, env); //done
        case FORLOOP: return evalForLoop(tree, env); //done
        // case FORCHECK: return evalForCheck(tree, env);
        // case FOROP: return evalForOp(tree, env);
        case FUNCCALL: return evalFuncCall(tree, env); //done
        case RETURNSTATEMENT: return evalReturn(tree, env); //done

        default: printf("bad expression\n"); return NULL;
    }
}

extern LEXEME *
evalProgram(LEXEME *tree, LEXEME *env) {
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
evalMain(LEXEME *tree, LEXEME *env) {
    LEXEME *arg;
    // if (car(tree)) arg = eval(car(tree)); //argList
    // LEXEME *mainEnv = extend(NULL, NULL, env); //variables, values, env

    LEXEME *main = eval(cdr(tree), env); //block
    // eval(cdr(tree)); //block
    return main;
}

extern LEXEME *
evalArgList(LEXEME *tree, LEXEME *env) {
    return cons(GLUE, eval(car(tree)), eval(cdr(tree)));
}

extern LEXEME *
evalBlock(LEXEME *tree, LEXEME *env) {
    return eval(car(tree), env); //statements
}

extern LEXEME *
evalStatements(LEXEME *tree, LEXEME *env) {
    LEXEME *result = eval(car(tree), env); //statement
    if (cdr(tree)) eval(cdr(tree)); //statements
    return result; //this might cause things to work in reverse
}

extern LEXEME *
evalStatement(LEXEME *tree, LEXEME *env) {
    return eval(car(tree), env); //varDef, ifStatement, whileLoop, forLoop, funcDef, returnStatement, expression
}

extern LEXEME *
evalExpression(LEXEME *tree, LEXEME *env) {
    if (car(cdr(tree)) == NULL) { //if no operator
        return eval(car(tree)); //unary, variable, funcCall
    }
    else { //if operator
        if (cdr(cdr(tree)) == NULL) { //if no expression after operator
            // setCar(car(car(cdr(tree))), car(tree)); //set operator->left = variable
            setCar(car(cdr(tree)), car(tree)); //set operator->left = variable
            return evalSelfOp(car(cdr(tree)), env); //eval operator
        }
        else {
            // setCar(car(car(cdr(tree))), car(tree)); //operator->left = variable
            setCar(car(cdr(tree)), car(tree)); //operator->left = variable
            // setCdr(car(car(cdr(tree))), cdr(cdr(tree))); //operator->right = expr
            setCdr(car(cdr(tree)), cdr(cdr(tree))); //operator->right = expr
            return eval(car(cdr(tree)), env);
        }
    }
}

extern LEXEME *
evalVarDef(LEXEME *tree, LEXEME *env) {
    return insert(car(tree), env, cdr(tree));
}

extern LEXEME *
evalFuncDef(LEXEME *tree, LEXEME *env) {
    LEXEME *closure = cons(CLOSURE, env, tree);
    return insert(car(car(tree)), env, closure);
}

extern LEXEME *
evalFuncCall(LEXEME *tree, LEXEME *env) {
    LEXEME *closure = eval(car(tree), env); //search call name, should return funcDef
    if (closure == NULL) {
        printf("THIS FUNCTIONS DOES NOT EXIST\nFatal on line %d\n", getLEXEMEline(tree));
        exit(1);
    }
    LEXEME *args = cdr(tree); //argList, or NULL
    LEXEME *params = cdr(car(closure)); //funcDef argList
    LEXEME *body = car(cdr(closure));
    if (cdr(cdr(closure))) LEXEME *r = cdr(cdr(closure)); //returnStatement
    else LEXEME *r = NULL;
    LEXEME *senv = car(closure); //closure's environment
    LEXEME *eargs = eval(args, env);
    LEXEME *xenv = extend(params, eargs, senv);

    //insert a variable that points to xenv
    insert(newLEXEMEString(VARIABLE, "this"), xenv, xenv);

    LEXEME *res = eval(body, xenv);
    if (r) return eval(r, xenv);
    else return res;
}

extern LEXEME *
evalReturn(LEXEME *tree, LEXEME *env) {
    if (car(tree)) {
        return eval(car(tree));
    }
    else if (cdr(tree)) {
        return eval(cdr(tree));
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



/** OPERATOR EVALUATORS **/
extern LEXEME *
evalSelfOp(LEXEME *tree, LEXEME *env) {
    if (getType(tree) == PLUSPLUS) return evalPlusPlus(tree, env);
    else if (getType(tree) == MINUSMINUS) return evalMinusMinus(tree, env);
    else return NULL;
}

extern LEXEME *
evalPlusPlus(LEXEME *tree, LEXEME *env) {
    LEXEME *val = eval(car(tree)); //should return lookup(variable) which is a value
    if (getType(val) == INTEGER) return newLEXEMEInt(INTEGER, getLEXEMEInt(car(tree))+1);
    else if (getType(val) == REAL) return newLEXEMEReal(REAL, getLEXEMEReal(car(tree)) + 1.0);
    else {
        printf("CAN ONLY INCREMENT NUMBERS\nExit on line %d\n", getLEXEMEline(val));
        exit(1);
    }
}

extern LEXEME *
evalMinusMinus(LEXEME *tree, LEXEME *env) {
    LEXEME *val = eval(car(tree));
    if (getType(val) == INTEGER) return newLEXEMEInt(INTEGER, getLEXEMEInt(car(tree))-1);
    else if (getType(val) == REAL) return newLEXEMEReal(REAL, getLEXEMEReal(car(tree)) - 1.0);
    else {
        printf("CAN ONLY DECREMENT NUMBERS\nExit on line %d\n", getLEXEMEline(val));
        exit(1);
    }
}

extern LEXEME *
evalOp(LEXEME *tree, LEXEME *env) {
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
    else if (getType(tree) == PEQAULS) return evalPlusEquals(tree, env); //done
    else if (getType(tree) == MINUSEQUALS) return evalMinusEquals(tree, env); //done
    else if (getType(tree) == TIMESEQUALS) return evalTimesEquals(tree, env); //done
    else if (getType(tree) == DIVIDEEQUALS) return evalDivideEquals(tree, env); //done
    else if (getType(tree) == ASSIGN) return evalAssign(tree, env); //done
}

extern LEXEME *
evalPlus(LEXEME *tree, LEXEME *env) {
    LEXEME *left = eval(car(tree), env);
    LEXEME *right = eval(cdr(tree), env);
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
    else if (gettype(left) == STRING && getType(right) == STRING) {
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
    else if (gettype(left) == STRING && getType(right) == STRING) {
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
    else if (gettype(left) == STRING && getType(right) == STRING) {
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
    else if (gettype(left) == STRING && getType(right) == STRING) {
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
    else if (gettype(left) == STRING && getType(right) == STRING) {
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
    else if (gettype(left) == STRING && getType(right) == STRING) {
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
    LEXEME *right = eval(cdr(tree), env);
    return update(car(tree), env, right);
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
