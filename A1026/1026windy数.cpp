#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define getdp(j,i) (((i)<0||(i)>9)?0:dp[j][i])
int dp[11][10];
int dpsum[11];
int m10[11]={0,1,10,100,1000,10000,100000,1000000,10000000,
 100000000,1000000000};
int getans(int inum)
{
    int tw;
    for(int i=10;i>=1;--i)
    {
        tw=inum%m10[i];
        inum-=tw*m10[i];
        
    }
int main()
{
    freopen("1026.in","r",stdin);
    freopen("1026.out","w",stdout);
    for(int i=0;i<=9;++i)dp[1][i]=1;
    dpsum[1]=10;
    for(int j=2;j<=10;++j)
    {
        for(int i=0;i<=9;++i)
        {
            dp[j][i]=dpsum[j-1]-
             getdp(j-1,i-1)-getdp(j-1,i)-getdp(j-1,i+1);
            dpsum[j]+=dp[j][i];
        }
    }
    cout<<getans(50)<<endl;
}
