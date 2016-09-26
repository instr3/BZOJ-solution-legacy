#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n,nl,np;
char tc[32];
int inlen[100001];
long long dp[100001];
int minat[100001];
long long tw[100001];
long long tsum[100001];
inline long long mypow(long long ib,int ip)
{
    long long res=1;
    for each(i,ip)res=res*ib;
    return res;
}
void task()
{
    scanf("%d%d%d",&n,&nl,&np);
    memset(dp,38,sizeof dp);
    for each(i,n)
    {
        scanf("%s",&tc[0]);
        inlen[i]=strlen(tc);
        tw[i]=inlen[i];
        tsum[i]=tsum[i-1]+tw[i];
    }
    dp[0]=0;
    for each(i,n)
    {
        for every(k,0,i-1)
        {
            //cout<<i<<","<<dp[i]<<","<<dp[k]+mypow(tsum[i]-tsum[k]+i-k-1-nl,np)<<endl;
            if(dp[i]>=dp[k]+mypow(abs(tsum[i]-tsum[k]+i-k-1-nl),np))
            {
                dp[i]=dp[k]+mypow(abs(tsum[i]-tsum[k]+i-k-1-nl),np);
                minat[i]=k;
            }
            cout<<minat[i]<<" ";
        }
        cout<<endl;
    }
    cout<<dp[n]<<endl;
}
        
int main()
{
    freopen("1563.in","r",stdin);
    freopen("1563.out","w",stdout);
    task();
}
