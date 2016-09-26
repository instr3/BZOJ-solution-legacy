#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;
int na,nb,ns,ans;
struct tnode
{
    int w,x,y;
};
struct deque
{
    int pf,pt;
    deque(){pf=1;pt=0;};
    inline void clear(){{pf=1;pt=0;};}
    tnode d[2001];
    inline void popfront()
    {
        ++pf;
        if(pf==1000001)pf=0;
    }
    inline void popback()
    {
        --pt;
        if(pt==-1)pt=1000001;
    }
    inline void push(int ix,int iy,int iw,bool iop)//TRUE:×î´óÖµ 
    {
        while((d[pt].w<=iw)==iop&&pf-1!=pt)popback();
        ++pt;
        if(pt==1000001)pt=0;
        d[pt].w=iw;
        d[pt].x=ix;
        d[pt].y=iy;
    }
    inline bool empty(){return pf-1==pt;}
    inline tnode getfront(){return d[pf];}
    inline tnode getback(){return d[pt];}
}qmax,qmin,sqmax,sqmin;
int data[1001][1001];
int dp1[1001][1001];
int dp2[1001][1001];
int main()
{
    freopen("1047.in","r",stdin);
    freopen("1047.out","w",stdout);
    scanf("%d%d%d",&na,&nb,&ns);
    for(int i=1;i<=na;++i)
    {
        for(int j=1;j<=nb;++j)
        {
            scanf("%d",&data[i][j]);
        }
    }
    /*for(int i=1;i<=na;++i)
    {
        for(int j=1;j<=nb;++j)
        {
            qmax[i].push(i,j,data[i][j],true);
            qmin[i].push(i,j,data[i][j],false);
        }
    }*/
    for(int i=1;i<=na;++i)
    {
        qmax.clear();
        qmin.clear();
        for(int j=1;j<=nb;++j)
        {
            qmax.push(i,j,data[i][j],true);
            qmin.push(i,j,data[i][j],false);
            if(j>=ns)
            {
                while(!(qmax.empty()||qmax.getfront().y>=j-ns+1))qmax.popfront();
                while(!(qmin.empty()||qmin.getfront().y>=j-ns+1))qmin.popfront();
                dp1[i][j-ns+1]=qmax.getfront().w;
                dp2[i][j-ns+1]=qmin.getfront().w;
                //cout<<dp2[i][j-ns+1]<<" ";
            }
        }
        //cout<<endl;
    }
    int ans=2000000000;
    for(int j=1;j<=nb-ns+1;++j)
    {
        qmax.clear();
        qmin.clear();
        for(int i=1;i<=na;++i)
        {
            qmax.push(i,j,dp1[i][j],true);
            qmin.push(i,j,dp2[i][j],false);
            if(i>=ns)
            {
                while(!(qmax.empty()||qmax.getfront().x>=i-ns+1))qmax.popfront();
                while(!(qmin.empty()||qmin.getfront().x>=i-ns+1))qmin.popfront();
                //cout<<qmin.getfront().w<<" ";
                ans=min(ans,qmax.getfront().w-qmin.getfront().w);
            }
        }
        //cout<<endl;
    }
            
    printf("%d",ans);
}
