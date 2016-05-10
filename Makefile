##
# Makefile for bounce, galaxy simulation

CFLAGS=-g
INCLUDES=-I/opt/X11/include
LDFLAGS=-L/opt/X11/lib -lX11 -lm

bounce: bounce.o graphics.o
	gcc -o bounce bounce.o graphics.o $(LDFLAGS)

bounce.o: bounce.c graphics.o rand.h
	gcc -c bounce.c $(INCLUDES)

graphics.o: graphics.c
	gcc -c graphics.c $(INCLUDES)

clean:
	rm -f ./bounce *.o 
