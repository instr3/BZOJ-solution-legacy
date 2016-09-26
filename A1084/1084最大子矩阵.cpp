#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
#define getm(var1,var2) (var1)=max((var1),(var2))
int indata[101][3];
//     len  use type
int dp[101][1111][5];
bool ispos[101][1111][5];
//0 1 2 3 4
//  =   = -
//    = = -
int main()
{
    freopen("1084.in","r",stdin);
    freopen("1084.out","w",stdout);
    int n,nm,nk;
    scanf("%d%d%d",&n,&nm,&nk);
    for each(i,n)
    for each(j,nm)
    scanf("%d",&indata[i][j]);
    dp[0][0][0]=0;
    if(nm==1)for each(i,n)indata[i][2]=-987654321;
    for each(i,n)dp[i][0][0]=0;
    for each(i,n)
    {
        for each(k,nk)
        {
            //无修改 
            dp[i][k][0]=dp[i-1][k][0];
            //延长前面的段
            getm(dp[i][k][1],dp[i-1][k][1]+indata[i][1]);
            getm(dp[i][k][2],dp[i-1][k][2]+indata[i][2]);
            getm(dp[i][k][3],dp[i-1][k][3]+indata[i][1]+indata[i][2]);
            getm(dp[i][k][4],dp[i-1][k][4]+indata[i][1]+indata[i][2]);
            //增加新段
            getm(dp[i][k][1],dp[i][k-1][0]+indata[i][1]);
            getm(dp[i][k][3],dp[i][k-1][2]+indata[i][1]);
            getm(dp[i][k][2],dp[i][k-1][0]+indata[i][2]);
            getm(dp[i][k][3],dp[i][k-1][1]+indata[i][2]);
    if(k>=2)getm(dp[i][k][3],dp[i][k-2][0]+indata[i][1]+indata[i][2]);
            getm(dp[i][k][4],dp[i][k-1][0]+indata[i][1]+indata[i][2]);
            
        }
        for each(k,nk)
        {
            //结束段
            getm(dp[i][k][0],dp[i][k][1]);
            getm(dp[i][k][0],dp[i][k][2]);
            getm(dp[i][k][0],dp[i][k][3]);
            getm(dp[i][k][0],dp[i][k][4]);
            getm(dp[i][k][1],dp[i][k][3]);
            getm(dp[i][k][2],dp[i][k][3]);
        }
    }
    cout<<dp[n][nk][0];
}
    
