#include <stdio.h>
#include "gameio.h"

#define LEVELMAX 8

//#define TABS (turn=='X')?"X.dat":"O.dat"
#define TABS "XO.dat"

void playmove(int val,int lX,int lY,int xL,int yL, int xS, int yS);
void bot(int lX,int lY);
void setmove(int xL,int yL,int xS, int yS);
int think(int val,int lX,int lY,int lev,int previous);
int Bvalcalc(int tabl[3][3],int val,int *win,int *full);
int evaluate();

char**** board;
int order[9][2] = {{1,1},{0,0},{2,2},{2,0},{0,2},{1,0},{0,1},{2,1},{1,2}};
int mat4[3][3][3][3];
int bigB[3][3];
int smallBval[3][3];
int bigBval;
int xLmove,yLmove,xSmove,ySmove;
int level;
int turn;

char player() {
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

void init()
{
    FILE* fp = fopen(TABS, "r");
    int i,j;
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            fscanf(fp, "%d", &smallBval[i][j]);
        }
    }
    fscanf(fp, "%d", &bigBval);
    fclose(fp);
}

void deinit() {
    FILE* fp = fopen(TABS, "w");
    int i, j;
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            fprintf(fp, "%d ", smallBval[i][j]);
        }
    }
    fprintf(fp, "%d", bigBval);
    fclose(fp);
}

int main() {
    // Initialization
    int lX, lY;
    board = input4D(&lX, &lY);
    int i, j, k, l;
    int t = 0;
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            smallBval[i][j] = 0;
            for (k=0; k<3; k++) {
                for (l=0; l<3; l++) {
                    if (board[i][j][k][l] == 'X') {
                        mat4[i][j][k][l] = 2;
                    }
                    else if (board[i][j][k][l] == 'O') {
                        mat4[i][j][k][l] = 1;
                    }
                    else mat4[i][j][k][l] = 0;
                }
            }
            k=check3x3(board[i][j]);
            if (k == 2)
                bigB[i][j] = t = 1;
            else if (k == 1)
                bigB[i][j] = t = 2;
            else bigB[i][j] = 0;
        }
    }
    bigBval = 0;
    turn = player();

    if (t) init();
    bot(lX,lY);
    playmove((player()=='X')+1,lX,lY,xLmove,yLmove,xSmove,ySmove);
    
    output2file(board,xSmove,ySmove);
    deinit();

    printf("I play: %d,%d,%d,%d\n\n", xLmove, yLmove, xSmove, ySmove);
    return 9*(3*xLmove+xSmove) + (3*yLmove+ySmove);
}

void bot(int lX,int lY)
{
    int nbAv = 0;
    int xL, yL, xS, yS;
    int res = 0;
    for(xL=0;xL<3;++xL)
        for(yL=0;yL<3;++yL)
            if(bigB[xL][yL]==0)
                for(xS=0;xS<3;++xS)
                    for(yS=0;yS<3;++yS)
                        if(mat4[xL][yL][xS][yS]==0)
                            ++nbAv;
    
    for (;level<=LEVELMAX&&res!=1000000&&res!=-1000000;++level) {
        res = think(1,lX,lY,0,1000000);
    }

    if (res==-1000000)
        for(--level;res==-1000000;--level)
            res = think(1,lX,lY,0,1000000);
}

void setmove(int xL,int yL,int xS, int yS)
{ xLmove = xL; yLmove = yL; xSmove = xS; ySmove = yS; }

int think(int val,int lX,int lY,int lev,int previous)
{
    if(lev==level)
        return evaluate();
    int res = (val==1?-1000000:1000000);
    int kL,kS,xL,yL,xS,yS;
    for(kL=0;kL<9;++kL) {
        xL = order[kL][0];
        yL = order[kL][1];
        if(bigB[xL][yL]!=0)
            continue;
        if(lX>=0&&lY>=0&&bigB[lX][lY]==0&&(xL!=lX||yL!=lY))
            continue;
        for(kS=0;kS<9;++kS) {
            xS = order[kS][0];
            yS = order[kS][1];
            if(mat4[xL][yL][xS][yS]!=0)
                continue;
            int oldSval = smallBval[xL][yL];
            int oldBval = bigBval;
            int win = 0;
            int full = 0;
            int globalwin = 0;
            int globalFull = 0;
            mat4[xL][yL][xS][yS] = val;
            smallBval[xL][yL] = (Bvalcalc(mat4[xL][yL],1,val==1?&win:NULL,&full)-Bvalcalc(mat4[xL][yL],2,val==2?&win:NULL,NULL));
            if(win) {
                bigB[xL][yL] = val;
                smallBval[xL][yL] = 0;
                bigBval = (Bvalcalc(bigB,1,val==1?&globalwin:NULL,&globalFull)-Bvalcalc(bigB,2,val==2?&globalwin:NULL,NULL));
            } else if(full) {
                bigB[xL][yL] = 9;
                smallBval[xL][yL] = 0;
                bigBval = (Bvalcalc(bigB,1,NULL,&globalFull)-Bvalcalc(bigB,2,NULL,NULL));
            }
            int calc = 0;
            if(globalwin)
                calc = (val==1?1000000:-1000000);
            else if(!globalFull)
                calc = think(val==1?2:1,xS,yS,lev+1,res);
            mat4[xL][yL][xS][yS] = 0;
            smallBval[xL][yL] = oldSval;
            bigB[xL][yL] = 0;
            bigBval = oldBval;
            if(calc>res&&lev==0)
                setmove(xL,yL,xS,yS);
            if(val==1) {
                // Max
                if(calc>res)
                    res = calc;
                if(res>=previous)
                    return res;
            } else {
                // Min
                if(calc<=res)
                    res = calc;
                if(res<=previous)
                    return res;
            }
        }
    }
    return res;
}

int Bvalcalc(int tabl[3][3],int val,int *win,int *full)
{
    int res = 0;
    int x,y,k;
    // Horiz
    for(y=0;y<3;++y) {
        int cptH = 0;
        for(x=0;x<3&&cptH>=0;++x) {
            if(tabl[x][y]==val)
                ++cptH;
            else if(tabl[x][y]!=0)
                cptH = -1;
        }
        if(cptH==3) {
            if(win!=NULL) *win = 1;
            return 0;
        } else if(cptH==2)
            res += 5;
        else if(cptH==1)
            res += 1;
    }
    // Vert
    for(x=0;x<3;++x) {
        int cptV = 0;
        for(y=0;y<3&&cptV>=0;++y) {
            if(tabl[x][y]==val)
                ++cptV;
            else if(tabl[x][y]!=0)
                cptV = -1;
        }
        if(cptV==3) {
            if(win!=NULL) *win = 1;
            return 0;
        } else if(cptV==2)
            res += 5;
        else if(cptV==1)
            res += 1;
    }
    // Diag 1
    int cptD1 = 0;
    for(k=0;k<3&&cptD1>=0;++k) {
        if(tabl[k][k]==val)
            ++cptD1;
        else if(tabl[k][k]!=0)
            cptD1 = -1;
    }
    if(cptD1==3) {
        if(win!=NULL) *win = 1;
        return 0;
    } else if(cptD1==2)
        res += 5;
    else if(cptD1==1)
        res += 1;
    // Diag 2
    int cptD2 = 0;
    for(k=0;k<3&&cptD2>=0;++k) {
        if(tabl[k][2-k]==val)
            ++cptD2;
        else if(tabl[k][2-k]!=0)
            cptD2 = -1;
    }
    if(cptD2==3) {
        if(win!=NULL) *win = 1;
        return 0;
    } else if(cptD2==2)
        res += 5;
    else if(cptD2==1)
        res += 1;
    if(win!=NULL) *win = 0;
    if(full!=NULL) {
        int f = 1;
        for(x=0;x<3&&f;++x)
            for(y=0;y<3&&f;++y)
                if(tabl[x][y]==0)
                    f = 0;
        *full = f;
    }
    return res;
}

int evaluate()
{
    return ((5*smallBval[1][1]+3*(smallBval[0][0]+smallBval[0][2]+smallBval[2][0]+smallBval[2][2])+smallBval[0][1]+smallBval[1][0]+smallBval[1][2]+smallBval[2][1])+1000*bigBval);
}

void playmove(int val,int lX,int lY,int xL,int yL, int xS, int yS)
{
    mat4[xL][yL][xS][yS] = val;
    if (val == 1)
        board[xL][yL][xS][yS] = 'O';
    else if (val == 2)
        board[xL][yL][xS][yS] = 'X';
    int win = 0;
    int full = 0;
    smallBval[xL][yL] = (Bvalcalc(mat4[xL][yL],1,val==1?&win:NULL,&full)-Bvalcalc(mat4[xL][yL],2,val==2?&win:NULL,NULL));
    if(win) {
        bigB[xL][yL] = val;
        smallBval[xL][yL] = 0;
        int globalwin = 0;
        int globalFull = 0;
        bigBval = (Bvalcalc(bigB,1,val==1?&globalwin:NULL,&globalFull)-Bvalcalc(bigB,2,val==2?&globalwin:NULL,NULL));
    }
    else if(full) {
        bigB[xL][yL] = 9;
        smallBval[xL][yL] = 0;
        int globalFull = 0;
        bigBval = (Bvalcalc(bigB,1,NULL,&globalFull)-Bvalcalc(bigB,2,NULL,NULL));
    }
}
