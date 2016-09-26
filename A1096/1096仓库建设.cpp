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
long long dix[1000011];
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
    myq[++pbk].x1=dix[n];myq[pbk].y1=dp[n]-pre[n]+sum[n]*dix[n];myq[pbk].n=n;
    
    long long tres,getans,tk,tm;
    for(int i=n-1;i>=0;--i)
    {
        tres=9223372036854775807LL;
        tk=sum[i];//ip[i+1];
        tm=ic[i]+pre[i];//ic[i]-ip[i+1]*ix[i+1];
        while(pfr<=pbk)
        {
            getans=myq[pfr].y1-tk*myq[pfr].x1+tm;
            //o/oi(i)ooi(getans)
            if(getans<=tres)
            {
                tres=getans;
            }
            else
            {
                break;
            }
            ++pfr;
        }
        --pfr;
        dp[i]=tres;
        //myq[++pbk].x1=-ix[i];myq[pbk].y1=dp[i];myq[pbk].n=i;
        myq[++pbk].x1=dix[i];myq[pbk].y1=dp[i]-pre[i]+sum[i]*dix[i];myq[pbk].n=i;
        //ooi(i);
        //for every(j,pfr,pbk)
        //{ooi(myq[j].n);ooi(myq[j].x1);ooi(myq[j].y1)}
        while(pbk-pfr>=2&&getk(pbk-2,pbk-1)>=getk(pbk-1,pbk))
        {
            myq[pbk-1]=myq[pbk];
            pbk--;
        }

    }
    printf("%lld",dp[0]);
}
