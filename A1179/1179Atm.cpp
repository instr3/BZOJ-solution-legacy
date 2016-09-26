#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
struct enode{int fr,to,next;}mye[500001],myne[500001];
struct vnode{int first,bbar,money;}myv[500001],mynv[500001];
int n,nm;
int tstk[500001],pstk;
int dfn[500001],low[500001];
int tidex;
bool visit[500001];
bool instk[500001];
int tnewv[500001];
int pnv;
int tdp[500001];
int dfs(int iv)
{
    //cout<<iv<<","<<mynv[iv].bbar<<endl;
    if(tdp[iv]!=tdp[0])return tdp[iv];
    int pt,res=-1;
    for(int p=mynv[iv].first;p;p=myne[p].next)
    {
        pt=myne[p].to;
        //if(visit[pt]==true)continue;
        res=max(res,dfs(pt));
    }
    if(res==-1)
    {
        if(mynv[iv].bbar)
        {
            return tdp[iv]=mynv[iv].money;
        }
        else 
        {
            return tdp[iv]=-1;
        }
    }
    return tdp[iv]=mynv[iv].money+res;
}
void tarjan(int iv)
{
    visit[iv]=true;
    dfn[iv]=low[iv]=++tidex;
    tstk[++pstk]=iv;
    instk[iv]=true;
    int pt;
    for(int p=myv[iv].first;p;p=mye[p].next)
    {
        pt=mye[p].to;
        if(!visit[pt])
        {
            tarjan(pt);
            low[iv]=min(low[iv],low[pt]);
        }
        else if(instk[pt])
        {
            low[iv]=min(low[iv],dfn[pt]);
        }
    }
    if(low[iv]==dfn[iv])
    {
        //cout<<"Group:";
        ++pnv;
        while(tstk[pstk]!=iv)
        {
            //cout<<tstk[pstk]<<" ";
            tnewv[tstk[pstk]]=pnv;
            instk[tstk[pstk]]=false;
            if(myv[tstk[pstk]].bbar)mynv[pnv].bbar=true;
            mynv[pnv].money+=myv[tstk[pstk]].money;
            --pstk;
        }
        
        tnewv[iv]=pnv;--pstk;
        instk[iv]=false;
        if(myv[iv].bbar)mynv[pnv].bbar=true;
        mynv[pnv].money+=myv[iv].money;
        //cout<<iv<<":"<<mynv[pnv].bbar<<endl;
    }
}
int ist,nbar;
int main()
{
    freopen("1179.in","r",stdin);
    freopen("1179.out","w",stdout);
    memset(tdp,-2,sizeof tdp);
    scanf("%d%d",&n,&nm);
    int pf,pt;
    for each(i,nm)
    {
        scanf("%d%d",&pf,&pt);
        mye[i].fr=pf;
        mye[i].to=pt;
        mye[i].next=myv[pf].first;
        myv[pf].first=i;
    }
    for each(i,n)
    {
        scanf("%d",&myv[i].money);
    }
    scanf("%d%d",&ist,&nbar);
    for each(i,nbar)
    {
        scanf("%d",&pf);
        myv[pf].bbar=1;
    }
    for each(i,n)
    {
        if(!visit[i])tarjan(i);
    }
    for each(i,nm)
    {
        pf=tnewv[mye[i].fr];
        pt=tnewv[mye[i].to];
        if(pf==pt)continue;
        //cout<<"Add:"<<pf<<","<<pt<<endl;
        myne[i].to=pt;
        myne[i].next=mynv[pf].first;
        mynv[pf].first=i;
    }
    memset(visit,0,sizeof visit);
    printf("%d",dfs(tnewv[ist]));
}
