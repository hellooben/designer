#Ben Bailey
#makefile for lexical analysis

OPTS = -Wall -Wextra
OBJS = types.o lexing.o environment.o env-test.o environment

all : environment

environment :
	gcc $(OPTS) -c env-test.c environment.c lexing.c types.c
	gcc $(OPTS) types.o lexing.o environment.o env-test.o -o environment

clean :
	rm -f $(OBJS)
