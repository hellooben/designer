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

run :
	scanner test1.txt
	scanner test4.txt

clean :
	rm -f $(OBJS)
