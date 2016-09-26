#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n,nm;
struct enode{int to,w,next;}mye[200002];int pmye;
struct vnode{int first;}myv[100001];
inline void addedge(int pf,int pt,int pw)
{
    //cout<<"Adding:"<<pf<<","<<pt<<","<<pw<<endl;
    mye[++pmye].to=pt;
    mye[pmye].w=-pw;
    mye[pmye].next=myv[pf].first;myv[pf].first=pmye;
}
int dist[100001];
bool inq[100001];
queue<int>myq;
int tcount[100001];
inline void spfa()
{
    //memset(dist,1,sizeof dist);
    for each(i,n)
    {
        myq.push(i);
        inq[i]=true;
        dist[i]=1;
    }
    int pf,pt;
    while(!myq.empty())
    {
        pf=myq.front();myq.pop();
        //cout<<"Poping:"<<pf<<":"<<dist[pf]<<endl;
        inq[pf]=false;
        for(int p=myv[pf].first;p;p=mye[p].next)
        {
            pt=mye[p].to;
            if(dist[pt]<dist[pf]+mye[p].w)
            {
                dist[pt]=dist[pf]+mye[p].w;
                if(!inq[pt])
                {
                    myq.push(pt);
                    tcount[pt]++;
                    if(tcount[pt]>=n)
                    {
                        printf("-1");
                        exit(0);
                    }
                    inq[pt]=true;
                }
            }
        }
    }
    long long tot=0;
    for each(i,n)
    {
        tot+=dist[i];
    }
    printf("%lld",tot);
}

    
inline void die()
{
    printf("-1");
    exit(0);
}

int main()
{
    freopen("2330.in","r",stdin);
    freopen("2330.out","w",stdout);
    scanf("%d%d",&n,&nm);
    int top,pf,pt;
    for each(i,nm)
    {
        scanf("%d%d%d",&top,&pf,&pt);
        switch(top)
        {
            case 1:addedge(pf,pt,0);addedge(pt,pf,0);break;
            case 2:addedge(pf,pt,-1);if(pf==pt)die();break;
            case 5:addedge(pf,pt,0);break;
            case 4:addedge(pt,pf,-1);if(pf==pt)die();break;
            case 3:addedge(pt,pf,0);break;
            default:;
        }
    }
    spfa();
}
