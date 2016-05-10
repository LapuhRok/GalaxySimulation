##
# Makefile for bounce



# The following flags work for OSX.
#  For linux, you must instead link to the GLUT and OpenGL libraries
LDFLAGS=-framework GLUT -framework OpenGL
#LDFLAGS=-lm -lglut -lGL

# Suppresses warnings about the deprecated GLUT routines.
CFLAGS=-Wno-deprecated


all: bounce

bounce: bounce.o graphics.o
	gcc -o bounce bounce.o graphics.o $(LDFLAGS)

bounce.o: bounce.c
	gcc -c bounce.c $(CFLAGS)
	
graphics.o: graphics.c
	gcc -c graphics.c $(CFLAGS)	
	
clean:
	rm -f ./bounce *.o
