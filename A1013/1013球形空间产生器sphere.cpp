#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#define sqr(x) ((x)*(x))
using namespace std;
int n;
struct snode
{
    long double s[11];
    long double r;
}mys[11][11];
long double init[12][11];
long double res[11];
int main()
{
    freopen("1013.in","r",stdin);
    freopen("1013.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n+1;++i)
    {
        for(int j=1;j<=n;++j)
        {
            cin>>init[i][j];
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            mys[n][i].s[j]=2*(init[i+1][j]-init[i][j]);
            mys[n][i].r-=(sqr(init[i][j])-sqr(init[i+1][j]));
        }
    }
    for(int k=n;k>=2;--k)
    {
        for(int i=1;i<=k;++i)
        {
            for(int j=1;j<=k;++j)
            {
                mys[k-1][i].s[j]+=
                 mys[k][i].s[j]*mys[k][i+1].s[k]-
                  mys[k][i+1].s[j]*mys[k][i].s[k];
            }
            mys[k-1][i].r=mys[k][i].r*mys[k][i+1].s[k]-
             mys[k][i+1].r*mys[k][i].s[k];
        }
    }
    for(int k=1;k<=n;++k)
    {
        for(int j=1;j<k;++j)
        {
            mys[k][1].r-=mys[k][1].s[j]*res[j];
        }
        res[k]=mys[k][1].r/mys[k][1].s[k];
        printf("%.3f",(double)res[k]);
        if(k!=n)printf(" ");
    }
}
