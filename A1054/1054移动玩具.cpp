#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
struct enode{int to,fr,c,f,w,next;}mye[200001];int pmye=1;
struct vnode{int first,pre;}myv[100001];
int dist[100001];
bool inque[100001];
int tot;
int n;
void addedge(int pf,int pt,int pc,int pw)
{
    //cout<<"Add:"<<pf<<","<<pt<<","<<pc<<","<<pw<<endl;
    mye[++pmye].fr=pf;
    mye[pmye].to=pt;
    mye[pmye].c=pc;
    mye[pmye].w=pw;
    mye[pmye].next=myv[pf].first;
    myv[pf].first=pmye;
    
    mye[++pmye].fr=pt;
    mye[pmye].to=pf;
    mye[pmye].c=0;
    mye[pmye].w=-pw;
    mye[pmye].next=myv[pt].first;
    myv[pt].first=pmye;
}
bool spfa()
{
    bool arrive=false;
    memset(dist,38,sizeof dist);
    memset(inque,0,sizeof inque);
    queue<int> myq;
    myq.push(1);
    inque[1]=true;
    dist[1]=0;
    int pf,pt;
    while(!myq.empty())
    {
        pf=myq.front();
        inque[pf]=false;
        myq.pop();
        for(int p=myv[pf].first;p;p=mye[p].next)
        {
            pt=mye[p].to;
            if(mye[p].c-mye[p].f<=0)continue;
            if(mye[p].w+dist[pf]<dist[pt])
            {
                dist[pt]=mye[p].w+dist[pf];
                myv[pt].pre=p;
                if(!inque[pt])
                {
                    myq.push(pt);
                    inque[pt]=true;
                    if(pt==n)arrive=true;
                }
            }
        }
    }
    return arrive;
}
void network()
{
    int minf;
    while(true)
    {
        if(!spfa())break;
        minf=99999999;
        for(int ie=myv[n].pre;;ie=myv[mye[ie].fr].pre)
        {
            //cout<<mye[ie].fr<<" ";
            minf=min(minf,mye[ie].c-mye[ie].f);
            if(mye[ie].fr==1)break;
        }
        //cout<<minf<<endl;
        for(int ie=myv[n].pre;;ie=myv[mye[ie].fr].pre)
        {
            mye[ie].f+=minf;
            mye[ie^1].f-=minf;
            tot+=minf*mye[ie].w;
            if(mye[ie].fr==1)break;
        }
    }
}
int i1data[5][5];int i2data[5][5];
int p1d[5][5],p2d[5][5];
int main()
{
    freopen("1054.in","r",stdin);
    freopen("1054.out","w",stdout);
    /*n=5;
    addedge(1,4,1,3);
    addedge(4,5,4,4);
    addedge(1,2,3,3);
    addedge(2,4,2,2);
    network();
    cout<<tot<<endl;*/
    n=1;
    char tc[6];
    for each(i,4)
    {
        scanf("%s",&tc[1]);
        for each(j,4)
        {
            i1data[i][j]=tc[j]=='1';
            p1d[i][j]=++n;
            if(i1data[i][j])addedge(1,p1d[i][j],1,0);
        }
    }
    ++n;
    for each(i,4)
    {
        scanf("%s",&tc[1]);
        for each(j,4)
        {
            i2data[i][j]=tc[j]=='1';
            if(i2data[i][j])addedge(p1d[i][j],n,1,0);
            if(i>1)addedge(p1d[i][j],p1d[i-1][j],99999999,1);
            if(j>1)addedge(p1d[i][j],p1d[i][j-1],99999999,1);
            if(i<4)addedge(p1d[i][j],p1d[i+1][j],99999999,1);
            if(j<4)addedge(p1d[i][j],p1d[i][j+1],99999999,1);
        }
    }
    network();
    cout<<tot<<endl;
}
