#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
struct enode{int to,next,w;}mye[2000002];
struct vnode{int first;}myv[1000001];
bool visit[1000001];
int tstk[1000001],pstk;
int n;
int tcv[1000001];int ptcv;
struct enode2{int to,w;}myne[1000001];
int tct[1000001];
int main()
{
    freopen("2435.in","r",stdin);
    freopen("2435.out","w",stdout);
    scanf("%d",&n);
    int pf,pt,pw;
    for(int i=1,j=1;i<n;++i)
    {
        scanf("%d%d%d",&pf,&pt,&pw);
        mye[++j].to=pt;
        mye[j].w=pw;
        mye[j].next=myv[pf].first;
        myv[pf].first=j;
        mye[++j].to=pf;
        mye[j].w=pw;
        mye[j].next=myv[pt].first;
        myv[pt].first=j;
    }
    tstk[++pstk]=1;
    tcv[1]=++ptcv;
    while(pstk)
    {
        pf=tstk[pstk--];
        visit[pf]=true;
        
        for(int p=myv[pf].first;p;p=mye[p].next)
        {
            pt=mye[p].to;
            if(visit[pt])continue;
            tcv[pt]=++ptcv;
            myne[ptcv]=(enode2){tcv[pf],mye[p].w};
            tstk[++pstk]=pt;
        }
    }
    long long res=0;
    for(int i=n;i;--i)
    {
        tct[i]++;
        res+=abs(2*tct[i]-n)*(long long)myne[i].w;
        tct[myne[i].to]+=tct[i];
    }
    printf("%lld",res);
        
}
