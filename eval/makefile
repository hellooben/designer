#Ben Bailey
#makefile for the evaluator

OPTS = -Wall -Wextra
OBJS = types.o lexing.o recognize.o environment.o pretty.o eval.o print.o driver.o eval a.out print pp

all : eval

eval :
	gcc $(OPTS) -c driver.c eval.c recognize.c lexing.c environment.c pretty.c types.c
	gcc $(OPTS) types.o pretty.o environment.o lexing.o recognize.o eval.o driver.o -o eval

print :
	gcc $(OPTS) -c print.c pretty.c recognize.c environment.c lexing.c types.c
	gcc $(OPTS) types.o lexing.o environment.o recognize.o pretty.o print.o -o pp

error1 : print #syntax error: missing "!"
	./pp e1.bean

error1x : eval
	./eval e1.bean

error2 : print #syntax error: unexpected character
	./pp e2.bean

error2x : eval
	./eval e2.bean

error3 : print #syntax error: typed variable definition
	./pp e3.bean

error3x : eval
	./eval e3.bean

error4 : print #semantic error: array access out of bounds
	./pp e4.bean

error4x : eval
	./eval e4.bean

error5 : print #semantic error: array items not of same type
	./pp e5.bean

error5x : eval
	./eval e5.bean

arrays : print #works
	./pp arrays.bean

arraysx : eval #works
	./eval arrays.bean

conditionals : print #works
	./pp conditionals.bean

conditionalsx : eval #works
	./eval conditionals.bean

functions : print #works
	./pp function.bean

functionsx : eval #works
	./eval function.bean

recursion : print #works
	./pp recursion.bean

recursionx : eval #works
	./eval recursion.bean

iteration : print #works
	./pp iteration.bean

iterationx : eval #works
	./eval iteration.bean

lambda : print #works
	./pp lambda.bean

lambdax : eval #works
	./eval lambda.bean

problem : print #works
	./pp problem.bean

problemx : eval #works
	./eval problem.bean numbers.txt

run : eval

clean :
	rm -f $(OBJS)
