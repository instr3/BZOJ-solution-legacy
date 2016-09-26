#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
//#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
struct enode{int to,fr,next;int mk;}mye[100001];
struct vnode{int first;}myv[100001];
int n,nm;
int idex;
int dnf[100001];
int low[100001];
bool visit[100001];
int stk[100001];int pstk;
int tnewv[100001];
int tcn[100001];
void dfs(int iv)
{

    dnf[iv]=low[iv]=++idex;
    //cout<<iv<<":"<<idex<<endl;
    visit[iv]=true;
    int pt;
    for (int p=myv[iv].first;p;p=mye[p].next)
    {
        pt=mye[p].to;
        if(!visit[pt])
        {
            mye[p].mk=1;
            mye[p^1].mk=1;
            dfs(pt);
            low[iv]=min(low[iv],low[pt]);
        }
        else
        {
            if(!mye[p].mk)
            {
                low[iv]=min(low[iv],dnf[pt]);
            }
        }
    }
}
void dfs2(int iv)
{
    visit[iv]=true;
    tnewv[iv]=idex;
    int pt;
    for (int p=myv[iv].first;p;p=mye[p].next)
    {
        if(mye[p].mk==9)continue;
        pt=mye[p].to;
        if(!visit[pt])
        {
            dfs2(pt);
        }
    }
}
int main()
{
    freopen("1718.in","r",stdin);
    freopen("1718.out","w",stdout);
    scanf("%d%d",&n,&nm);
    int pf,pt;
    for(int i=1,j=1;i<=nm;++i)
    {
        scanf("%d%d",&pf,&pt);
        mye[++j].to=pt;
        mye[j].fr=pf;
        mye[j].next=myv[pf].first;
        myv[pf].first=j;
        mye[++j].to=pf;
        mye[j].fr=pt;
        mye[j].next=myv[pt].first;
        myv[pt].first=j;
    }
    dfs(1);
    for each(j,nm*2+1)
    {
        pf=mye[j].fr;
        pt=mye[j].to;
        if(mye[j].mk)
        {
            if(dnf[pf]<low[pt])
            {
                mye[j].mk=9;
                mye[j^1].mk=9;
                //cout<<pf<<"->"<<pt<<"Goto (9)"<<endl;
            }
        }
    }
    memset(visit,0,sizeof(visit));
    idex=0;
    for each(i,n)
    {
        if(!visit[i])
        {
            idex++;
            dfs2(i);
        }
    }
    for each(j,nm*2+1)
    {
        if(mye[j].mk==9)
        {
            //cout<<mye[j].to<<"->"<<tnewv[mye[j].to]<<"++"<<endl;
            tcn[tnewv[mye[j].to]]++;
        }
    }
    int tot=0;
    for each(i,idex)
    {
        if(tcn[i]==1)++tot;
        if(tcn[i]==0)tot+=2;
    }
    if(idex==1)cout<<0<<endl;else
    cout<<(tot+1)/2<<endl;
}
