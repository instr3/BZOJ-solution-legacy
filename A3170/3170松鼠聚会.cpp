#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n;
struct zdpoint
{
    int x,y,n;
}ind[100001];
long long tget;
long long tdp[100001];
inline bool cmpx(zdpoint it1,zdpoint it2)
{
    return it1.x<it2.x;
}
inline bool cmpy(zdpoint it1,zdpoint it2)
{
    return it1.y<it2.y;
}

int main()
{
    freopen("3170.in","r",stdin);
    freopen("3170.out","w",stdout);
    scanf("%d",&n);
    int tx,ty;
    for each(i,n)
    {
        scanf("%d%d",&tx,&ty);
        ind[i].x=tx+ty;
        ind[i].y=tx-ty;
        ind[i].n=i;
    }
    sort(ind+1,ind+n+1,cmpx);
    for every(i,2,n)
    {
        tget+=(i-1)*((long long)ind[i].x-ind[i-1].x);
        tdp[ind[i].n]+=tget;
    }
    tget=0;
    for(int i=n-1;i;--i)
    {
        tget+=(n-i)*((long long)ind[i+1].x-ind[i].x);
        tdp[ind[i].n]+=tget;
    }
    tget=0;
    sort(ind+1,ind+n+1,cmpy);
    for every(i,2,n)
    {
        tget+=(i-1)*((long long)ind[i].y-ind[i-1].y);
        tdp[ind[i].n]+=tget;
    }
    tget=0;
    for(int i=n-1;i;--i)
    {
        tget+=(n-i)*((long long)ind[i+1].y-ind[i].y);
        tdp[ind[i].n]+=tget;
    }
    long long tot=888888888888888888LL;
    for each(i,n)
    {
        //cout<<tdp[i]<<endl;
        tot=min(tot,tdp[i]);
    }
    printf("%lld",tot/2);
}
