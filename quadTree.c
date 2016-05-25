#include "quadTree.h"


//int main(int argc, char *argv[]) {
//    
//    N = 4;
//    
//    // Allocate memory for variables
//    x = (double *)malloc(N*sizeof(double));
//    y = (double *)malloc(N*sizeof(double));
//    mass = (double *)malloc(N*sizeof(double));
//    
//    x[0] = 0.5;
//    y[0] = 0.5;
//    mass[0] = 1.0;
//    x[1] = 0.5;
//    y[1] = 0.8;
//    mass[1] = 1.0;
//    x[2] = 0.5;
//    y[2] = 0.35;
//    mass[2] = 2.0;
//    x[3] = 0.5;
//    y[3] = 0.575;
//    mass[3] = 2.0;
//    
//    rootNode = (treeNode*)malloc(sizeof(treeNode));
//    createTree();
//    getCenterOfMass(rootNode);
//    print_tree(rootNode, 0);
//    free_tree(rootNode);
//    
//    return 0;
//}

void createTree(const int N)
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
    rootNode -> id = -1;
    
    for (int i = 0; i < N; i++) {
        insertInTree(i, rootNode);
    }
}

void insertInTree(int i, treeNode* node)
{
    // Filter out particles outside the box
    if (x[i] < 0 || x[i] > 1 || y[i] < 0 || y[i] > 1) {
        return;
    }
    
    
    if (node == rootNode) rootNode -> numberOfParticles++;
    
    // create children if they do not exist
    if (!node -> SW) {
        node -> id = -1; // set id of nodes without children to -1
        double midX = (node->leftBorder + node->rightBorder)/2;
        double midY = (node->downBorder + node->upBorder)/2;
        // NW
        node -> NW = (treeNode*)malloc(sizeof(treeNode));
        node -> NW -> numberOfParticles = 0;
        node -> NW -> downBorder = midY;
        node -> NW -> upBorder = node->upBorder;
        node -> NW -> leftBorder = node->leftBorder;
        node -> NW -> rightBorder = midX;
        node -> NW -> NW = NULL;
        node -> NW -> NE = NULL;
        node -> NW -> SW = NULL;
        node -> NW -> SE = NULL;
        node -> NW -> id = -1;
        // SW
        node -> SW = (treeNode*)malloc(sizeof(treeNode));
        node -> SW -> numberOfParticles = 0;
        node -> SW -> downBorder = node->downBorder;
        node -> SW -> upBorder = midY;
        node -> SW -> leftBorder = node->leftBorder;
        node -> SW -> rightBorder = midX;
        node -> SW -> NW = NULL;
        node -> SW -> NE = NULL;
        node -> SW -> SW = NULL;
        node -> SW -> SE = NULL;
        node -> SW -> id = -1;
        // NE
        node -> NE = (treeNode*)malloc(sizeof(treeNode));
        node -> NE -> numberOfParticles = 0;
        node -> NE -> downBorder = midY;
        node -> NE -> upBorder = node->upBorder;
        node -> NE -> leftBorder = midX;
        node -> NE -> rightBorder = node->rightBorder;
        node -> NE -> NW = NULL;
        node -> NE -> NE = NULL;
        node -> NE -> SW = NULL;
        node -> NE -> SE = NULL;
        node -> NE -> id = -1;
        // SE
        node -> SE = (treeNode*)malloc(sizeof(treeNode));
        node -> SE-> numberOfParticles = 0;
        node -> SE -> downBorder = node->downBorder;
        node -> SE -> upBorder = midY;
        node -> SE -> leftBorder = midX;
        node -> SE -> rightBorder = node->rightBorder;
        node -> SE -> NW = NULL;
        node -> SE -> NE = NULL;
        node -> SE -> SW = NULL;
        node -> SE -> SE = NULL;
        node -> SE -> id = -1;
    }
    
    // Particle on the WEST
    if (x[i] < (node->leftBorder + node->rightBorder)/2) {
        // Particle on the SOUTH
        if (y[i] < (node->downBorder + node->upBorder)/2) {
            if (node -> SW -> numberOfParticles == 0) {
                node -> SW -> id = i;
                node -> SW -> numberOfParticles++;
            } else if (node -> SW -> numberOfParticles == 1) {
                node -> SW -> numberOfParticles++;
                insertInTree(node->SW->id, node->SW);
                insertInTree(i, node->SW);
            } else {
                insertInTree(i, node->SW);
            }
        // Particle on the NORTH
        } else {
            if (node -> NW -> numberOfParticles == 0) {
                node -> NW -> id = i;
                node -> NW -> numberOfParticles++;
            } else if (node -> NW -> numberOfParticles == 1) {
                node -> NW -> numberOfParticles++;
                insertInTree(node->NW->id, node->NW);
                insertInTree(i, node->NW);
            } else {
                insertInTree(i, node->NW);
            }
        }
    }
    // Particle on the EAST
    else {
        // Particle on the SOUTH
        if (y[i] < (node->downBorder + node->upBorder)/2) {
            if (node -> SE -> numberOfParticles == 0) {
                node -> SE -> id = i;
                node -> SE -> numberOfParticles++;
            } else if (node -> SE -> numberOfParticles == 1) {
                node -> SE -> numberOfParticles++;
                insertInTree(node->SE->id, node->SE);
                insertInTree(i, node->SE);
            } else {
                insertInTree(i, node->SE);
            }
        }
        // Particle on the NORTH
        else {
            if (node -> NE -> numberOfParticles == 0) {
                node -> NE -> id = i;
                node -> NE -> numberOfParticles++;
            } else if (node -> NE -> numberOfParticles == 1) {
                node -> NE -> numberOfParticles++;
                insertInTree(node->NE->id, node->NE);
                insertInTree(i, node->NE);
            } else {
                insertInTree(i, node->NE);
            }
        }
    }
}

void free_tree(treeNode* node) {
    if(node->NW) free_tree(node->NW);
    if(node->NE) free_tree(node->NE);
    if(node->SW) free_tree(node->SW);
    if(node->SE) free_tree(node->SE);
    free(node);
}

void print_tree(treeNode* node, int level) {
    for(int i = 0; i < level; i++) printf("   ");
    printf("x=%f y=%f m=%f id=%d #=%d\n", node->centerX, node->centerY, node->nodeMass, node->id, node->numberOfParticles);
    
    if(node->NW){
        print_tree(node->NW, level+1);
    }
    if(node->NE){
        print_tree(node->NE, level+1);
    }
    if(node->SW){
        print_tree(node->SW, level+1);
    }
    if(node->SE){
        print_tree(node->SE, level+1);
    }
}

void getCenterOfMass(treeNode* node)
{
    if (!node->NE) {
        if (node -> numberOfParticles == 0) {
            node -> nodeMass = 0;
            node -> centerX = 0;
            node -> centerY = 0;
        } else {
            node -> nodeMass = mass[node->id];
            node -> centerX = x[node->id];
            node -> centerY = y[node->id];
        }
    } else {
        getCenterOfMass(node -> NW);
        getCenterOfMass(node -> NE);
        getCenterOfMass(node -> SW);
        getCenterOfMass(node -> SE);
        
        node -> nodeMass =  node->NW->nodeMass +
                            node->NE->nodeMass +
                            node->SW->nodeMass +
                            node->SE->nodeMass;
        
        node -> centerX =   node->NW->nodeMass * node->NW->centerX +
                            node->NE->nodeMass * node->NE->centerX +
                            node->SW->nodeMass * node->SW->centerX +
                            node->SE->nodeMass * node->SE->centerX;
        node -> centerX = node->centerX / node->nodeMass;
        
        
        node -> centerY =   node->NW->nodeMass * node->NW->centerY +
                            node->NE->nodeMass * node->NE->centerY +
                            node->SW->nodeMass * node->SW->centerY +
                            node->SE->nodeMass * node->SE->centerY;
        node -> centerY = node->centerY / node->nodeMass;
    }
}



























