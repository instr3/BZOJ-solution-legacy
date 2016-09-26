#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(a) ((a)<0?-(a):(a))
int n;
long long tot=99999999999999LL,tres;
struct ck2dpoint
{
    int x,y;
}ind[10001];
int main()
{
    freopen("3170.in","r",stdin);
    freopen("3170.out","w",stdout);
    scanf("%d",&n);
    for each(i,n)
    {
        scanf("%d%d",&ind[i].x,&ind[i].y);
    }
    for each(i,n)
    {
        tres=0;
        for each(j,n)
        {
            tres=tres+max(abs(ind[i].x-ind[j].x),abs(ind[i].y-ind[j].y));
        }
        tot=min(tot,tres);
    }
    printf("%lld",tot);
}
