#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int tdy[5]={0,-1,0,1,0};
int tdx[5]={0,0,-1,0,1};
//#define inrange(x,y)
//#define inchunk(x,y,x0,y0) (((x)-1)/3==((x0)-1)/3&&((y)-1)/3==((y0)-1)/3)
bool cmps[10][10][5];
int tlim[2][10]={0,1,1,1,4,4,4,7,7,7,0,3,3,3,6,6,6,9,9,9};
int tb[10][10];
int td[10][10][10];
int tgx,tgy,tgz;
//#define savegame do{for each(tgx,9)for each(tgy,9)for every(tgz,0,9)tsd[tgx][tgy][tgz]=td[tgx][tgy][tgz];}while(0)
//#define loadgame do{for each(tgx,9)for each(tgy,9)for every(tgz,0,9)td[tgx][tgy][tgz]=tsd[tgx][tgy][tgz];}while(0)
#define orz int

struct cnode
{
    
    orz x,y,z;
    
};




void dfs()
{
    cnode myc[35];int pmyc=0;
    int tmin=999,minatx=0,minaty=0;
    for each(itx,9)
    {
        for each(ity,9)
        {
            if(tb[itx][ity])continue;
            if(td[itx][ity][0]<tmin)
            {
                tmin=td[itx][ity][0];
                minatx=itx;
                minaty=ity;
            }
        }
    }
    int ix=minatx,iy=minaty;
    int tnx,tny,tnz;
    if(tmin==999)
    {
        for each(itx,9)
        {
            for each(ity,8)
            {
                printf("%d ",tb[itx][ity]);
            }
            printf("%d\n",tb[itx][9]);
        }
        exit(0);
    }
    //int tsd[10][10][10];
    //savegame;
    for each(iz,9)
    {
        if(!td[ix][iy][iz])continue;
        tb[ix][iy]=iz;
        for every(itx,1,9)
        {
            if(tb[itx][iy])continue;
            if(td[itx][iy][iz])
            {
                td[itx][iy][0]--;
                td[itx][iy][iz]=false;
                myc[++pmyc]=(cnode){itx,iy,iz};
                if(td[itx][iy][0]==0)goto die;
            }
        }
        for every(ity,1,9)
        {
            if(tb[ix][ity])continue;
            if(td[ix][ity][iz])
            {
                td[ix][ity][0]--;
                td[ix][ity][iz]=false;
                myc[++pmyc]=(cnode){ix,ity,iz};
                if(td[ix][ity][0]==0)goto die;
            }
        }
        for every(itx,tlim[0][ix],tlim[1][ix])
        {
            for every(ity,tlim[0][iy],tlim[1][iy])
            {
                if(tb[itx][ity])continue;
                if(td[itx][ity][iz])
                {
                    td[itx][ity][0]--;
                    td[itx][ity][iz]=false;
                    myc[++pmyc]=(cnode){itx,ity,iz};
                    if(td[itx][ity][0]==0)goto die;
                }
            }
        }
        for each(idir,4)
        {
            tnx=ix+tdx[idir],tny=iy+tdy[idir];
            if(tnx>tlim[1][ix]||tnx<tlim[0][ix])continue;
            if(tny>tlim[1][iy]||tny<tlim[0][iy])continue;
            if(tb[tnx][tny])continue;
            if(cmps[ix][iy][idir])
            {
                for every(itz,iz+1,9)
                {
                    //cout<<tnx<<","<<tny<<"Inf"<<ix<<","<<iy<<","<<iz<<"AT"<<itz<<endl;
                    if(td[tnx][tny][itz])
                    {
                        td[tnx][tny][0]--;
                        td[tnx][tny][itz]=false;
                        myc[++pmyc]=(cnode){tnx,tny,itz};
                        if(td[tnx][tny][0]==0)goto die;
                    }
                }
            }
            else
            {
                for every(itz,1,iz-1)
                {
                    if(td[tnx][tny][itz])
                    {
                        td[tnx][tny][0]--;
                        td[tnx][tny][itz]=false;
                        myc[++pmyc]=(cnode){tnx,tny,itz};
                        if(td[tnx][tny][0]==0)goto die;
                    }
                }
            }
        }
        //if(iy==1)
        //dfs(ix-1,9);
        //else
        //dfs(ix,iy-1);
        dfs();
        die:;
        //loadgame;
        while(pmyc)
        {
            tnx=myc[pmyc].x;
            tny=myc[pmyc].y;
            tnz=myc[pmyc].z;
            --pmyc;
            td[tnx][tny][tnz]=true;
            td[tnx][tny][0]++;
        }
            
    }
    tb[ix][iy]=0;
}
void task()
{
    for each(ix,9)
    for each(iy,9)
    {
        td[ix][iy][0]=9;
        for each(iz,9)
        {
            td[ix][iy][iz]=1;
        }
    }
    //pid=0;
    /*for each(ix,9)
    {
        for each(iy,9)
        {
            myd[++pid].x=ix;
            myd[pid].y=iy;
        }
    }*/
    dfs();
}


inline char readchar()
{
    char tc=0;
    while(tc!='>'&&tc!='<'&&tc!='v'&&tc!='^')tc=getchar();
    return tc;
}
inline void readx(int ix)
{
    char tc;
    tc=readchar();
    cmps[ix][1][3]=tc=='>';
    cmps[ix][2][1]=tc=='<';
    tc=readchar();
    cmps[ix][2][3]=tc=='>';
    cmps[ix][3][1]=tc=='<';
    tc=readchar();
    cmps[ix][4][3]=tc=='>';
    cmps[ix][5][1]=tc=='<';
    tc=readchar();
    cmps[ix][5][3]=tc=='>';
    cmps[ix][6][1]=tc=='<';
    tc=readchar();
    cmps[ix][7][3]=tc=='>';
    cmps[ix][8][1]=tc=='<';
    tc=readchar();
    cmps[ix][8][3]=tc=='>';
    cmps[ix][9][1]=tc=='<';
}
inline void ready(int ix)
{
    char tc;
    for each(iy,9)
    {
        tc=readchar();
        cmps[ix][iy][4]=tc=='v';
        cmps[ix+1][iy][2]=tc=='^';
    }
}    
int main()
{
    freopen("3109.in","r",stdin);
    freopen("3109.out","w",stdout);
    readx(1);ready(1);readx(2);ready(2);readx(3);
    readx(4);ready(4);readx(5);ready(5);readx(6);
    readx(7);ready(7);readx(8);ready(8);readx(9);
    task();
    
}
