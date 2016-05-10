/*
 * File: bounce.c
 * --------------
 * An example code to demonstrate graphics routines
 *
 */

#include "rand.h"
#include "graphics.h"
#include <GLUT/glut.h>
// For Linux, you may need GL/glut.h instead:
//#include <GL/glut.h>
#include <math.h>

void Bounce(double *x, double *y, double *u, double *v);

double *x,*y,*mass,*forceX,*forceY,*u,*v;
float dt=1e-3,grav=10;

int N = 10;

// This function is called every time GLUT refreshes the display.
void display(void)
{
    int i;
    double ax, ay;
    for(i=0;i<N;i++) {
      ax=forceX[i]/mass[i];
      ay=forceY[i]/mass[i]-grav;

      u[i]+=ax*dt;
      v[i]+=ay*dt;
      x[i]+=u[i]*dt;
      y[i]+=v[i]*dt;

      Bounce(&x[i],&y[i],&u[i],&v[i]);
    }
    
    drawPoints(x,y,N);
       	    	
}



int main(int argc, char *argv[]) {    
   
  // Initialize the graphics routines
  graphicsInit(&argc, argv, display);
    

  int i;

  x = (double *)malloc(N*sizeof(double));
  y = (double *)malloc(N*sizeof(double));
  u = (double *)malloc(N*sizeof(double));
  v = (double *)malloc(N*sizeof(double));
  mass = (double *)malloc(N*sizeof(double));
  forceX = (double *)malloc(N*sizeof(double));
  forceY = (double *)malloc(N*sizeof(double));


  for(i=0;i<N;i++) {
    x[i]=frand(-1,1);
    y[i]=frand(-.75,.75);
    u[i]=frand(-1,1);
    v[i]=frand(-1,1);
    mass[i]=1;
    forceX[i]=0;
    forceY[i]=0;
  }
  
  glutMainLoop();
	
  return 0;
}

/*
 * Function: Bounce
 * Usage: Bounce(&x[i],&y[i],&u[i],&v[i]);
 * -------------------------------------------
 * If a particle moves beyond any of the boundaries then bounce it back
 *
 */
void Bounce(double *x, double *y, double *u, double *v) {
  double W = 1.0f, H = 1.0f;
  if(*x>W) {
    *x=2*W-*x;
    *u=-*u;
  }

  if(*x<0) {
    *x=-*x;
    *u=-*u;
  }

  if(*y>H) {
    *y=2*H-*y;
    *v=-*v;
  }

  if(*y<0) {
    *y=-*y;
    *v=-*v;
  }
}


  
  
