#Ben Bailey
#makefile for the pretty printer

OPTS = -Wall -Wextra
OBJS = types.o lexing.o recognize.o pretty.o print.o pp a.out print *.printed *.printed1

all : print

# pp :
# 	gcc $(OPTS) -c print.c pp.c recognize.c lexing.c types.c
# 	gcc $(OPTS) types.o lexing.o recognize.o pp.o print.o -o pp
print :
	gcc $(OPTS) -c print.c pretty.c recognize.c lexing.c types.c
	gcc $(OPTS) types.o lexing.o recognize.o pretty.o print.o -o pp

test1 : print
	@echo Original file:
	@cat test1.txt
	@echo Pretty Printed version of the original:
	@./pp test1.txt > test1.txt.printed
	@cat test1.txt.printed
	@echo Pretty Printed version of the Pretty Printed version:
	@./pp test1.txt.printed > test1.txt.printed1
	@cat test1.txt.printed1
	diff -s -q test1.txt.printed test1.txt.printed1

test2 : print
	@echo Original file:
	@cat test2.txt
	@echo Pretty Printed version of the original:
	@./pp test2.txt > test2.txt.printed
	@cat test2.txt.printed
	@echo Pretty Printed version of the Pretty Printed version:
	@./pp test2.txt.printed > test2.txt.printed1
	@cat test2.txt.printed1
	diff -s -q test2.txt.printed test2.txt.printed1

test3 : print
	@echo Original file:
	@cat test10.txt
	@echo Pretty Printed version of the original:
	@./pp test10.txt > test10.txt.printed
	@cat test10.txt.printed
	@echo Pretty Printed version of the Pretty Printed version:
	@./pp test10.txt.printed > test10.txt.printed1
	@cat test10.txt.printed1
	diff -s -q test10.txt.printed test10.txt.printed1

# test2 : print
# 	./pp test2.txt
#
# test3 : print
# 	./pp test3.txt

run : print
	./pp test1.txt
	./pp test2.txt

clean :
	rm -f $(OBJS)
