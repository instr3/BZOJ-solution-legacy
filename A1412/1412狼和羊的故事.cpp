#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
struct enode{int to,f,c,next;}mye[80002];int pmye=1;
struct vnode{int first,h;}myv[10001];
int testk[800002];int pestk;
int n;
int tot;
int th[10001];
inline void addedge(int pf,int pt,int pw)
{
    //cout<<pf<<","<<pt<<","<<pw<<endl;
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
int indata[102][102];
int pin[102][102];
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    int nx,ny;
    scanf("%d%d",&nx,&ny);
    n=1;
    for each(ix,nx)
    for each(iy,ny)
    {
        scanf("%d",&indata[ix][iy]);
        if(ix-1&&iy-1&&indata[ix][iy]!=0)
        {
            if(indata[ix][iy]==indata[ix-1][iy])
            pin[ix][iy]=pin[ix-1][iy];
            else if(indata[ix][iy]==indata[ix][iy-1])
            pin[ix][iy]=pin[ix][iy-1];
        }
        if(!pin[ix][iy])
        pin[ix][iy]=++n;
    }
    ++n;
    for each(ix,nx)
    for each(iy,ny)
    {
        if(indata[ix][iy]==2)
        {
            addedge(pin[ix][iy],n,99999999);
            continue;
        }
        if(indata[ix][iy]==1)
        {
            addedge(1,pin[ix][iy],99999999);
        }
        if(ix-1 &&indata[ix-1][iy]!=1)
         addedge(pin[ix][iy],pin[ix-1][iy],1);
        if(iy-1 &&indata[ix][iy-1]!=1)
         addedge(pin[ix][iy],pin[ix][iy-1],1);
        if(ix<nx&&indata[ix+1][iy]!=1)
         addedge(pin[ix][iy],pin[ix+1][iy],1);
        if(iy<ny&&indata[ix][iy+1]!=1)
         addedge(pin[ix][iy],pin[ix][iy+1],1);
    }
    sap();
    cout<<tot;
    /*n=5;
    addedge(1,5,1);
    addedge(1,2,2);
    addedge(2,3,1);
    addedge(3,5,3);
    addedge(2,3,1);
    addedge(2,5,4);
    addedge(1,3,4);
    addedge(1,2,2);
    addedge(2,3,1);
    addedge(3,5,3);

    sap();*/
}
