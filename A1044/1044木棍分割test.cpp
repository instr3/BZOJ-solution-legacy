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
char dp  [50001][1002],dp2 [1002][50001];
int sdp [50001][1002];
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
    /*for each(i,n)scanf("%d",&nl[i]);
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
    cout<<endl;
    //return 0;
    for each(i,n)dp[i][1]=(sum[i]<=mintot);

    ptf=0;
    for each(i,n)
    {
        while(sum[i]-sum[ptf]>mintot&&ptf<=i)ptf++;
        sptf[i]=ptf;
    }*/
    
    for each(k,nm+1)
    {
        for each(i,n)
        {
            //dp[i][k]=1;
            dp2[k][i]=1;
            //(dp[i][k]+sdp[i-1][k-1]+10007-sdp[sptf[i]-1][k-1])%10007;
            //sdp[i][k]=1;//(sdp[i-1][k]+dp[i][k])%10007;
            //cout<<"DP:"<<i<<","<<k<<":"<<dp[i][k]<<" ";
        }
        //cout<<endl;
    }
    long long tot=0;
    //for each(i,nm+1)tot=om(tot+dp[n][i]);
    cout<<tot;
}
