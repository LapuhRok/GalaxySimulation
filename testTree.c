#include <GLUT/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

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

// Declarations
void createTree(treeNode* rootNode);
void insertInTree(int i, treeNode* node);
void free_tree(treeNode* rootNode);
void print_tree(treeNode* rootNode, int level);
double *x,*y,*mass,*forceX,*forceY,*u,*v;
int N;


int main(int argc, char *argv[]) {
    
    N = 1;
    
    // Allocate memory for variables
    x = (double *)malloc(N*sizeof(double));
    y = (double *)malloc(N*sizeof(double));
    mass = (double *)malloc(N*sizeof(double));
    
    x[0] = 0.75;
    y[0] = 0.75;
    mass[0] = 1.0;
    
    treeNode* rootNode = (treeNode*)malloc(sizeof(treeNode));
    createTree(rootNode);
    print_tree(rootNode, 0);
    free_tree(rootNode);
    
    return 0;
}

void createTree(treeNode* rootNode)
{
    rootNode -> numberOfParticles = 0;
    rootNode -> downBorder = 0.0;
    rootNode -> upBorder = 1.0;
    rootNode -> leftBorder = 0.0;
    rootNode -> rightBorder = 1.0;
    rootNode -> NW = NULL;
    rootNode -> NE = NULL;
    rootNode -> SW = NULL;
    rootNode -> SE = NULL;
    
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
        printf("ELSE!\n");
    }
}

void free_tree(treeNode* rootNode) {
    if(rootNode->NW) free_tree(rootNode->NW);
    if(rootNode->NE) free_tree(rootNode->NE);
    if(rootNode->SW) free_tree(rootNode->SW);
    if(rootNode->SE) free_tree(rootNode->SE);
    free(rootNode);
}

void print_tree(treeNode* rootNode, int level) {
    int i;
    for(i = 0; i < level; i++) printf("   ");
    printf("x=%f y=%f m=%f\n", rootNode->centerX, rootNode->centerY, rootNode->nodeMass);
    if(rootNode->NW){
        printf("Subprinting!"); fflush(stdout);
        print_tree(rootNode->NW, level+1);
    }
    if(rootNode->NE){
        printf("Subprinting!");
        print_tree(rootNode->NE, level+1);
    }
    if(rootNode->SW){
        printf("Subprinting!");
        print_tree(rootNode->NW, level+1);
    }
    if(rootNode->SE){
        printf("Subprinting!");
        print_tree(rootNode->NE, level+1);
    }
}



























