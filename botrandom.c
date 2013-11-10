//a bot which plays at the first available place in the 9*9 grid
#include <math.h>
#include <gamio.h>
char toplayXorO(char**** mat4);
int main()
{
    int *x;
    int *y;
     char**** mat4 = (char****) malloc(3*sizeof(char***));
    int i,j,k,l;
    for (i=0; i<3; i++) {
        mat4[i] = (char***) malloc(3*sizeof(char**));
        for (j=0; j<3; j++) {
            mat4[i][j] = (char**) malloc(3*sizeof(char*));
            for (k=0; k<3; k++) {
                mat4[i][j][k] = (char*) malloc(3*sizeof(char));

    mat4=input4D(x,y);
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
                        if(mat4[i][j][k][l]=='X'||mat4[i][j][k][l]=='O')
                        else
                        {
                            mat4[i][j][k][l]==play;
                            break;
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
                if(mat4[x][y][k][l]=='X'||mat4[x][y][k][l]=='O')
                else
                {
                    mat4[x][y][k][l]==play;
                    break;
                }
            }
        }
    }
}
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
