#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
struct enode{int to,f,c,next;}mye[900001];int pmye=1;
struct vnode{int first,h;}myv[64011];
int testk[900001];int pestk;
int n;
int tot;
int th[64011];
inline void addedge(int pf,int pt,int pw)
{
    //cout<<pf<<","<<pt<<","<<pw<<endl;
    if(pf==0||pt==0)return;
    mye[++pmye].to=pt;
    mye[pmye].f=0;
    mye[pmye].c=pw;
    mye[pmye].next=myv[pf].first;
    myv[pf].first=pmye;
    
    mye[++pmye].to=pf;
    mye[pmye].f=0;
    mye[pmye].c=0;
    mye[pmye].next=myv[pt].first;
    myv[pt].first=pmye;
}
void sap()
{
    int pf,pt;
    bool tfind;
    int minw;
    th[0]=n;
    while(true)
    {
        pestk=0;
        pf=1;
        while(true)
        {
            tfind=false;
            for(int p=myv[pf].first;p;p=mye[p].next)
            {
                pt=mye[p].to;
                if(mye[p].f<mye[p].c&&myv[pf].h==myv[pt].h+1)
                {
                    testk[++pestk]=p;
                    pf=pt;
                    tfind=true;
                    if(pt==n)
                    {
                        minw=99999999;
                        for each(i,pestk)
                        {
                            minw=min(minw,mye[testk[i]].c-mye[testk[i]].f);
                        }
                        tot+=minw;
                        //cout<<minw<<":1 ";
                        for each(i,pestk)
                        {
                            mye[testk[i]].f+=minw;
                            mye[testk[i]^1].f-=minw;
                            //cout<<mye[testk[i]].to<<" ";
                        }
                        //cout<<endl;
                        pestk=0;
                        goto m_break;
                    }
                    break;
                }
            }
            if(!tfind)
            {
                th[myv[pf].h]--;
                if(!th[myv[pf].h])return;
                myv[pf].h++;
                th[myv[pf].h]++;
                if(myv[pf].h>n)return;
                if(pestk>=2)
                {
                    pestk--;
                    pf=mye[testk[pestk]].to;
                    continue;
                }
                else break;
            }
        }
m_break:; 
    }
}
int indata[41][41][41];
int parr[42][42][42];
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    #define oo 99999999
    int nx,ny,nz,nd;
    scanf("%d%d%d",&nx,&ny,&nz);
    scanf("%d",&nd);
    n=1;
    for each(iz,nz)
    for each(ix,nx)
    for each(iy,ny)
    {
        scanf("%d",&indata[ix][iy][iz]);
        
    }
    for each(ix,nx)
    for each(iy,ny)
    for every(iz,0,nz)
    {
        parr[ix][iy][iz]=++n;
        if(iz)addedge(parr[ix][iy][iz-1],parr[ix][iy][iz],indata[ix][iy][iz]);
    }
    ++n;
    for each(ix,nx)
    for each(iy,ny)
    {
        addedge(1,parr[ix][iy][0],oo);
        addedge(parr[ix][iy][nz],n,oo);
    }
    for each(ix,nx)
    for each(iy,ny)
    for every(iz,0,nz)
    {
        if(iz-nd>0  )addedge(parr[ix][iy][iz],parr[ix+1][iy][iz-nd],oo);
        if(iz+nd<=nz)addedge(parr[ix+1][iy][iz+nd],parr[ix][iy][iz],oo);
        if(iz-nd>0  )addedge(parr[ix][iy][iz],parr[ix][iy+1][iz-nd],oo);
        if(iz+nd<=nz)addedge(parr[ix][iy+1][iz+nd],parr[ix][iy][iz],oo);
    }
        
        
    sap();
    cout<<tot<<endl;
}
