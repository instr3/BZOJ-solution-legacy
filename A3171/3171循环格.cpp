#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=n;++i)
#define MAXN 1001
#define OO 199999999
struct enode{int w,c,fr,to,next;}mye[4*MAXN];int pmye=1;
struct vnode{int wp,pre,first;}myv[MAXN];
//int mys[MAXN],pmys;
struct queue
{
    int ft,bk;
    int d[MAXN];
    queue(){ft=1;};
    inline void clean(){ft=1;bk=0;};
    inline void push(int iv)
    {
        ++ft;if(ft==MAXN)ft-=MAXN;
        d[ft]=iv;
    }
    inline int pop()
    {
        ++bk;if(bk==MAXN){bk-=MAXN;return d[MAXN-1];}
        else return d[bk-1];
    }
    inline bool empty(){return ft+1==bk;}
}myq;bool inque[MAXN];
int n,nm;
int tot;
inline void addedge(int pf,int pt,int pw,int pc)
{
    //cout<<"Add:"<<pf<<","<<pt<<","<<pw<<","<<pc<<endl;
    mye[++pmye].to=pt;
    mye[pmye].fr=pf;
    mye[pmye].w=pw;
    mye[pmye].c=pc;
    mye[pmye].next=myv[pf].first;
    myv[pf].first=pmye;
    
    mye[++pmye].to=pf;
    mye[pmye].fr=pt;
    mye[pmye].w=0;
    mye[pmye].c=-pc;
    mye[pmye].next=myv[pt].first;
    myv[pt].first=pmye;
}
void spfa()
{
    int pf,pt;
    myq.clean();
    for each(i,n) myv[i].wp=OO;
    myv[1].wp=0;
    myq.push(1);
    inque[1]=true;
    while(!myq.empty())
    {
        pf=myq.pop();
        inque[pf]=false;
        for(int p=myv[pf].first;p;p=mye[p].next)
        {
            pt=mye[p].to;
            if(myv[pt].wp>myv[pf].wp+mye[p].c&&mye[p].w>0)
            {
                myv[pt].wp=myv[pf].wp+mye[p].c;
                myv[pt].pre=p;
                if(!inque[pt])
                {
                    myq.push(pt);
                    inque[pt]=true;
                }
            }
        }
    }  
}
void mincostflow()
{
    int minw;
    while(true)
    {
        spfa();
        if(myv[n].wp==OO)return;
        minw=OO;
        for(int ie=myv[n].pre;;ie=myv[mye[ie].fr].pre)
        {
            //cout<<mye[ie].fr<<" ";
            minw=min(minw,mye[ie].w);
            if(mye[ie].fr==1)break;
        }
        //cout<<":"<<minw<<endl;
        tot+=myv[n].wp*minw;
        for(int ie=myv[n].pre;;ie=myv[mye[ie].fr].pre)
        {
            //cout<<mye[ie].fr<<endl;
            mye[ie].w-=minw;
            mye[ie^1].w+=minw;
            if(mye[ie].fr==1)break;
        }
    }
}
int nx,ny;
int map[17][17];
int pmap[17][17][2];
int tdx[5]={0,0,-1,0,1},
    tdy[5]={0,-1,0,1,0};
inline char readchar()
{
    char tc=0;
    while(tc!='U'&&tc!='D'&&tc!='L'&&tc!='R')tc=getchar();
    if(tc=='L')return 1;
    if(tc=='U')return 2;
    if(tc=='R')return 3;
    if(tc=='D')return 4;
}
int main()
{
    freopen("3171.in","r",stdin);
    freopen("3171.out","w",stdout);
    scanf("%d%d",&nx,&ny);
    n=1;
    for each(ix,nx)
    {
        for each(iy,ny)
        {
            map[ix][iy]=readchar();
            pmap[ix][iy][0]=++n;
            pmap[ix][iy][1]=++n;
            if(ix==1)
            {
                pmap[nx+1][iy][0]=pmap[1][iy][0];
                pmap[nx+1][iy][1]=pmap[1][iy][1];
            }
            if(iy==1)
            {
                pmap[ix][ny+1][0]=pmap[ix][1][0];
                pmap[ix][ny+1][1]=pmap[ix][1][1];
            }
            if(ix==nx)
            {
                pmap[0][iy][0]=pmap[nx][iy][0];
                pmap[0][iy][1]=pmap[nx][iy][1];
            }
            if(iy==ny)
            {
                pmap[ix][0][0]=pmap[ix][ny][0];
                pmap[ix][0][1]=pmap[ix][ny][1];
            }
                
        }
    }
    ++n;
    int tnx,tny;
    for each(ix,nx)
    {
        for each(iy,ny)
        {
            addedge(1,pmap[ix][iy][0],1,0);
            addedge(pmap[ix][iy][1],n,1,0);
            for each(idir,4)
            {
                tnx=ix+tdx[idir];tny=iy+tdy[idir];
                //cout<<ix<<","<<iy<<"->"<<tnx<<","<<tny<<endl;
                if(map[ix][iy]==idir)
                {
                    addedge(pmap[ix][iy][0],pmap[tnx][tny][1],1,0);
                }
                else addedge(pmap[ix][iy][0],pmap[tnx][tny][1],1,1);
            }
        }
    }
    mincostflow();
    cout<<tot<<endl;
}
