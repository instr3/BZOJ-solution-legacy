#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
struct enode{int to,w,next;}mye[400002];
struct vnode{int first;}myv[200001];
int n;
bool visit[200001];
long long tcmax=999999999999999LL;int tcat;
long long alllen;
long long dist[200001];

long long tmaxfi=-1,tmaxse=-1,tmaxrd=-1;
long long tmaxatfi,tmaxatse;
long long dfs(int iv)
{
    visit[iv]=true;
    int pt;
    long long trem=0,tget,tmax=0;
    for(int p=myv[iv].first;p;p=mye[p].next)
    {
        pt=mye[p].to;
        if(!visit[pt])
        {
            tget=dfs(pt)+mye[p].w;
            if(tget>tmax)tmax=tget;
            trem+=tget;
        }
    }
    tmax=max(tmax,alllen-trem);
    if(tmax<tcmax)
    {
        tcmax=tmax;
        tcat=iv;
    }
    return trem;
}
long long dfs2(int iv)
{
    int pt;
    visit[iv]=true;
    long long tres=0;
    for(int p=myv[iv].first;p;p=mye[p].next)
    {
        pt=mye[p].to;
        if(!visit[pt])
        {
            dist[pt]=dist[iv]+mye[p].w;
            tres=max(tres,dfs2(pt));
        }
    }
    return max(tres,dist[iv]);
}
long long ttarget;
int tdie[200001];
bool dfs3(int iv)
{
    visit[iv]=true;
    int pt;
    for(int p=myv[iv].first;p;p=mye[p].next)
    {
        pt=mye[p].to;
        if(!visit[pt])
        {
            if(dfs3(pt))tdie[iv]++;
        }
    }
    return tdie[iv] or dist[iv]==ttarget;
}
int dfs4(int iv)
{
    if(tdie[iv]!=1)return 0;
    visit[iv]=true;
    int pt;
    int tcount=0;
    for(int p=myv[iv].first;p;p=mye[p].next)
    {
        pt=mye[p].to;
        if(!visit[pt])
        {
            tcount+=dfs4(pt);
        }
    }
    return tcount+1;
}
int main()
{
    freopen("3124.in","r",stdin);
    freopen("3124.out","w",stdout);
    scanf("%d",&n);
    int pf,pt,pw;
    for(int i=1,j=1;i<n;++i)
    {
        scanf("%d%d%d",&pf,&pt,&pw);
        mye[++j].to=pt;
        mye[j].w=pw;
        mye[j].next=myv[pf].first;myv[pf].first=j;
        mye[++j].to=pf;
        mye[j].w=pw;
        mye[j].next=myv[pt].first;myv[pt].first=j;
        alllen+=pw;
    }
    dfs(1);
    memset(visit,0,sizeof visit);
    long long tget;
    visit[tcat]=true;
    for(int p=myv[tcat].first;p;p=mye[p].next)
    {
        dist[mye[p].to]=mye[p].w;
        tget=dfs2(mye[p].to);
        //cout<<tget<<endl;
        if(tget>tmaxfi)
        {
            tmaxrd=tmaxse;
            tmaxse=tmaxfi;
            tmaxatse=tmaxatfi;
            tmaxfi=tget;
            tmaxatfi=mye[p].to;
        }
        else if(tget>tmaxse)
        {
            tmaxrd=tmaxse;
            tmaxse=tget;
            tmaxatse=mye[p].to;
        }
        else if(tget>tmaxrd)
        {
            tmaxrd=tget;
        }
    }
    //for each(i,n)cout<<dist[i]<<" ";
    //cout<<tmaxfi<<","<<tmaxse<<","<<tmaxrd<<endl;
    memset(visit,0,sizeof visit);
    visit[tcat]=true;
    int tot=0;
    if(tmaxrd!=tmaxse)
    {
        ttarget=tmaxse;
        dfs3(tmaxatse);
        ttarget=tmaxfi;
        dfs3(tmaxatfi);
        memset(visit,0,sizeof visit);
        visit[tcat]=true;
        tot+=dfs4(tmaxatse)+1;
        tot+=dfs4(tmaxatfi)+1;
        
    }
    else if(tmaxfi!=tmaxse)
    {
        ttarget=tmaxfi;
        dfs3(tmaxatfi);
        memset(visit,0,sizeof visit);
        visit[tcat]=true;
        tot+=dfs4(tmaxatfi)+1;
    }
    cout<<tmaxfi+tmaxse<<endl<<tot;
}
