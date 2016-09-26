//Warning:Using %lld Input/Output
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
//#define os(x) ((x)*(x))
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,n1,n2) (int i=(n1);i<=(n2);++i)
#define ooi(sth) cout<<"Debug["<<__LINE__<<"]("#sth"):"<<sth<<endl;
int n;
struct qnode
{
    long long x1,y1;
    int n;
}myq[1000012];int pfr=1,pbk;
long long ix[1000011],ip[1000011],ic[1000011];
long long dp[1000011];
inline const long double getk(int in1,int in2)
{
    return ((long double)(myq[in2].y1-myq[in1].y1))/(myq[in2].x1-myq[in1].x1+1e-6);
}
long long pre[1000011],sum[1000011];
int dix[1000011];
int main()
{
    
    freopen("1096.in","r",stdin);
    freopen("1096.out","w",stdout);
    int n;
    scanf("%d",&n);
    for each(i,n)scanf("%lld%lld%lld",&ix[i],&ip[i],&ic[i]);
    
    for(int i=n;i>=0;--i)
    {
        sum[i-1]=sum[i]+ip[i];
        pre[i-1]=pre[i]+ip[i]*(ix[n]-ix[i]);
        dix[i]=ix[n]-ix[i];
    }
    
    dp[n]=ic[n];
    myq[++pbk].x1=-ix[n];myq[pbk].y1=dp[n];myq[pbk].n=n;
    
    //long long tres,getans,tk,tm;
    for(int i=n-1;i>=0;--i)
    {
        dp[i]=99999999;
        for(int j=n;j>i;--j)
        {
            dp[i]=min(dp[i],dp[j]+ic[i]+pre[i]-pre[j]-(sum[i]-sum[j])*dix[j]);
        }
    }
    printf("%lld",dp[0]);
}
