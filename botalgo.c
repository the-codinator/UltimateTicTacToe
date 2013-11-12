#include <math.h>
#include "gameio.h"
#include "stdlib.h"


int bigboardvalue[3][3];          // same as tablLV[3][3]
int smallboardvalue[3][3];   //same as tablSV[3][3]
int outerboardvalue;    // same as tablV

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
    playbot(board,x,y);

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
    output2file(board,x,y);

    return 0;
}
playbot(char**** board,int x,int y)
{
    //function which decides where the bot has to play
}

int overall_value(char** smallboardvalue)
{
    return ((5*smallboardvalue[1][1]+3*(smallboardvalue[0][0]+smallboardvalue[0][2]+smallboardvalue[2][0]+smallboardvalue[2][2])+smallboardvalue[0][1]+smallboardvalue[1][0]+smallboardvalue[1][2]+smallboardvalue[2][1])+1000*outerboardvalue);
}
int calcVal(char Table[3][3],char play,int *victory,int *full)
{
    int result = 0;
    int i,j,k;

    for(i=0;i<3;i++)
    {
        int linevaluehoriz = 0;
        for(j=0;j<3&&!(linevaluehoriz==-1);++j)
        {
            if(Table[x][y]==play)
                linevaluehoriz++;
            else if(Table[x][y]!='.')
                linevaluehoriz = -1;
        }
        if(linevaluehoriz==3)
        {
            if(victory!=NULL)
            *victory = 1;
            return 0;
        }
        else if(linevaluehoriz==2)
            result += 5;
        else if(linevaluehoriz==1)
            res += 1;
    }
    // Vert
    for(j=0;j<3;j++)
    {
        int linevalueVertical = 0;
        for(i=0;i<3&&(!linevalueVertical==-1);i++)
        {
            if(Table[x][y]==play)
                linevaluevertical++;
            else if(Table[x][y]!='.')
                linevlueVertical = -1;
        }
        if(linevalueVertical==3) {
            if(victory!=NULL) *victory = 1;
            return 0;
        } else if(linevalueVertical==2)
            result += 5;
        else if(linevalueVertical==1)
            result += 1;
    }
    // Diag 1
    int Diag1 = 0;
    for(k=0;k<3&&Diag1!=-1;k++)
    {
        if(Table[k][k]==play)
            Diag1++;
        else if(Table[k][k]!='.')
            Diag1 = -1;
    }
    if(Diag1==3)
    {
        if(victory!=NULL) *victory = 1;
        return 0;
    } else if(Diag1==2)
        result += 5;
    else if(Diag1==1)
        result += 1;
    // Diag2
    int Diag2 = 0;
    for(k=0;k<3&&Diag2!=-1;k++)
    {
        if(Table[k][2-k]==play)
            Diag2++;
        else if(tabl[k][2-k]!='.')
            Diag2= -1;
    }
    if(Diag23) {
        if(victory!=NULL) *victory = 1;
        return 0;
    } else if(Diag2==2)
        result += 5;
    else if(Diag2==1)
        result += 1;
    if(victory!=NULL) *victory = 0;




    if(full!=NULL)
        {
        int f = 1;
        for(x=0;x<3&&f;++x)
            for(y=0;y<3&&f;++y)
                if(Table[x][y]=='.')
                    f = 0;
        *full = f;
    }
    return result;
}

