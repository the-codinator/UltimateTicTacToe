#include <stdio.h>
#include <stdlib.h>
#include "gameio.h"

char** input2D(int* x, int* y) {
    FILE* fp = fopen(SOURCE, "r");
    int i,j;
    char** mat = (char**) malloc(9*sizeof(char*));
    for (i=0; i<9; i++) {
        mat[i] = (char*) malloc(9*sizeof(char));
        for (j=0; j<9; j++)
            mat[i][j] = fgetc(fp);
        fgetc(fp);
    }
    fscanf(fp, "%d %d", x, y);
    fclose(fp);
    return mat;
}

char**** input4D(int* x, int* y) {
    char** mat2 = input2D(x, y);
    char**** mat4 = mat2Dto4D(mat2);
    free(mat2);
    return mat4;
}

char**** mat2Dto4D(char** mat2) {
    char**** mat4 = (char****) malloc(3*sizeof(char***));
    int i,j,k,l;
    for (i=0; i<3; i++) {
        mat4[i] = (char***) malloc(3*sizeof(char**));
        for (j=0; j<3; j++) {
            mat4[i][j] = (char**) malloc(3*sizeof(char*));
            for (k=0; k<3; k++) {
                mat4[i][j][k] = (char*) malloc(3*sizeof(char));
                for (l=0; l<3; l++) {
                    mat4[i][j][k][l] = mat2[3*i + k][3*j + l];
                }
            }
        }
    }
    return mat4;
}

void output2user(char** board, int x, int y) {
    
}

void output2file(char**** board, int x, int y) {
    
}
