//a bot which plays at the first available place in the 9*9 grid
#include <math.h>
#include <stdbool.h>
#include "gameio.h"

char toplayXorO(char**** mat4);


int main()
{
    int x;
    int y;
    int i,j,k,l;
    char**** mat4=input4D(&x,&y);
    char play=toplayXorO(mat4);
    if(x==-1)
    {
        bool dobreak = false;
        for(i=0;!dobreak &&i<3;i++)
        {
            for(j=0;!dobreak &&j<3;j++)
            {
                for(k=0;!dobreak &&k<3;k++)
                {
                    for(l=0;!dobreak &&l<3;l++)
                    {
                        if(mat4[i][j][k][l]=='.')
                        {
                            mat4[i][j][k][l]=play;
                            dobreak=true;
                            x=k;
                            y=l;
                        }
                    }
                }
            }
        }
    }
    else
    {
        bool dobreak = false;
        for(k=0;!dobreak &&k<3;k++)
        {
            for(l=0;!dobreak &&l<3;l++)
            {
                if(mat4[x][y][k][l]=='.')
                {
                    mat4[x][y][k][l]=play;
                    dobreak=true;
                    x=k;
                    y=l;
                }
            }
        }
    }
    output2file(mat4, x, y);
    return 0;
}

// X plays first, returns whose turn to play based on number of X and O
char toplayXorO(char**** mat4)
{
    int i,j,k,l;
    int c=0;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            for(k=0;k<3;k++)
            {
                for(l=0;l<3;l++)
                {
                    if(mat4[i][j][k][l]=='X')
                        c++;
                    else if(mat4[i][j][k][l]=='O')
                        c--;
                }
            }
        }
    }
    if(c)
        return 'O';
    else
        return 'X';

}
