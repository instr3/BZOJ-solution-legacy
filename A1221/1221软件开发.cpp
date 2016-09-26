#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
struct enode{int to,fr,w,f,c,next;}mye[100001];int pmye=1;
struct vnode{int first,pre;}myv[10001];int n=1;
int testk[100001],pestk;
struct queue
{
    int d[100001];
    int front,back;
    inline void init(){front=1;back=0;}
    inline bool empty(){if(front!=0)return front==back+1;return back=100000-1;}
    inline void push(int in)
    {
        back++;if(back==100000)back=0;d[back]=in;
    }
    inline int pop()
    {
        int res=d[front];
        front++;if(front==100000)front=0;
        return res;
    }
}myq;bool inq[10001];
int dist[10001];
int tot;
int mintot=99999999;
inline void addedge(int pf,int pt,int pc,int pw)
{
    mye[++pmye].to=pt;
    mye[pmye].fr=pf;
    mye[pmye].c=pc;
    mye[pmye].w=pw;
    mye[pmye].f=0;
    mye[pmye].next=myv[pf].first;
    myv[pf].first=pmye;
    
    mye[++pmye].to=pf;
    mye[pmye].fr=pt;
    mye[pmye].c=0;
    mye[pmye].w=-pw;
    mye[pmye].f=0;
    mye[pmye].next=myv[pt].first;
    myv[pt].first=pmye;
    
}
bool spfa()
{
    memset(dist,38,sizeof dist);
    int pf=1,pt;
    myq.init();
    myq.push(pf);
    inq[pf]=true;
    dist[pf]=0;
    while(!myq.empty())
    {
        pf=myq.pop();
        inq[pf]=false;
        for(int p=myv[pf].first;p;p=mye[p].next)
        {
            pt=mye[p].to;
            if(mye[p].c-mye[p].f<=0)continue;
            if(dist[pt]>dist[pf]+mye[p].w)
            {
                dist[pt]=dist[pf]+mye[p].w;
                myv[pt].pre=p^1;
                if(!inq[pt])
                {
                    myq.push(pt);
                    inq[pt]=true;
                }
            }
        }
    }
    //cout<<"DIST:"<<dist[n]<<endl;
    return dist[n]!=640034342;
}
void mincostflow()
{
    int minw;
    while(true)
    {
        if(!spfa())return;
        minw=999999999;
        for(int p=myv[n].pre;p;p=myv[mye[p].to].pre)
        {
            //cout<<mye[p].to<<" ";
            minw=min(minw,mye[p^1].c-mye[p^1].f);
        }
        //cout<<":"<<minw<<endl;
        for(int p=myv[n].pre;p;p=myv[mye[p].to].pre)
        {
            mye[p].f-=minw;
            mye[p^1].f+=minw;
        }
        tot+=minw*dist[n];
        mintot=min(mintot,tot);
    }
}
int nn;
int nf,nf1,nf2;
int nd1,nd2;
int px[1001],py[1001];
int indata[1001];
int main()
{
    freopen("1221.in","r",stdin);
    freopen("1221.out","w",stdout);
    scanf("%d%d%d%d%d%d",&nn,&nd1,&nd2,&nf,&nf1,&nf2);
    n=1;
    int sum=0;
    for each(i,nn)
    {
        scanf("%d",&indata[i]);
        sum+=indata[i];
        px[i]=++n;
    }
    for each(i,nn)
    {
        py[i]=++n;
    }
    ++n;
    for each(i,nn-1)
    {
        addedge(py[i],py[i+1],99999999,0);
    }
    for each(i,nn)
    {
        addedge(1,py[i],indata[i],0);
        addedge(px[i],n,indata[i],0);
    }
    for each(i,nn)
    {
        if(i+nd1+1<=nn)addedge(py[i],px[i+nd1+1],99999999,nf1-nf);
        if(i+nd2+1<=nn)addedge(py[i],px[i+nd2+1],99999999,nf2-nf);
    }
    mincostflow();
    cout<<sum*nf+mintot<<endl;
}
