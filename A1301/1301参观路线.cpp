#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
struct enode{int to,next;}mye[2000001];
struct vnode{int first;}myv[100001];
struct lnode
{
    int prev,next;
}myl[100002];
int myh[100001],pmyh;
bool visit[100001];
int n;
void dfs(int iv)
{
    printf("%d\n",iv);
    visit[iv]=true;
    //Unlink iv
    myl[myl[iv].prev].next=myl[iv].next;
    myl[myl[iv].next].prev=myl[iv].prev;
    int pt;
    pmyh=0;
    for(int p=myv[iv].first;p;p=mye[p].next)
    {
        pt=mye[p].to;
        myh[++pmyh]=pt;
        push_heap(myh+1,myh+pmyh+1,greater<int>());
    }
    //sort(myh+1,myh+pmyh+1);
    int ih=pmyh;
    for(pt=myl[0].next;pt<=n;pt=myl[pt].next)
    {
        if(ih>=0)
        do
        {
            pop_heap(myh+1,myh+ih+1,greater<int>());
            --ih;
        }while(ih>=0&&myh[ih+1]<pt);
        if(myh[ih+1]>pt||ih<0)
        {
            dfs(pt);
            return;
        }
    }
    return;
}
int main()
{
    freopen("1301.in","r",stdin);
    freopen("1301.out","w",stdout);
    int nm;scanf("%d%d",&n,&nm);
    int pf,pt;
    for(int i=1,j=0;i<=nm;++i)
    {
        scanf("%d%d",&pf,&pt);
        mye[++j].to=pt;
        mye[j].next=myv[pf].first;
        myv[pf].first=j;
        
        mye[++j].to=pf;
        mye[j].next=myv[pt].first;
        myv[pt].first=j;
    }
    
    for each(i,n)
    {
        myl[i].next=i+1;
        myl[i].prev=i-1;
    }
    myl[0].next=1;myl[n+1].prev=n;
    dfs(1);
}
