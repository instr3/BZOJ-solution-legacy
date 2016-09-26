#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int nx,ny,nz;
int indata[5001];int pin;
bool tdata[5001];
struct ck3dpoint
{
    int x,y,z;
}tpoint[5001];int ppoint;
#define locate(x,y,z) (((x)-1)*ny*nz+((y)-1)*nz+(z))
#define locate2(x,y,z) (((x)-1)*tsy*tsz+((y)-1)*tsz+(z))

#define min(a,b) ((a)<(b)?(a):(b))
int zmap[72][5001];
int zedge[72][5001],pzc[72];
int zx[72],zy[5001];
//int tax[72],tay[5001];
bool visit[5001];
bool zpath(int ix)
{
    int iy;
    for each(ie,pzc[ix])
    {
        iy=zedge[ix][ie];
        //if(zmap[ix][iy])
        {
            if(visit[iy])continue;
            visit[iy]=true;
            if(!zy[iy])
            {
                zx[ix]=iy;
                zy[iy]=ix;
                return true;
            }
            else if(zpath(zy[iy]))
            {
                zx[ix]=iy;
                zy[iy]=ix;
                return true;
            }
        }
    }
    return false;
}
#define getbit(izz,i) (izz&(1<<(i)-1)) 
void subtask()
{
    int tot=99999999;
    /*Announcement:
        ix=1..70,
        iy=1..5000,
        iz=1..17*/
    int res;
    int tpv;
    int nzz=1<<nz;
    //int tcx,tcy;
    for every(izz,0,nzz-1)
    {
        
        //memset(zmap,0,sizeof zmap);
        tpv=0;
        res=0;
        for each(iz,nz)
        {
            if(getbit(izz,iz))++res;
        }
        if(res>=tot)continue;
        for each(ix,nx)zx[ix]=0,pzc[ix]=0;//zmap[ix][0]=0;
        for each(iy,ny)zy[iy]=0;//zmap[0][iy]=0;
        for each(ix,nx)
        for each(iy,ny)
        {
            zmap[ix][iy]=0;
            zedge[ix][iy]=0;
        }
        //tcx=tcy=0;
        /*
        for each(iz,nz)
        {
            if(getbit(izz,iz))continue;
            for each(ix,nx)
            for each(iy,ny)
            {
                if(tdata[locate(ix,iy,iz)])
                {
                    if(!zmap[ix][iy])
                    {
                        zmap[ix][iy]=true;
                        zedge[ix][++pzc[ix]]=iy;
                    }
                }
            }
        }*/
        int ix,iy,iz;
        for each(i,ppoint)
        {
            ix=tpoint[i].x;
            iy=tpoint[i].y;
            iz=tpoint[i].z;
            if(getbit(izz,iz))continue;
            if(!zmap[ix][iy])
            {
                zmap[ix][iy]=true;
                zedge[ix][++pzc[ix]]=iy;
            }
        }
        //if(min(tcx,tcy)+res>=tot)continue;
        for each(ix,nx)
        {
            //memset(visit,0,sizeof visit);
            for each(iy,ny)visit[iy]=false;
            if(zpath(ix))++res;
            if(res>=tot)goto die;
        }
        //printf("%d,%d\n",izz,res);
        tot=min(tot,res);
        die:;
    }
    printf("%d\n",tot);
    
}
void task()
{
    scanf("%d%d%d",&nx,&ny,&nz);
    pin=0;
    for each(i,nx)
    {
        for each(j,ny)
        {
            for each(k,nz)
            {
                scanf("%d",&indata[++pin]);
                //if(indata[pin])cout<<pin<<endl;
            }
        }
    }
    int tsx=nx,tsy=ny,tsz=nz;
    if(nz>ny)
    {
        swap(nz,ny);
        for each(ix,nx)
        for each(iy,ny)
        for each(iz,nz)
        {
            tdata[locate(ix,iy,iz)]=indata[locate2(ix,iz,iy)];
        }
        for each(ix,nx)
        for each(iy,ny)
        for each(iz,nz)
        {
            indata[locate(ix,iy,iz)]=tdata[locate(ix,iy,iz)];
        }
        swap(tsy,tsz);
    }
    if(nz>nx)
    {
        swap(nz,nx);
        for each(ix,nx)
        for each(iy,ny)
        for each(iz,nz)
        {
            tdata[locate(ix,iy,iz)]=indata[locate2(iz,iy,ix)];
        }
        for each(ix,nx)
        for each(iy,ny)
        for each(iz,nz)
        {
            indata[locate(ix,iy,iz)]=tdata[locate(ix,iy,iz)];
        }
        swap(tsx,tsz);
    }
    if(nx>ny)
    {
        swap(nz,nx);
        for each(ix,nx)
        for each(iy,ny)
        for each(iz,nz)
        {
            tdata[locate(ix,iy,iz)]=indata[locate2(iy,ix,iz)];
        }
        for each(ix,nx)
        for each(iy,ny)
        for each(iz,nz)
        {
            indata[locate(ix,iy,iz)]=tdata[locate(ix,iy,iz)];
        }
        swap(tsx,tsy);
    }
    ppoint=0;
    for each(ix,nx)
    for each(iy,ny)
    for each(iz,nz)
    {
        if(tdata[locate(ix,iy,iz)]=indata[locate(ix,iy,iz)])
            tpoint[++ppoint]=(ck3dpoint){ix,iy,iz};
    }
    /*for each(ix,nx)
    {
        for each(iy,ny)
        {
            for each(iz,nz)
            {
                cout<<indata[locate(ix,iy,iz)]<<" ";
            }
            cout<<endl;
        }
    }*/
    //return;
    subtask();
}
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    int nt;scanf("%d",&nt);
    for each(i,nt)
    task();
}
