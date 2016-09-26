#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
struct enode{int to,next;}mye[2000002];
struct vnode{int first;}myv[10001];
int n,nm;
struct lnode{lnode *prev,*next;int iv,ic;};
lnode *tct[10001];
lnode *myp[10001];
lnode *tp;
bool visit[10001];
int tperfect[10001];
inline void tie(int iv,int ic)
{
    /*
    myl[++pmyl].prev=0;
    myl[pmyl].next=tct[ic];//first
    myl[myl[pmyl].next].prev=pmyl;
    tct[ic]=pmyl;
    myp[iv]=pmyl;*/
    tp=new lnode();
    tp->prev=0;
    tp->next=tct[ic];
    tp->iv=iv;
    tp->ic=ic;
    if(tp->next)tp->next->prev=tp;
    tct[ic]=tp;
    myp[iv]=tp;
}
inline void untie(int iv)
{
    /*
    int tpnode=myp[iv];
    myl[myl[tpnode].prev].next=myl[tpnode].next;
    myl[myl[tpnode].next].prev=myl[tpnode].prev;*/
    tp=myp[iv];
    myp[iv]=0;
    if(tp->next)tp->next->prev=tp->prev;
    if(tp->prev)tp->prev->next=tp->next;else tct[tp->ic]=tp->next;
    delete tp;
}
    
int main()
{
    freopen("1006.in","r",stdin);
    freopen("1006.out","w",stdout);
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
    for each(i,n-1)
    {
        tie(i,0);
    }
    int maxc=1,tv,tcount;
    tie(n,1);
    for each(k,n)
    {
        if(tct[maxc]==0)return 0;
        tv=tct[maxc]->iv;
        visit[tv]=true;
        tperfect[n-k+1]=tv;
        //cout<<tv<<endl;
        untie(tv);
        while(maxc>=0&&tct[maxc]==0)--maxc;
        for(int p=myv[tv].first;p;p=mye[p].next)
        {
            pt=mye[p].to;
            if(!visit[pt])
            {
                tcount=myp[pt]->ic;
                untie(pt);
                tie(pt,tcount+1);
                maxc=max(maxc,tcount+1);
            }
        }
    }
    memset(visit,0,sizeof visit);
    int tot=0,tres;
    for each(i,n)
    {
        tres=0;
        tv=tperfect[i];
        visit[tv]=true;
        for(int p=myv[tv].first;p;p=mye[p].next)
        {
            pt=mye[p].to;
            if(!visit[pt])
            {
                tres++;
            }
        }
        tot=max(tot,tres);
    }
    cout<<tot+1;
}
