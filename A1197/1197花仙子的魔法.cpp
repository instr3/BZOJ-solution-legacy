#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
long long dp[1001][1001];
int main()
{
    for each(nm,101)dp[0][nm]=2;
    dp[0][1]=1;
    for each(n,15)
    {
        dp[n][1]=1;
        for every(nm,2,101)
        {
            dp[n][nm]=dp[n][nm-1]+dp[n-1][nm-1];
        }
    }
    /*for each(n,15)
    {
        for each(nm,10)
        {
            cout<<dp[n][nm]<<" ";
        }
        cout<<endl;
    }*/
    int n,nm;
    scanf("%d%d",&nm,&n);
    printf("%lld",dp[n][nm+1]);
    system("pause");
}
        
