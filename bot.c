#include <math.h>
#include "gameio.h"

int main() {
    // Initialization
    int x, y;
    char**** board = input4D(&x, &y);
    int i, j, k, l;
    char bigBoard[3][3];
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            k=check3x3(board[i][j]);
            if (k == 2)
                bigBoard[i][j] = 'O';
            else if (k == 1)
                bigBoard[i][j] = 'X';
            else bigBoard[i][j] = '.';
        }
    }
    
    if (x!=-1 && y!=-1 && bigBoard[x][y]!='.')
        x=y=-1;
    
    // Analysis
    
    //TODO: A lot of things here
    
    
    // Output
    k=check3x3(board[x][y]);
    if (k == 2) {
        bigBoard[x][y] = 'O';
        x=y=-1;
    }
    else if (k == 1) {
        bigBoard[x][y] = 'X';
        x=y=-1;
    }
    else bigBoard[x][y] = '.';
    
    return 0;
}
