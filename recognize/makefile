#Ben Bailey
#makefile for the recognizer

OPTS = -Wall -Wextra
OBJS = types.o lexing.o recognize.o parser.o recognizer

all : recognizer

recognizer :
	gcc $(OPTS) -c parser.c recognize.c lexing.c types.c
	gcc $(OPTS) types.o lexing.o recognize.o parser.o -o recognizer

test1 :
	gcc $(OPTS) -c parser.c recognize.c lexing.c types.c
	gcc $(OPTS) types.o lexing.o recognize.o parser.o -o recognizer
	./recognizer test1.txt
#
test2 :
	gcc $(OPTS) -c parser.c recognize.c lexing.c types.c
	gcc $(OPTS) types.o lexing.o recognize.o parser.o -o recognizer
	./recognizer test2.txt
#
test3 :
	gcc $(OPTS) -c parser.c recognize.c lexing.c types.c
	gcc $(OPTS) types.o lexing.o recognize.o parser.o -o recognizer
	./recognizer test3.txt

test4 :
	gcc $(OPTS) -c parser.c recognize.c lexing.c types.c
	gcc $(OPTS) types.o lexing.o recognize.o parser.o -o recognizer
	./recognizer test4.txt

test5 :
	gcc $(OPTS) -c parser.c recognize.c lexing.c types.c
	gcc $(OPTS) types.o lexing.o recognize.o parser.o -o recognizer
	./recognizer test5.txt

test6 :
	gcc $(OPTS) -c parser.c recognize.c lexing.c types.c
	gcc $(OPTS) types.o lexing.o recognize.o parser.o -o recognizer
	./recognizer test6.txt

run :
	./recognizer test2.txt
	./recognizer test4.txt
	./recognizer test6.txt


clean :
	rm -f $(OBJS)
