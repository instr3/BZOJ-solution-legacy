#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define om(n) ((n)%10007)
int n,nm;
int  dp [2][50002];
int sdp [2][50002];
int sum [50001];
int       sptf[50001];
int       nl  [50001];
long long mintot=10;
int ptf,tlt,trt;
bool task(int tnum)
{
    int tct=0,tsum=0;
    for each(i,n)
    {
        tsum+=nl[i];
        if(tsum>tnum)
        {
            tct++;
            tsum=nl[i];
            if(tct>nm||tsum>tnum)return false;
        }
    }
    return true;
}
int main()
{
    freopen("1044.in","r",stdin);
    freopen("1044.out","w",stdout);
    scanf("%d%d",&n,&nm);
    for each(i,n)scanf("%d",&nl[i]);
    for each(i,n)sum[i]=sum[i-1]+nl[i];
    ptf=0;
    tlt=1,trt=sum[n]+1;
    while(tlt+1<trt)
    {
        ptf=(tlt+trt)/2-1;
        if(task(ptf))
        {
            trt=ptf+1;
        }
        else
        {
            tlt=ptf+1;
        }
    }mintot=ptf=tlt;
    cout<<ptf<<" ";
    //cout<<endl;
    //return 0;
    for each(i,n)
    {
        dp[1][i]=(sum[i]<=mintot);
        sdp[1][i]=(sdp[1][i-1]+dp[1][i])%10007;
        //cout<<"DP:"<<i<<","<<1<<":"<<dp[1][i]<<" ";
    }

    ptf=0;
    for each(i,n)
    {
        while(sum[i]-sum[ptf]>mintot&&ptf<=i)ptf++;
        sptf[i]=ptf;
    }
    long long tot=0;
    int tbk;
    for (int k=2;k<=nm+1;++k)
    {
        tbk=k&1;
        for (int i=1;i<=n;++i)
        {
            
            dp[tbk][i]=(sdp[tbk^1][i-1]+10007-sdp[tbk^1][sptf[i]-1])%10007;
            sdp[tbk][i]=(sdp[tbk][i-1]+dp[tbk][i])%10007;
            //cout<<"DP:"<<i<<","<<k<<":"<<dp[tbk][i]<<" ";
        }
        tot=om(tot+dp[tbk][n]);
        //cout<<endl;
    }
    cout<<tot<<endl;
}
