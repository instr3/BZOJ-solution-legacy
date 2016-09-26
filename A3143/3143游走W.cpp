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
#define double long double
struct enode{int to,next;}mye[50002];
struct vnode{int first;}myv[501];
int n,nm,nm2;
queue<int> myq;
bool inq[50001];
double dist[50002];
double twe[25001];
inline bool update(int ie)
{
    int pf=mye[ie^1].to;
    if(pf==n)return 0;
    double res=0;
    int tcount=0;
    for(int p=myv[pf].first;p;p=mye[p].next)
    {
        res+=dist[p^1];
        tcount++;
    }
    if(pf==1)res+=1;
    res/=tcount;
    if(abs(dist[ie]-res)>=1e-6)
    {
        dist[ie]=res;
        return true;
    }
    dist[ie]=res;
    return false;
}
void spfa()
{
    int pt,pe;
    for every(p,2,nm2)
    {
        if(update(p))
        {
            myq.push(p);
            inq[p]=true;
        }
    }
    while(!myq.empty())
    {
        pe=myq.front();myq.pop();
        inq[pe]=false;
        pt=mye[pe].to;
        cout<<"V:"<<pe<<":"<<mye[pe^1].to<<","<<mye[pe].to<<":"<<dist[pe]<<endl;
        for(int p=myv[pt].first;p;p=mye[p].next)
        {
            if(update(p))
            {
                if(!inq[p])
                {
                    myq.push(p);
                    inq[p]=true;
                }
            }
        }
    }
}
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    scanf("%d%d",&n,&nm);
    int pf,pt;
    for(int i=1,j=1;i<=nm;++i)
    {
        scanf("%d%d",&pf,&pt);
        mye[++j].to=pt;
        mye[j].next=myv[pf].first;
        myv[pf].first=j;
        mye[++j].to=pf;
        mye[j].next=myv[pt].first;
        myv[pt].first=j;
    }
    nm2=nm*2+1;
    spfa();
    for each(i,nm)
    {
        twe[i]=dist[i*2]+dist[i*2+1];
        //cout<<dist[i*2]<<","<<dist[i*2+1]<<" ";
    }
    sort(twe+1,twe+nm+1);
    double res=0;
    for each(i,nm)
    {
        res=res+twe[i]*(nm-i+1);
    }
    printf("%.3f",(float)res);
    
}
        
