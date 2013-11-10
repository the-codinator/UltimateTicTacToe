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
    int i,j;
    system("clear");
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
            printf("%c",board[i][j]);
        printf("\n");
    }
    printf("%d %d",x,y);
}

void output2file(char**** board, int x, int y) {
    FILE* fp = fopen("TEMP", "w");
    int i,j,k,l;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            for(k=0;k<3;k++)
            {
                for(l=0;l<3;l++)
                    fprintf(fp,"%c",board[i][k][j][l]);
            }
            fprintf(fp, "\n");
        }
    }
    fprintf(fp, "%d %d\n",x,y);
    remove(SOURCE);
    rename("TEMP", SOURCE);
    fclose(fp);
}

int check3x3(char board[3][3]) {
    int i, row, col;
    
    // All horizontal and vertical lines
    for (i=0; i<3; i++) {
        row = board[i][0]+board[i][1]+board[i][2];
        col = board[0][i]+board[1][i]+board[2][i];
        if (row == 3*'X' || col == 3*'X')
            return 1;
        else if (row == 3*'O' || col == 3*'O')
            return 2;
    }
    
    // Both diagonals
    if ((board[1][1]==board[0][0] && board[1][1] == board[2][2]) || 
        (board[1][1]==board[2][0] && board[1][1] == board[0][2]))
    {
        if (board[1][1] == 'X')
            return 1;
        else if (board[1][1] == 'O')
            return 2;
        else return -1;     // Diagonals consist of a line of 3 blank spaces
    }
    
    for (row=0; row<3; row++)
        for (col=0; col<3; col++)
            if (board[row][col] == '.')
                return -1;  // Incomplete board
    
    return 0;
}
