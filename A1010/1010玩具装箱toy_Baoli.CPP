#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define os(x) ((x)*(x))
#define test(i,j) os(sum[(i)]-sum[(j)]+(i)-(j)-1-nl)
using namespace std;
int n,nl;
int nc[50001];
long long sum[50001];
long long dp[50001];
int minat[50001];
int main()
{
    freopen("1010.in","r",stdin);
    freopen("1010.out","w",stdout);
    scanf("%d%d",&n,&nl);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&nc[i]);
    }
    for(int i=1;i<=n;++i)
    {
        sum[i]=sum[i-1]+nc[i];
    }
    for(int i=1;i<=n;++i)
    {
        dp[i]=9999999999999999LL;
        for(int j=0;j<i;++j)
        {
            if(dp[i]>=dp[j]+test(i,j))
            {
                dp[i]=dp[j]+test(i,j);
                minat[i]=j;
            }
            //cout<<minat[i]<<" ";
        }
        //cout<<endl;
    }
    for(int i=1;i<=n;++i)
    cout<<dp[i]<<endl;
}

