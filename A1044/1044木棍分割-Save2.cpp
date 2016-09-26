#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=n;++i)
int n,nm;
int dp [50001][1002];
int sdp[50001][1002];
int sum[50001];
int nl [50001];
int mintot=137228;
int main()
{
    freopen("1044.in","r",stdin);
    freopen("1044.out","w",stdout);
    scanf("%d%d",&n,&nm);
    for each(i,n)scanf("%d",&nl[i]);
    for each(i,n)sum[i]=sum[i-1]+nl[i];
    for each(i,n)dp[i][1]=(sum[i]<mintot);

    for each(k,nm+1)
    {
        for each(i,n)
        {
            if(i>=k)dp[i][k]+=dp[i][k-1];
            for each(Vi,i-1)
            {
                if(sum[i]-sum[Vi]<=mintot)
                dp[i][k]+=dp[Vi][k-1];
            }
            sdp[i][k]=sdp[i][k-1]+dp[i][k];
            cout<<"DP:"<<i<<","<<k<<":"<<dp[i][k]<<" ";
        }
        cout<<endl;
    }
}
