#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
/*solve 1/ia+1/ib=1/n!*/
#define mod 1000000007
int tprime[1000001];int ppri;
bool isprime[1000001];
int tcount[1000001];
inline void initprime()
{
    memset(isprime,1,sizeof isprime);
    isprime[1]=0;
    tprime[ppri=1]=2;
    for(int j=4;j<=1000000;j+=2)isprime[j]=false;
    for(int i=3;i<=1000000;i+=2)
    {
        if(isprime[i]==true)
        {
            tprime[++ppri]=i;
            for(int j=i*2;j<=1000000;j+=i)isprime[j]=false;
        }
    }
}
int n;
inline void calc(int iv)
{
    int sqrtiv=(int)sqrt(iv);
    int tp;
    for(int ip=1;tprime[ip]<=sqrtiv;++ip)
    {
        tp=tprime[ip];
        while(iv%tp==0)
        {
            tcount[tp]+=2;
            iv/=tp;
        }
    }
    if(iv>1)tcount[iv]+=2;

}
int main()
{
    freopen("2721.in","r",stdin);
    freopen("2721.out","w",stdout);
    scanf("%d",&n);
    initprime();
    for each(i,n)
    {
        calc(i);
    }
    int res=1;
    for each(i,n)
    {
        res=(((long long)res)*(tcount[i]+1))%mod;
    }
    printf("%d",res);
}
