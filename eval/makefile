#Ben Bailey
#makefile for the evaluator

OPTS = -Wall -Wextra
OBJS = types.o lexing.o recognize.o environment.o pretty.o eval.o print.o driver.o bean a.out print pp

all : bean

run : run

bean :
	gcc $(OPTS) -c driver.c eval.c recognize.c lexing.c environment.c pretty.c types.c
	gcc $(OPTS) types.o pretty.o environment.o lexing.o recognize.o eval.o driver.o -o bean

print :
	gcc $(OPTS) -c print.c pretty.c recognize.c environment.c lexing.c types.c
	gcc $(OPTS) types.o lexing.o environment.o recognize.o pretty.o print.o -o pp

error1 : print #syntax error: missing "!"
	@echo error1 contents:
	@cat e1.bean
	./pp e1.bean

error1x : eval
	./bean e1.bean

error2 : print #syntax error: unexpected character
	@echo error2 contents:
	@cat e2.bean
	./pp e2.bean

error2x : eval
	./bean e2.bean

error3 : print #syntax error: typed variable definition
	@echo error3 contents:
	@cat e3.bean
	./pp e3.bean

error3x : bean
	./bean e3.bean

error4 : print #semantic error: array access out of bounds
	./pp e4.bean

error4x : bean
	./bean e4.bean

error5 : print #semantic error: array items not of same type
	./pp e5.bean

error5x : bean
	./bean e5.bean

arrays : print #works
	./pp arrays.bean

arraysx : bean #works
	./bean arrays.bean

conditionals : print #works
	./pp conditionals.bean

conditionalsx : bean #works
	./bean conditionals.bean

functions : print #works
	./pp function.bean

functionsx : bean #works
	./bean function.bean

recursion : print #works
	./pp recursion.bean

recursionx : bean #works
	./bean recursion.bean

iteration : print #works
	./pp iteration.bean

iterationx : bean #works
	./bean iteration.bean

lambda : print #works
	./pp lambda.bean

lambdax : bean #works
	./bean lambda.bean

objects : print
	# @echo Objects are not implemented
	./pp oo.bean

objectsx : bean
	# @echo Objects are not implemented
	./bean oo.bean

problem : print #works
	./pp problem.bean

problemx : bean #works
	./bean problem.bean numbers.txt

clean :
	rm -f $(OBJS)
