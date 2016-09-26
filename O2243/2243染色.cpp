#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define MAXV 10000
#define MAXE 200000
using namespace std;
struct enode{int to,next;}mye[MAXE];
struct vnode{int first,pos,top,dp;}myv[MAXV];
bool visit[MAXV];
int timpv[MAXV];
int indata[MAXV];
int invarr[MAXV],pinv;
int n,nm;
int dfs(int iv,int idp)
{
    visit[iv]=true;
    myv[iv].dp=idp;
    int tv,tans,tmax=0,tmaxat=0,ttot=0;
    for(int p=myv[iv].first;p;p=mye[p].next)
    {
        tv=mye[p].to;
        if(!visit[tv])
        {
            tans=dfs(tv,idp+1);
            ttot+=tans;
            if(tans>tmax)
            {
                tmax=tans;
                tmaxat=tv;
            }
        }
    }
    cout<<iv<<"->"<<tmaxat<<" is important!"<<endl;
    timpv[iv]=tmaxat;
    return ttot+1;
}
void dfs2(int iv,int itop)
{
    cout<<"Mking Arr:"<<iv<<endl;
    visit[iv]=false;
    myv[iv].pos=++pinv;
    myv[iv].top=itop;
    if(timpv[iv])
    {
        dfs2(timpv[iv],itop);
    }
    int tv;
    for(int p=myv[iv].first;p;p=mye[p].next)
    {
        tv=mye[p].to;
        if(!visit[tv]||tv==timpv[iv])continue;
        dfs2(tv,tv);
    }
}
void treeask(int ifr,int ito)
{
    while(true)
    {
    }
}
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    scanf("%d%d",&n,&nm);
    int pf,pt,pw;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&indata[i]);
    }
    for(int i=1,j=0;i<n;++i)
    {
        scanf("%d%d",&pf,&pt);
        mye[++j].to=pt;
        mye[j].next=myv[pf].first;
        myv[pf].first=j;
        mye[++j].to=pf;
        mye[j].next=myv[pt].first;
        myv[pt].first=j;
    }
    dfs(1,1);
    dfs2(1,1);
    char tc;
    for(int i=1;i<=nm;++i)
    {
        tc=0;
        while(tc!='Q'&&tc!='C'){tc=getchar();}
        if(tc=='Q')
        {
            scanf("%d%d",&pf,&pt);
            printf("%d\n",treeask(pf,pt));
        }
        else
        {
            scanf("%d%d%d",&pf,&pt,&pw);
            treecolor(pf,pt,pw);
        }
    }
}
