#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "file_operations.c"

int main(int argc, char *argv[]) {
    
    // Check input parameters
    if (argc != 4) {
        printf("Input Error!\nRun: $ ./compare N filename1 filename2\n");
        return -1;
    }
    
    // Read input parameters
    int N;
    sscanf(argv[1],"%d",&N);
    
    // Allocate memory for variables
    double *p1 = (double *)malloc(5*N*sizeof(double));
    double *p2 = (double *)malloc(5*N*sizeof(double));
    double *x1 = (double *)malloc(N*sizeof(double));
    double *x2 = (double *)malloc(N*sizeof(double));
    double *y1 = (double *)malloc(N*sizeof(double));
    double *y2 = (double *)malloc(N*sizeof(double));
    
    // Read input file
    int flag = read_doubles_from_file(5*N, p1, argv[2]);
    if (flag != 0){
        printf("Error reading data from file.\n"); fflush(stdout);
        return -1;
    }
    
    flag = read_doubles_from_file(5*N, p2, argv[3]);
    if (flag != 0){
        printf("Error reading data from file.\n"); fflush(stdout);
        return -1;
    }
    
    // Separate initial conditions
    for (int i = 0; i < N; i++) {
        x1[i] = p1[5*i + 1];
        y1[i] = p1[5*i + 2];
        x2[i] = p2[5*i + 1];
        y2[i] = p2[5*i + 2];
    }
    
    double sum = 0;
    for (int i = 0; i < N; i++) {
        sum += (x1[i] - x2[i])*(x1[i] - x2[i]) + (y1[i] - y2[i])*(y1[i] - y2[i]);
    }
    double diff = sqrt(sum)/N;
    
    printf("Difference: %e\n", diff);
    
    return 0;
}
