all: ithaiShell

ithaiShell: ithaiShell.o lex.yy.o
	gcc -o ithaiShell ithaiShell.o lex.yy.o -lfl

ithaiShell.o: ithaiShell.c
	gcc -Wall -g -c ithaiShell.c

lex.yy.o: lex.yy.c
	gcc -Wall -g -c lex.yy.c

lex.yy.c: lex.c
	flex lex.c

clean:
	rm -f *.o
	rm -f lex.yy.c
	rm -f ithaiShell
	