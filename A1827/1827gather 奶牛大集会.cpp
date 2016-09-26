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
struct enode{int to,fr,w,next;long long tw,tper;}mye[200002];
struct vnode{int first,iper;long long tw,tper;}myv[100001];
bool visit[100001];
/*int test(int idp)
{
    long long myvar[4];
    
    if(idp%1000==0)cout<<idp<<endl;
    test(idp+1);
}*/
void dfs(int iv)
{
    visit[iv]=true;
    int pt,tp;
    for(int p=myv[iv].first;p;p=mye[p].next)
    {
        pt=mye[p].to;
        if(visit[pt]){tp=p;continue;}
        dfs(pt);
        //res+=dfs(pt);
        //res=res+mye[p].w*myv[pt].tp;
        //myv[iv].tp+=myv[pt].tp;
    }
    if(iv==1)return;
    //tp^=1;
    for(int p=myv[iv].first;p;p=mye[p].next)
    {
        if(tp==p)continue;
        mye[tp].tper+=mye[p^1].tper;
        mye[tp].tw+=mye[p^1].tw;
    }
    mye[tp].tper+=myv[iv].iper;
    mye[tp].tw+=mye[tp].tper*mye[tp].w;
    //cout<<tp<<":"<<mye[tp].fr<<"->"<<mye[tp].to<<":"<<mye[tp].tper<<","<<mye[tp].tw<<endl;
}
void dfs2(int iv)
{
    visit[iv]=true;
    int pt,tp;
    for(int p=myv[iv].first;p;p=mye[p].next)
    {
        myv[iv].tper+=mye[p^1].tper;
        myv[iv].tw+=mye[p^1].tw;
    }
    myv[iv].tper+=myv[iv].iper;
    //cout<<iv<<":"<<myv[iv].tper<<","<<myv[iv].tw<<endl;
    for(int p=myv[iv].first;p;p=mye[p].next)
    {
        pt=mye[p].to;
        if(visit[pt])continue;
        mye[p].tw=myv[iv].tw-mye[p^1].tw;
        mye[p].tper=myv[iv].tper-mye[p^1].tper;
        mye[p].tw+=mye[p].tper*mye[p].w;
        //cout<<iv<<"->"<<pt<<":"<<mye[p].tper<<","<<mye[p].tw<<endl;
        dfs2(pt);
    }

}
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    int n;scanf("%d",&n);
    for each(i,n)scanf("%d",&myv[i].iper);
    int pf,pt,pw;
    for(int i=1,j=1;i<n;++i)
    {
        scanf("%d%d%d",&pf,&pt,&pw);
        mye[++j].fr=pf;
        mye[j].to=pt;
        mye[j].w=pw;
        mye[j].next=myv[pf].first;
        myv[pf].first=j;
        mye[++j].fr=pt;
        mye[j].to=pf;
        mye[j].w=pw;
        mye[j].next=myv[pt].first;
        myv[pt].first=j;
    }
    dfs(1);
    memset(visit,0,sizeof visit);
    dfs2(1);
    long long tres,tmin=999999999999999LL;
    for each(i,n)
    {
        tres=0;
        for(int p=myv[i].first;p;p=mye[p].next)
        {
            tres+=mye[p^1].tw;
        }
        //cout<<i<<";"<<tres<<endl;
        tmin=min(tres,tmin);
    }
    printf("%lld",tmin);
}
