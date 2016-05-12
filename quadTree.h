#ifndef quadTree_h
#define quadTree_h

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
    int id;
};
typedef struct treeNode_ treeNode;



// Declarations
void createTree();
void insertInTree(int i, treeNode* node);
void free_tree(treeNode* node);
void print_tree(treeNode* node, int level);
void getCenterOfMass(treeNode* node);
double *x,*y,*mass,*forceX,*forceY,*u,*v;
int N;
treeNode* rootNode;



#endif
