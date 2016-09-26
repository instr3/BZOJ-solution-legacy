#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int nx,ny;
int map[1004][1004];
int tmark[1004][1004];int pmark,nmark;
int tmark2[1004][1004],pmark2;
bool visit[1004][1004];
int tm2p[1004*1004/2][2];
int tminfo[1004*1004/2][3];
int tminfo2[1004*1004/2][3];
int tct[1004*1004/2][2];
bool accept[1004*1004/2];
int tstk[1004*1004],pstk;
bool instk[1004][1004];
int tdirx[9]={0,1,0,-1,0,1,1,-1,-1};
int tdiry[9]={0,0,1,0,-1,1,-1,1,-1};
#define inrange(x,y) ((x)>0&&(x)<=nx&&(y)>0&&(y)<=ny)
int main()
{
    freopen("1235.in","r",stdin);
    freopen("1235.out","w",stdout);
    scanf("%d%d",&nx,&ny);
    char tstr[1002];
    for each(ix,nx)
    {
        scanf("%s",&tstr[1]);
        for each(iy,ny)
        {
            map[ix+1][iy+1]=tstr[iy]=='#'?1:0;
        }
    }
    ++++nx;++++ny;
    int tx,ty,tget;
    int tnx,tny;
    //STP1
    for each(ix,nx)
    {
        for each(iy,ny)
        {
            if(!map[ix][iy])
            if(!tmark[ix][iy])
            {
                ++pmark;
                tstk[++pstk]=ix*10000+iy;
                instk[ix][iy]=true;
                while(pstk)
                {
                    tget=tstk[pstk--];
                    tx=tget/10000;ty=tget%10000;
                    //cout<<pmark<<";"<<tx<<","<<ty<<endl;
                    instk[tx][ty]=false;
                    tmark[tx][ty]=pmark;
                    for each(idir,4)
                    {
                        tnx=tx+tdirx[idir];
                        tny=ty+tdiry[idir];
                        if(inrange(tnx,tny))
                        if(!map[tnx][tny])
                        if(!instk[tnx][tny])
                        if(!tmark[tnx][tny])
                        {
                            tstk[++pstk]=tnx*10000+tny;
                            instk[tnx][tny]=true;
                        }
                    }
                }
            }
        }
    }
    
    //STP2
    for each(ix,nx)
    {
        for each(iy,ny)
        {
            if(map[ix][iy])
            if(!tmark2[ix][iy])
            {
                ++pmark2;
                tm2p[pmark2][0]=ix;
                tm2p[pmark2][1]=iy;
                tstk[++pstk]=ix*10000+iy;
                instk[ix][iy]=true;
                while(pstk)
                {
                    tct[pmark2][0]++;
                    tget=tstk[pstk--];
                    tx=tget/10000;ty=tget%10000;
                    //cout<<pmark<<";"<<tx<<","<<ty<<endl;
                    instk[tx][ty]=false;
                    tmark2[tx][ty]=pmark2;
                    for each(idir,8)
                    {
                        tnx=tx+tdirx[idir];
                        tny=ty+tdiry[idir];
                        if(inrange(tnx,tny))
                        if(map[tnx][tny])
                        {
                            if(!instk[tnx][tny])
                            if(!tmark2[tnx][tny])
                            {
                                tstk[++pstk]=tnx*10000+tny;
                                instk[tnx][tny]=true;
                            }
                        }
                        else
                        {
                            if(!tminfo2[pmark2][1])
                            {
                                tminfo2[pmark2][1]=tmark[tnx][tny];
                            }
                            else if(!tminfo2[pmark2][2])
                            {
                                if(tminfo2[pmark2][1]==tmark[tnx][tny])continue;
                                else tminfo2[pmark2][2]=tmark[tnx][tny];
                            }
                            else
                            {
                                if(tminfo2[pmark2][1]==tmark[tnx][tny])continue;
                                if(tminfo2[pmark2][2]==tmark[tnx][tny])continue;
                                tminfo2[pmark2][0]=-1;
                            }
                        }
                    }
                }
            }
        }
    }
    //STP3
    int nmark2=pmark2;
    for each(pmark2,nmark2)
    {
        int ix=tm2p[pmark2][0];
        int iy=tm2p[pmark2][1];
        tstk[++pstk]=ix*10000+iy;
        instk[ix][iy]=true;
        while(pstk)
        {
            tct[pmark2][1]++;
            tget=tstk[pstk--];
            tx=tget/10000;ty=tget%10000;
            visit[tx][ty]=true;
            instk[tx][ty]=false;
            tmark2[tx][ty]=pmark2;
            for each(idir,4)
            {
                tnx=tx+tdirx[idir];
                tny=ty+tdiry[idir];
                if(inrange(tnx,tny))
                if(map[tnx][tny])
                {
                    if(!instk[tnx][tny])
                    if(!visit[tnx][tny])
                    {
                        tstk[++pstk]=tnx*10000+tny;
                        instk[tnx][tny]=true;
                    }
                }
            }
        }
        //cout<<"pmark2:"<<tct[pmark2][0]<<","<<tct[pmark2][1]<<endl;
    }
    //STP4
    nmark=pmark;
    for each(ix,nx)
    {
        for each(iy,ny)
        {
            if(!map[ix][iy])
            {
                pmark=tmark[ix][iy];
                for each(idir,4)
                {
                    tnx=ix+tdirx[idir];
                    tny=iy+tdiry[idir];
                    if(inrange(tnx,tny))
                    if(map[tnx][tny])
                    {
                        if(!tminfo[pmark][1])
                        {
                            tminfo[pmark][1]=tmark2[tnx][tny];
                        }
                        else if(!tminfo[pmark][2])
                        {
                            if(tminfo[pmark][1]==tmark2[tnx][tny])continue;
                            else tminfo[pmark][2]=tmark2[tnx][tny];
                        }
                        else
                        {
                            if(tminfo[pmark][1]==tmark2[tnx][tny])continue;
                            if(tminfo[pmark][2]==tmark2[tnx][tny])continue;
                            tminfo[pmark][0]=-1;
                        }
                    }
                }
            }
        }
    }
    int tot=0;
    for every(i,2,nmark)
    {
        if(tminfo[i][0]==-1)continue;
        if(tminfo[i][2]!=0)
        {
            if(tminfo2[tminfo[i][1]][2])swap(tminfo[i][1],tminfo[i][2]);
            //cout<<i<<":"<<tminfo[i][1]<<","<<tminfo[i][2]<<endl;
            if(tct[tminfo[i][1]][0]==tct[tminfo[i][1]][1])
            {
                if(tminfo2[tminfo[i][1]][0]!=-1&&tminfo2[tminfo[i][2]][0]!=-1)
                if(!tminfo2[tminfo[i][1]][2])
                {
                    accept[tminfo[i][1]]=accept[tminfo[i][2]]=true;
                    ++tot;
                    continue;
                }
            }
        }
        tminfo[i][0]=-1;
        //cout<<tminfo[i][1]<<","<<tminfo[i][2]<<endl;
    }
    printf("%d\n",tot);
    for every(ix,2,nx-1)
    {
        for every(iy,2,ny-1)
        {
            //if(tminfo[tmark[ix][iy]][0]==-1)
            //cout<<"-";else
            //cout<<tmark[ix][iy];
            if(accept[tmark2[ix][iy]])
            {
                putchar('#');
                //cout<<tmark2[ix][iy];
            }
            else putchar('.');
        }
        //cout<<endl;
        putchar('\n');
    }
}
