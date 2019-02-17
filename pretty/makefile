#Ben Bailey
#makefile for the pretty printer

OPTS = -Wall -Wextra
OBJS = types.o lexing.o recognize.o pp.o print.o pp

all : pp

pp :
	gcc $(OPTS) -c print.c pp.c recognize.c lexing.c types.c
	gcc $(OPTS) types.o lexing.o recognize.o pp.o print.o -o pp

clean :
	rm -f $(OBJS)
