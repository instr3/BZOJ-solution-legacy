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
struct enode{int w,c,fr,to,next;}mye[1000000];int pmye=1;
struct vnode{int wp,pre,first;}myv[MAXN];int pmyv=1;
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
int pm[10][100],pn[100];
int it[10][100];
int main()
{
    freopen("1070.in","r",stdin);
    freopen("1070.out","w",stdout);
    int nn;
    scanf("%d%d",&nm,&nn);
    for each(i,nn)
    for each(j,nm)
    {
        scanf("%d",&it[j][i]);
    }
    for each(i,nn)
    {
        pn[i]=++pmyv;
        addedge(1,pn[i],1,0);
    }
    for each(i,nm)
    for each(j,nn)
    {
        pm[i][j]=++pmyv;
    }
    n=++pmyv;
    for each(i,nm)
    for each(j,nn)
    {
        addedge(pm[i][j],n,1,0);
    }
    for each(k,nn)
    {
        for each(i,nm)
        for each(j,nn)
        {
            addedge(pn[j],pm[i][k],1,it[i][j]*k);
        }
    }
    mincostflow();
    printf("%.2f",(double)tot/nn);
}
