#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
bool isprime[44723];
int nprime[44723];int pprime;
int tsfu[1000001];
int fu(int in)
{
    cout<<in<<endl;
    if(tsfu[in]!=tsfu[0])return tsfu[in];
    int res=1;
    for each(ip,pprime)
    {
        if(in%nprime[ip]==0)
        {
            res=-res;
            in/=nprime[ip];
        }
        if(in%nprime[ip]==0)return tsfu[in]=0;
        if(in<nprime[ip])break;
    }
    if(in!=1)res=-res;
    return tsfu[in]=res;
}
inline void getprime()
{
    memset(isprime,1,sizeof isprime);
    
    int np=44722;
    for each(i,np)tsfu[i]=1;
    for every(i,2,np)
    {
        if(!isprime[i])
        {
            continue;
        }
        nprime[++pprime]=i;
        tsfu[i]=-1;
        for(int j=i*2;j<=np;j+=i)
        {
            isprime[j]=false;
            tsfu[j]=-tsfu[j];
            if((j/i)%i==0)tsfu[j]=0;
        }
    }
}
int fcount(int in)
{
    int sqrtn=(int)sqrt(in);
    long long res=0;
    for each(i,sqrtn)
    {
        //if(in%i==0)
        {
            res+=tsfu[i]*in/(i*(long long)i);
        }
    }
    
    return res;
}
void task()
{
    int n;
    scanf("%d",&n);
    unsigned int tl=1,tr=2000000000,tm;
    while(tl+1!=tr)
    {
        tm=(tl+tr)>>1;
        if(fcount(tm-1)<n)
        {
            tl=tm;
        }
        else
        {
            tr=tm;
        }
    }
    printf("%d\n",tl);
}
int main()
{
    freopen("2440.in","r",stdin);
    freopen("2440.out","w",stdout);
    memset(tsfu,3,sizeof tsfu);
    getprime();
    //for every(i,1000000000,1000000010)cout<<fu(i)<<endl;
    //cout<<fcount(1000000);
    int nt;scanf("%d",&nt);
    for each(i,nt)task();
    //for each(i,30)cout<<tsfu[i]<<endl;
}
