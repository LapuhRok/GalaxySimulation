##
# Makefile for galsim

# The following flags work for OSX.
# For linux, you must instead link to the GLUT and OpenGL libraries

# Set Standard at C99 to enable for(int i= ...)
STFLAGS=-std=c99

#LDFLAGS=-framework GLUT -framework OpenGL
LDFLAGS=-lm -lglut -lGL

# Suppresses warnings about the deprecated GLUT routines.
CFLAGS=-Wno-deprecated-declarations
OPTFLAGS=-O3


all: galsim

galsim: galsim.o graphics.o
	gcc  $(STFLAGS) -o galsim galsim.o graphics.o $(LDFLAGS)

galsim.o: galsim.c
	gcc $(STFLAGS) $(OPTFLAGS) -c galsim.c $(CFLAGS)
	
graphics.o: graphics.c
	gcc $(STFLAGS) $(OPTFLAGS) -c graphics.c $(CFLAGS)	
	
clean:
	rm -f ./galsim *.o
