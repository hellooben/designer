#Ben Bailey
#makefile for the evaluator

OPTS = -Wall -Wextra
OBJS = types.o lexing.o recognize.o environment.o pretty.o eval.o print.o driver.o eval a.out

all : eval

eval :
	gcc $(OPTS) -c driver.c eval.c recognize.c lexing.c environment.c pretty.c types.c
	gcc $(OPTS) types.o pretty.o environment.o lexing.o recognize.o eval.o driver.o -o eval

# pp :
# 	gcc $(OPTS) -c print.c pp.c recognize.c lexing.c types.c
# 	gcc $(OPTS) types.o lexing.o recognize.o pp.o print.o -o pp
# print :
# 	gcc $(OPTS) -c print.c pretty.c recognize.c lexing.c types.c
# 	gcc $(OPTS) types.o lexing.o recognize.o pretty.o print.o -o pp
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
