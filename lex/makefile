#Ben Bailey
#makefile for lexical analysis

OPTS = -Wall -Wextra
OBJS = types.o lexing.o scanner.o scanner

all : scanner

scanner :
	gcc $(OPTS) -c scanner.c lexing.c types.c
	gcc $(OPTS) types.o lexing.o scanner.o -o scanner

test1 :
	gcc $(OPTS) -c scanner.c lexing.c types.c
	gcc $(OPTS) types.o lexing.o scanner.o -o scanner
	./scanner test1.txt

test2 :
	gcc $(OPTS) -c scanner.c lexing.c types.c
	gcc $(OPTS) types.o lexing.o scanner.o -o scanner
	./scanner test2.txt

test3 :
	gcc $(OPTS) -c scanner.c lexing.c types.c
	gcc $(OPTS) types.o lexing.o scanner.o -o scanner
	./scanner test3.txt

test4 :
	gcc $(OPTS) -c scanner.c lexing.c types.c
	gcc $(OPTS) types.o lexing.o scanner.o -o scanner
	./scanner test4.txt

test5 :
	gcc $(OPTS) -c scanner.c lexing.c types.c
	gcc $(OPTS) types.o lexing.o scanner.o -o scanner
	./scanner test5.txt

run :
	scanner test1.txt
	scanner test4.txt

clean :
	rm -f $(OBJS)
