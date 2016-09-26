#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
//#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
struct enode{int to,next;long double w;}mye[20002];
struct vnode{int first;long double dist;}myv[3001];
int n;
bool visit[3001];
bool dfs(int iv,long double iw)
{
    int pt;
    visit[iv]=true;
    for(int p=myv[iv].first;p;p=mye[p].next)
    {
        pt=mye[p].to;
        if(myv[pt].dist>myv[iv].dist+iw+mye[p].w)
        {
            if(visit[pt])return true;
            myv[pt].dist=myv[iv].dist+iw+mye[p].w;
            if(dfs(pt,iw))return true;
        }
    }
    visit[iv]=false;
    return false;
}
bool task(long double iw)
{
    for each(i,n)myv[i].dist=0;
    memset(visit,0,sizeof visit);
    for each(i,n)
    if(dfs(i,iw))return true;
    return false;
}
int main()
{
    freopen("1486.in","r",stdin);
    freopen("1486.out","w",stdout);
    int nm;
    scanf("%d%d",&n,&nm);
    int pf,pt;long long pw;
    for each(i,nm)
    {
        scanf("%d%d",&pf,&pt);
        cin>>pw;
        mye[i].to=pt;
        mye[i].w=pw;
        mye[i].next=myv[pf].first;
        myv[pf].first=i;
    }
    long double tl=-9e11,tr=9e11,tm;
    while(tr-tl>1e-9)
    {
        tm=(tl+tr)/2;
        if(task(tm))tl=tm;else tr=tm;
    }
    cout<<fixed<<setprecision(8)<<-tl<<endl;
}
