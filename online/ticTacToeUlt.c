#include <stdio.h>
#include <time.h>

int playAt(int val,int lX,int lY,int xL,int yL, int xS, int yS);
int playHuman(int lX,int lY,int *xSp,int *ySp);
int playComputer(int lX,int lY,int *xSp,int *ySp);
void setBest(int xL,int yL,int xS, int yS);
int recur(int val,int lX,int lY,int lev,int prevMinMax);
int calcVal(int tabl[3][3],int val,int *vict,int *full);
int evalue();
void print();

int order[9][2] = {{1,1},{0,0},{2,2},{2,0},{0,2},{1,0},{0,1},{2,1},{1,2}};
int tablS[3][3][3][3];
int tablL[3][3];
int tablSV[3][3];
int tablLV;

int xLbest,yLbest,xSbest,ySbest;

int maxLev;

int main(int argc,char *argv)
{
    // Init
    int xL,yL,xS,yS;
    tablLV = 0;
    for(xL=0;xL<3;++xL) {
        for(yL=0;yL<3;++yL) {
            tablL[xL][yL] = 0;
            tablSV[xL][yL] = 0;
            for(xS=0;xS<3;++xS)
                for(yS=0;yS<3;++yS)
                    tablS[xL][yL][xS][yS] = 0;
        }
    }
    maxLev = 8;
    
    int lX = -1, lY = -1;
    int ok = 0;
    // ok = playComputer(lX,lY,&lX,&lY); // For computer start
    while(!ok) {
        ok = playHuman(lX,lY,&lX,&lY);
        if(!ok)
            ok = playComputer(lX,lY,&lX,&lY);
    }
    print();
    return 0;
}

int playAt(int val,int lX,int lY,int xL,int yL, int xS, int yS)
{
    if(xL<0||xL>2||yL<0||yL>2||xS<0||xS>2||yS<0||yS>2) {
        printf("Bad params...\n");
        return 2;
    }
    if((lX>=0&&lY>=0&&tablL[lX][lY]==0&&(xL!=lX||yL!=lY))||tablL[xL][yL]!=0||tablS[xL][yL][xS][yS]!=0) {
        printf("Cannot play there...\n");
        return 2;
    }
    tablS[xL][yL][xS][yS] = val;
    int vict = 0;
    int full = 0;
    tablSV[xL][yL] = (calcVal(tablS[xL][yL],1,val==1?&vict:NULL,&full)-calcVal(tablS[xL][yL],2,val==2?&vict:NULL,NULL));
    if(vict) {
        if(val==1)
            printf("Gives me victory at xL = %d, yL = %d\n",xL, yL);
        else
            printf("Gives you victory at xL = %d, yL = %d\n",xL, yL);
        tablL[xL][yL] = val;
        tablSV[xL][yL] = 0;
        int globVict = 0;
        int globFull = 0;
        tablLV = (calcVal(tablL,1,val==1?&globVict:NULL,&globFull)-calcVal(tablL,2,val==2?&globVict:NULL,NULL));
        if(globVict) {
            if(val==1)
                printf("I won !\n");
            else
                printf("You won !\n");
            return 1;
        }
        if(globFull) {
            printf("It is a draw...\n");
            return 1;
        }
    } else if(full) {
        printf("Part at xL = %d, yL = %d is full with a draw\n",xL, yL);
        tablL[xL][yL] = 9;
        tablSV[xL][yL] = 0;
        int globFull = 0;
        tablLV = (calcVal(tablL,1,NULL,&globFull)-calcVal(tablL,2,NULL,NULL));
        if(globFull) {
            printf("It is a draw...\n");
            return 1;
        }
    }
    return 0;
}

int playHuman(int lX,int lY,int *xSp,int *ySp)
{
    int ok = 0;
    int xL, yL, xS, yS;
    print();
    while(!ok) {
        printf("Please give xL, yL, xS, yS (lX = %d ; lY = %d):\n",lX,lY);
        scanf("%1d %1d %1d %1d",&xL,&yL,&xS,&yS);
        scanf ("%*[^\n]");
        getchar ();
        if(xL<0||xL>2||yL<0||yL>2||xS<0||xS>2||yS<0||yS>2) {
            printf("Bad answer...\n");
            continue;
        }
        if((lX>=0&&lY>=0&&tablL[lX][lY]==0&&(xL!=lX||yL!=lY))||tablL[xL][yL]!=0||tablS[xL][yL][xS][yS]!=0) {
            printf("You cannot play there...\n");
            continue;
        }
        ok = 1;
    }
    printf("You are playing at xL = %d, yL = %d, xS = %d, yS = %d\n",xL,yL,xS,yS);
    int rep = playAt(2,lX,lY,xL,yL,xS,yS);
    if(xSp!=NULL)
        *xSp = xS;
    if(ySp!=NULL)
        *ySp = yS;
    return rep;
}

int playComputer(int lX,int lY,int *xSp,int *ySp)
{
    int nbAv = 0;
    int xL, yL, xS, yS;
    int res = 0;
    int t = 0;
    for(xL=0;xL<3;++xL)
        for(yL=0;yL<3;++yL)
            if(tablL[xL][yL]==0)
                for(xS=0;xS<3;++xS)
                    for(yS=0;yS<3;++yS)
                        if(tablS[xL][yL][xS][yS]==0)
                            ++nbAv;
    maxLev = (nbAv>6?6:nbAv);
    for(;maxLev<=nbAv&&t<2*CLOCKS_PER_SEC&&res!=1000000&&res!=-1000000;++maxLev) {
        clock_t tStart = clock();
        printf("Depth = %2d   ",maxLev);
        fflush(stdout);
        res = recur(1,lX,lY,0,1000000);
        t = (clock()-tStart);
        printf("   %6d second(s) -> res = %d\n",t/CLOCKS_PER_SEC,res);
    }
    if(res==1000000)
        printf("I will win for sure now...\n");
    else if(res==-1000000) {
        printf("I feel it very bad...\n");
        for(--maxLev;res==-1000000;--maxLev)
            res = recur(1,lX,lY,0,1000000);
    }
    printf("I will play at xL = %d, yL = %d, xS = %d, yS = %d\n",xLbest,yLbest,xSbest,ySbest);
    int rep = playAt(1,lX,lY,xLbest,yLbest,xSbest,ySbest);
    if(xSp!=NULL)
        *xSp = xSbest;
    if(ySp!=NULL)
        *ySp = ySbest;
    return rep;
}

void setBest(int xL,int yL,int xS, int yS)
{
    xLbest = xL;
    yLbest = yL;
    xSbest = xS;
    ySbest = yS;
}

int recur(int val,int lX,int lY,int lev,int prevMinMax)
{
    int i;
    if(lev==maxLev)
        return evalue();
    int res = (val==1?-1000000:1000000);
    int kL,kS,xL,yL,xS,yS;
    for(kL=0;kL<9;++kL) {
        xL = order[kL][0];
        yL = order[kL][1];
        if(tablL[xL][yL]!=0)
            continue;
        if(lX>=0&&lY>=0&&tablL[lX][lY]==0&&(xL!=lX||yL!=lY))
            continue;
        for(kS=0;kS<9;++kS) {
            xS = order[kS][0];
            yS = order[kS][1];
            if(tablS[xL][yL][xS][yS]!=0)
                continue;
            int oldSV = tablSV[xL][yL];
            int oldLV = tablLV;
            int vict = 0;
            int full = 0;
            int globVict = 0;
            int globFull = 0;
            tablS[xL][yL][xS][yS] = val;
            tablSV[xL][yL] = (calcVal(tablS[xL][yL],1,val==1?&vict:NULL,&full)-calcVal(tablS[xL][yL],2,val==2?&vict:NULL,NULL));
            if(vict) {
                tablL[xL][yL] = val;
                tablSV[xL][yL] = 0;
                tablLV = (calcVal(tablL,1,val==1?&globVict:NULL,&globFull)-calcVal(tablL,2,val==2?&globVict:NULL,NULL));
            } else if(full) {
                tablL[xL][yL] = 9;
                tablSV[xL][yL] = 0;
                tablLV = (calcVal(tablL,1,NULL,&globFull)-calcVal(tablL,2,NULL,NULL));
            }
            int calc = 0;
            if(globVict)
                calc = (val==1?1000000:-1000000);
            else if(!globFull)
                calc = recur(val==1?2:1,xS,yS,lev+1,res);
            tablS[xL][yL][xS][yS] = 0;
            tablSV[xL][yL] = oldSV;
            tablL[xL][yL] = 0;
            tablLV = oldLV;
            if(lev==0) {
                printf(".");
                fflush(stdout);
            }
            if(calc>res&&lev==0)
                setBest(xL,yL,xS,yS);
            if(val==1) {
                // Max
                if(calc>res)
                    res = calc;
                if(res>=prevMinMax)
                    return res;
            } else {
                // Min
                if(calc<=res)
                    res = calc;
                if(res<=prevMinMax)
                    return res;
            }
        }
    }
    return res;
}

int calcVal(int tabl[3][3],int val,int *vict,int *full)
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
            if(vict!=NULL) *vict = 1;
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
            if(vict!=NULL) *vict = 1;
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
        if(vict!=NULL) *vict = 1;
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
        if(vict!=NULL) *vict = 1;
        return 0;
    } else if(cptD2==2)
        res += 5;
    else if(cptD2==1)
        res += 1;
    if(vict!=NULL) *vict = 0;
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

int evalue()
{
    return ((5*tablSV[1][1]+3*(tablSV[0][0]+tablSV[0][2]+tablSV[2][0]+tablSV[2][2])+tablSV[0][1]+tablSV[1][0]+tablSV[1][2]+tablSV[2][1])+1000*tablLV);
}

void print()
{
    int x,y;
    printf("tablS:\n");
    for(y=0;y<9;++y) {
        for(x=0;x<9;++x) {
            int val = tablS[x/3][y/3][x%3][y%3];
            printf(val==0?".":(val==2?"X":"O"));
            if((x%3)==2)
                printf(" ");
        }
        printf("\n");
        if((y%3)==2)
            printf("\n");
    }
    printf("tablSV:\n");
    for(y=0;y<3;++y) {
        for(x=0;x<3;++x)
            printf("%3d ",tablSV[x][y]);
        printf("\n");
    }
    printf("\ntablL:\n");
    for(y=0;y<3;++y) {
        for(x=0;x<3;++x) {
            int val = tablL[x][y];
            printf(val==0?".":(val==9?"#":(val==2?"X":"O")));
        }
        printf("\n");
    }
    printf("\ntablLV = %d\n\n",tablLV);
}
