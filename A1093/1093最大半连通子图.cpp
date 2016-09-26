#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
struct enode{int to,fr,next;}myie[1000001],mye[1000001];int pmye;
struct vnode{int first;}myiv[100001],myv[100001];
int n,nm,nmod;
int dfn[100001],low[100001];
int tvstk[100001],pvstk;int tidex;
bool visit[100001],instk[100001];
int tnewv[100001];int nv;
int tfat[100001];
struct hashtable
{
    struct lnode{int ia,ib,next;}myl[1000001];int pmyl;
    struct hnode{int first;}myh[10000001];
    #define hmod 9999997
    inline void add(int ia,int ib)
    {
        int ih=((long long)ia*123456+ib)%hmod;
        myl[++pmyl].ia=ia;
        myl[pmyl].ib=ib;
        myl[pmyl].next=myh[ih].first;
        myh[ih].first=pmyl;
    }
    inline bool ask(int ia,int ib)
    {
        int ih=((long long)ia*123456+ib)%hmod;
        for(int p=myh[ih].first;p;p=myl[p].next)
        {
            if(myl[p].ia==ia&&myl[p].ib==ib)return true;
        }
        return false;
    }
}myh;
void tarjan(int iv)
{
    dfn[iv]=low[iv]=++tidex;
    tvstk[++pvstk]=iv;
    instk[iv]=true;
    visit[iv]=true;
    int pt;
    for(int p=myiv[iv].first;p;p=myie[p].next)
    {
        pt=myie[p].to;
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
    if(dfn[iv]==low[iv])
    {
        nv++;
        for(;tvstk[pvstk]!=iv;--pvstk)
        {
            //cout<<tvstk[pvstk]<<" ";
            tnewv[tvstk[pvstk]]=nv;
            instk[tvstk[pvstk]]=false;
            tfat[nv]++;
        }
        instk[iv]=false;
        tnewv[iv]=nv;
        tfat[nv]++;
        //cout<<tvstk[pvstk]<<"Died!"<<endl;
        
        --pvstk;
    }
}
int tlen[100001];

int dfs(int iv)
{
    //cout<<"Checking:"<<iv<<endl;
    if(tlen[iv])return tlen[iv];
    int res=0,pt;
    for(int p=myv[iv].first;p;p=mye[p].next)
    {
        pt=mye[p].to;
        res=max(res,dfs(pt));
    }
    return tlen[iv]=res+tfat[iv];
}
int tdp[100001];
int dfs2(int iv)
{
    if(tdp[iv])return tdp[iv];
    if(tlen[iv]==tfat[iv])return tdp[iv]=1;
    int res=0,pt;
    for(int p=myv[iv].first;p;p=mye[p].next)
    {
        pt=mye[p].to;
        if(tlen[pt]==tlen[iv]-tfat[iv])
        {
            res=(res+dfs2(pt))%nmod;
        }
    }
    return tdp[iv]=res;
}
int main()
{
    freopen("1093.in","r",stdin);
    freopen("1093.out","w",stdout);
    scanf("%d%d%d",&n,&nm,&nmod);
    int pf,pt;
    for each(i,nm)
    {
        scanf("%d%d",&pf,&pt);
        myie[i].to=pt;
        myie[i].fr=pf;
        myie[i].next=myiv[pf].first;myiv[pf].first=i;
    }
    for each(i,n)
    {
        if(!visit[i])
        tarjan(i);
    }
    for each(i,nm)
    {
        pf=tnewv[myie[i].fr];
        pt=tnewv[myie[i].to];
        if(pf==pt)continue;
        if(myh.ask(pf,pt))continue;
        myh.add(pf,pt);
        //cout<<"Add:"<<pf<<","<<pt<<endl;
        mye[++pmye].to=pt;
        mye[pmye].fr=pf;
        mye[pmye].next=myv[pf].first;
        myv[pf].first=pmye;
    }
    int tmax=0;
    for each(i,nv)
    {
        tmax=max(tmax,dfs(i));
        //cout<<i<<":"<<<<endl;
    }
    int res=0;
    for each(i,nv)
    {
        //cout<<i<<":"<<dfs2(i)<<endl;
        if(tlen[i]==tmax)res=(res+dfs2(i))%nmod;
    }
    printf("%d\n%d",tmax,res);
}
