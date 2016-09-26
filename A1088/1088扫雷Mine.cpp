#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
#define iif(statement,truepart,falsepart) ((statement)?(truepart):(falsepart))
//          this,prev
int dp[10002][2][2];
int indata[10001];
int main()
{
    //freopen("1088.in","r",stdin);
    //freopen("1088.out","w",stdout);
    int n;scanf("%d",&n);
    for each(i,n)scanf("%d",&indata[i]);
    dp[0][0][0]=1;
    dp[1][0][0]=1;
    dp[1][1][0]=1;
    for each(i,n)
    {
        switch(indata[i])
        {
            case 0:
                dp[i+1][0][0]=dp[i][0][0];break;
            case 1:
                dp[i+1][0][0]=dp[i][0][1];
                dp[i+1][0][1]=dp[i][1][0];
                dp[i+1][1][0]=dp[i][0][0];break;
            case 2:
                dp[i+1][1][1]=dp[i][1][0];
                dp[i+1][1][0]=dp[i][0][1];
                dp[i+1][0][1]=dp[i][1][1];break;
            case 3:
                dp[i+1][1][1]=dp[i][1][1];break;
        }
    }
    cout<<dp[n+1][0][0]+dp[n+1][0][1];
                
    system("pause");
}
