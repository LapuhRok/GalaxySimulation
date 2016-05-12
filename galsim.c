// galsim.c
// High Perfomrance Computing - Assignment
// Rok Lapuh

#include "graphics.h"
#include "file_operations.c"
#include <GLUT/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

// For Linux, you may need GL/glut.h instead:
//#include <GL/glut.h>

// Declarations of functions
void Bounce(double *x, double *y, double *u, double *v);
void updateForce();
void createTree();
void insertInTree(int i, treeNode* node);

// Constant parameters
int N;
int nsteps;
double delta_t;
double theta_max;
double G;
double e0 = 1e-3;

// Iterations counter
int iter = 0;

// Data
double *p;
double *x,*y,*mass,*forceX,*forceY,*u,*v;

// Timers
double totalRunTime = 0;    // time of running the program
double totalCodeTime = 0;   // time of running my code
double startRunTime;
double startCodeTime;
double endTime;

// Timing function
static double get_wall_seconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
    return seconds;
}

// Tree structure
struct treeNode_ {
    double centerX;
    double centerY;
    double nodeMass;
    int numberOfParticles;
    double leftBorder;
    double rightBorder;
    double upBorder;
    double downBorder;
    struct treeNode_* NW;
    struct treeNode_* NE;
    struct treeNode_* SW;
    struct treeNode_* SE;

};
typedef struct treeNode_ treeNode;

// This function is called every time GLUT refreshes the display.
void display(void)
{
    startCodeTime = get_wall_seconds();
    
    // Update force
    updateForce();
    
    // Update positions
    double ax, ay;
    for(int i = 0; i < N; i++) {
        
        ax=forceX[i]/mass[i];
        ay=forceY[i]/mass[i];
        
        u[i] += ax*delta_t;
        v[i] += ay*delta_t;
        x[i] += u[i]*delta_t;
        y[i] += v[i]*delta_t;
        
        // Uncomment to force points to stay in bounds
        // Bounce(&x[i],&y[i],&u[i],&v[i]);
    }
    
    // Write to file
    iter++;
    if (iter == nsteps) {
        endTime = get_wall_seconds();
        totalRunTime =  endTime - startRunTime;
        totalCodeTime +=  endTime - startCodeTime;
        printf("Total running time: %f\n", totalRunTime);
        printf("Running time: %f\n", totalCodeTime);
        
        // Put everything together
        for (int i = 0; i < N; i++) {
            p[5*i + 0] = mass[i];
            p[5*i + 1] = x[i];
            p[5*i + 2] = y[i];
            p[5*i + 3] = u[i];
            p[5*i + 4] = v[i];
        }
        write_doubles_to_file(5*N, p, "results.gal");
        printf("Done!\n");
    }
    
    totalCodeTime +=  get_wall_seconds() - startCodeTime;
    
    // Display
    if (iter % 100 == 0) {
        drawPoints(x,y,N);
    }
    
}



int main(int argc, char *argv[]) {
    
    startRunTime = get_wall_seconds();
    
    // Check input parameters
    if (argc != 6) {
        printf("Input Error!\nRun: $ ./galsim N filename nsteps delta_t theta_max\n");
        return -1;
    }
    
    // Read input parameters
    sscanf(argv[1],"%d",&N);
    sscanf(argv[3],"%d",&nsteps);
    sscanf(argv[4],"%lf",&delta_t);
    sscanf(argv[5],"%lf",&theta_max);
    
    // Calculate gravitational constant
    G = 100/N;
    
    // Initialize the graphics routines
    graphicsInit(&argc, argv, display);
    
    // Allocate memory for variables
    p = (double *)malloc(5*N*sizeof(double));
    x = (double *)malloc(N*sizeof(double));
    y = (double *)malloc(N*sizeof(double));
    u = (double *)malloc(N*sizeof(double));
    v = (double *)malloc(N*sizeof(double));
    mass = (double *)malloc(N*sizeof(double));
    forceX = (double *)malloc(N*sizeof(double));
    forceY = (double *)malloc(N*sizeof(double));
    
    // Read input file
    int flag = read_doubles_from_file(5*N, p, argv[2]);
    if (flag != 0){
        printf("Error reading data from file.\n"); fflush(stdout);
        return -1;
    }
    
    // Separate initial conditions
    for (int i = 0; i < N; i++) {
        mass[i] = p[5*i + 0];
        x[i] = p[5*i + 1];
        y[i] = p[5*i + 2];
        u[i] = p[5*i + 3];
        v[i] = p[5*i + 4];
    }
    
    // Run
    glutMainLoop();
    
    return 0;
}

void Bounce(double *x, double *y, double *u, double *v)
{
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

void updateForce()
{
//    double sumX;
//    double sumY;
//    double xi;
//    double yi;
//    double xj, yj, rx, ry, r, rr;
//    for(int i = 0; i < N; i++) {
//        sumX = 0;
//        sumY = 0;
//        xi = x[i];
//        yi = y[i];
//        for (int j = 0; j < N; j++) {
//            if (i == j) continue;
//            xj = x[j];
//            yj = y[j];
//            rx = xi - xj;
//            ry = yi - yj;
//            r = sqrt(rx*rx + ry*ry);
//            rr = r + e0;
//            sumX += mass[j]*rx/(rr*rr*rr);
//            sumY += mass[j]*ry/(rr*rr*rr);
//        }
//        forceX[i] = -G*mass[i]*sumX;
//        forceY[i] = -G*mass[i]*sumY;
//    }
}

void createTree()
{
    if (rootNode) free_tree(rootNode);
    
    treeNode* rootNode = (treeNode*)malloc(sizeof(treeNode));
    rootNode -> numberOfParticles = 0;
    rootNode -> downBorder = 0.0;
    rootNode -> upBorder = 1.0;
    rootNode -> leftBorder = 0.0;
    rootNode -> rightBorder = 1.0;
    
    for (int i = 0; i < N; i++) {
        insertInTree(i, rootNode);
    }
    
    
}

void insertInTree(int i, treeNode* node)
{
    node -> numberOfParticles++;
    if (node -> numberOfParticles == 1) {
        node -> centerX = x[i];
        node -> centerY = y[i];
        node -> nodeMass = mass[i];
    }
    else {
        printf("ELSE!");
    }
}

void free_tree(treeNode* rootNode) {
    if(rootNode->NW)
        free_tree(rootNode->NW);
    if(rootNode->NE)
        free_tree(rootNode->NE);
    if(rootNode->SW)
        free_tree(rootNode->SW);
    if(rootNode->SE)
        free_tree(rootNode->SE);
    free(rootNode);
}



