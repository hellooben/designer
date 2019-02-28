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
	./pp e1.txt

error1x : eval
	./eval e1.txt

error2 : print #syntax error: unexpected character
	./pp e2.txt

error2x : eval
	./eval e2.txt

error3 : print #syntax error: typed variable definition
	./pp e3.txt

error3x : eval
	./eval e3.txt

error4 : print #semantic error: array access out of bounds
	./pp e4.txt

error4x : eval
	./eval e4.txt

error5 : print #semantic error: array items not of same type
	./pp e5.txt

error5x : eval
	./eval e5.txt

arrays : print #works
	./pp arrays.txt

arraysx : eval #works
	./eval arrays.txt

conditionals : print #works
	./pp conditionals.txt

conditionalsx : eval #works
	./eval conditionals.txt

functions : print #works
	./pp function.txt

functionsx : eval #works
	./eval function.txt

iteration : print #works
	./pp iteration.txt

iterationx : eval #works 
	./eval iteration.txt

lambda : print #works
	./pp lambda.txt

lambdax : eval #works
	./eval lambda.txt
#
# test1 : print
# 	@echo Original file:
# 	@cat test1.txt
# 	@echo Pretty Printed version of the original:
# 	@./pp test1.txt > test1.txt.printed
# 	@cat test1.txt.printed
# 	@echo Pretty Printed version of the Pretty Printed version:
# 	@./pp test1.txt.printed > test1.txt.printed1
# 	@cat test1.txt.printed1
# 	diff -s -q test1.txt.printed test1.txt.printed1
#
# test2 : print
# 	@echo Original file:
# 	@cat test2.txt
# 	@echo Pretty Printed version of the original:
# 	@./pp test2.txt > test2.txt.printed
# 	@cat test2.txt.printed
# 	@echo Pretty Printed version of the Pretty Printed version:
# 	@./pp test2.txt.printed > test2.txt.printed1
# 	@cat test2.txt.printed1
# 	diff -s -q test2.txt.printed test2.txt.printed1
#
# test3 : print
# 	@echo Original file:
# 	@cat test3.txt
# 	@echo Pretty Printed version of the original:
# 	@./pp test3.txt > test3.txt.printed
# 	@cat test3.txt.printed
# 	@echo Pretty Printed version of the Pretty Printed version:
# 	@./pp test3.txt.printed > test3.txt.printed1
# 	@cat test3.txt.printed1
# 	diff -s -q test3.txt.printed test3.txt.printed1

# test2 : print
# 	./pp test2.txt
#
# test3 : print
# 	./pp test3.txt

run : eval

clean :
	rm -f $(OBJS)
