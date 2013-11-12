
#include <math.h>
#include <malloc.h>
#include "gameio.h"
int playorder[9][2]= {{1,1},{0,0},{2,2},{2,0},{0,2},{1,0},{0,1},{2,1},{1,2}};
void playbot(char**** board,int *x,int *y);
// Who has to play
char player(char**** board) {
    int i, j, k, l;
    int x=0;
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            for (k=0; k<3; k++) {
                for (l=0; l<3; l++) {
                    if (board[i][j][k][l] == 'X') x++;
                    else if (board[i][j][k][l] == 'O') x--;
                }
            }
        }
    }
    if (x) return 'O';
    else return 'X';
}

int main() {
    // Initialization
    int x, y;
    char**** board = input4D(&x, &y);
    int i, j, k, l;
    int play;       // play has the square in which the last move was made (values = 0 to 80)
    char turn = player(board);
    char** bigBoard = (char**) malloc(3*sizeof(char*));
    for (i=0; i<3; i++) {
        bigBoard[i] = (char*) malloc(3*sizeof(char));
        for (j=0; j<3; j++) {
            k=check3x3(board[i][j]);
            if (k == 2)
                bigBoard[i][j] = 'O';
            else if (k == 1)
                bigBoard[i][j] = 'X';
            else if (k == 0) bigBoard[i][j] = 'D';
            else bigBoard[i][j] = '.';
        }
    }

    if (x!=-1 && y!=-1 && bigBoard[x][y]!='.')
        x=y=-1;
    playbot(board,&x,&y);
    // Analysis

    //TODO: A lot of things here


    // Output
    output2file(board,x,y);
    return 3*x+y;
}
void playbot(char**** board,int *x,int *y)
{
    int player=player(board);
    if((*x)!=-1&&(*y)!=-1)
    {
        int sx,sy;
        sx=(*x);
        sy=(*y);
        int linecompleter=lineplay(board,x,y);
        if(linecompleter==-1)
        {
            (*x)=sx;
            (*y)=sy;
            if(board[*x][*y][*x][*y]=='.')
            {
                board[*x][*y][*x][*y]==player;
                return;
            }
            int i;
            for(i=0;i<9;i++)
            {
                x=playorder[i][0];
                y=playorder[i][1];
                if(board[sx][sy][*x][*y]=='.')
                {
                    board[sx][sy][*x][*y]==player;
                    return;
                }
            }
        }
        else
            return;
    }
    else
    {
        int i;
        //specifications of bigboard
        // 0 if it hasent been won and cannot be won by playing in this move
        // 1 if it can be won by playing in this move
        // 2 if it has already been won by him
        //-1 if it has already been won enemy
        int** bigboard = (int**) malloc(3*sizeof(int*));
        for (i=0; i<3; i++)
        bigboard[i] = (int*) malloc(3*sizeof(int));
        bigboard=generatebigboard(board);
        int d[8];
        int de[8];
        int j;
        for(i=0;i<3;i++)
        {
            if(bigboard[i][i]==2)
            {
                d[6]+=2;
            }
            de[6]+=bigboard[i][i];
            for(j=0;j<3;j++)
            {
                if(bigboard[i][j]==2)
                {
                    d[i]+=2;
                }
                de[i]+=bigboard[i][j];
                de[i+3]+=bigboard[j][i];
                if(bigboard[j][i]==2)
                {
                    d[i+3]+=2;
                }
                if(i+j==2)
                {
                    if(bigboard[i][j]==2)
                    {
                        d[7]+=2;
                    }
                    de[7]+=bigboard[i][j];
                }
            }
        }
        //
        //int maxi=maxof(d,de);
        if(maxi==0)
        {
            //play in available square following the pre defined order
            //while playing in the inner square just follow the pre defined order
        }
    }

}
int lineplay(char**** board,int* x,int* y)
{

    int l[8][3];
    int c;
    for(c=0;c<8;c++)
    {
        l[c][0]=0;
    }
    int i,j;
    char player=player(board);
    for(i=0;i<3;i++)
    {
        {if(board[*x][*y][i][i]==player)
            l[6][0]++;
            else
               { l[6][1]=i;
                l[6][2]=i;}
        }
        for(j=0;j<3;j++)
        {
            {
                if(board[*x][*y][i][j]==player)
                l[i][0]++;
                else
                {l[i][1]=i;
                l[i][2]=j;}

            }
            {
                if(board[*x][*y][j][i]==player)
                l[i+3]++;
                else
                {l[i+3][1]=j;
                l[i+3][2]=i;}
            }
            if(i+j==2)
            {
                {
                    if(board[*x][*y][i][j]==player)
                    l[7]++;
                    else
                    {l[7][1]=i;
                    l[7][2]=j;}
                }
            }
        }
    }
    int nooflines=0;
    for(c=0;c<8;c++)
    {
        if(l[i]==2)
            nooflines++;
    }
    if(nooflines==0)
        return -1;
    else
    {
        int a;
        for(a=0;a<8;a++)
        {
            if(l[a]==2)
            {
                board[*x][*y][l[a][1]][l[a][2]]=player;
                (*x)=l[a][1];
                (*y)=l[a][2];
                return 1;
            }
        }
    }
}
