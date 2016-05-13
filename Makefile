##
# Makefile for galsim

# The following flags work for OSX.
# For linux, you must instead link to the GLUT and OpenGL libraries

LDFLAGS=-framework GLUT -framework OpenGL
#LDFLAGS=-lm -lglut -lGL

# Suppresses warnings about the deprecated GLUT routines.
CFLAGS=-Wno-deprecated-declarations
OPTFLAGS=-O0
DEBUGFLAGS=


all: galsim

galsim: galsim.o graphics.o
	gcc $(DEBUGFLAGS) -o galsim galsim.o graphics.o $(LDFLAGS)

galsim.o: galsim.c
	gcc $(DEBUGFLAGS) $(OPTFLAGS) -c galsim.c $(CFLAGS)
	
graphics.o: graphics.c
	gcc $(DEBUGFLAGS) $(OPTFLAGS) -c graphics.c $(CFLAGS)	
	
clean:
	rm -f ./galsim *.o
