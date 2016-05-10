/*
 * File: bounce.c
 * --------------
 * Contains a sample of how to use the graphics routines.
 *
 * CME212 Assignment 5
 * Oliver Fringer
 * Stanford University
 *
 */

#include "rand.h"
#include "graphics.h"
#include "math.h"

void Bounce(double *x, double *y, double *u, double *v, double L, double W);

const double circleRadius=0.025, circleColor=0;
const int windowWidth=800;

int main(int argc, char *argv[]) {
  int i, N=10;
  float L=1,W=1,dt=1e-3,grav=10;
  double *x,*y,*mass,*forceX,*forceY,*u,*v,ax,ay;

  x = (double *)malloc(N*sizeof(double));
  y = (double *)malloc(N*sizeof(double));
  u = (double *)malloc(N*sizeof(double));
  v = (double *)malloc(N*sizeof(double));
  mass = (double *)malloc(N*sizeof(double));
  forceX = (double *)malloc(N*sizeof(double));
  forceY = (double *)malloc(N*sizeof(double));


  for(i=0;i<N;i++) {
    x[i]=frand(0,1);
    y[i]=frand(.25,.75);
    u[i]=frand(-1,1);
    v[i]=frand(-1,1);
    mass[i]=1;
    forceX[i]=0;
    forceY[i]=0;
  }
  InitializeGraphics(argv[0],windowWidth,windowWidth);
  SetCAxes(0,1);

  printf("Hit q to quit.\n");
  while(!CheckForQuit()) {
    for(i=0;i<N;i++) {
      ax=forceX[i]/mass[i];
      ay=forceY[i]/mass[i]-grav;

      u[i]+=ax*dt;
      v[i]+=ay*dt;
      x[i]+=u[i]*dt;
      y[i]+=v[i]*dt;

      Bounce(&x[i],&y[i],&u[i],&v[i],L,W);
    }

    ClearScreen();  
    for(i=0;i<N;i++)
      DrawCircle(x[i],y[i],L,W,circleRadius,circleColor);
    Refresh();

    // Sleep a short while to avoid screen flickering
    usleep(3000);
  }
  FlushDisplay();
  CloseDisplay();
  return 0;
}

/*
 * Function: Bounce
 * Usage: Bounce(&x[i],&y[i],&u[i],&v[i],L,W);
 * -------------------------------------------
 * If a particle moves beyond any of the boundaries then set
 * it on the other side of the boundary back in the domain and
 * reverse the velocities.
 *
 */
void Bounce(double *x, double *y, double *u, double *v, double L, double W) {
  if(*x>L) {
    *x=2*L-*x;
    *u=-*u;
  }

  if(*x<0) {
    *x=-*x;
    *u=-*u;
  }

  if(*y>W) {
    *y=2*W-*y;
    *v=-*v;
  }

  if(*y<0) {
    *y=-*y;
    *v=-*v;
  }
}



  
  
