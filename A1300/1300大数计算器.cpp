#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
int na,nc,nb;
int twc;
long double res;
int nprime[100000],pnp;
bool ptable[1001001];
void preprime()
{
    memset(ptable,true,sizeof ptable);
    ptable[1]=false;
    for(int j=4;j<1001000;j+=2)ptable[j]=false;
    for(int i=3;i<1000;i+=2)
    {
        for(int j=i*i;j<1000000;j+=i)ptable[j]=false;
    }
    for each(i,1001000)
    {
        if(ptable[i])nprime[++pnp]=i;
    }
}
inline int getpcount(int ip,int inum)
{
    int tot=0;
    inum/=ip;
    while(inum)
    {
        tot+=inum;
        inum/=ip;
    }
    return tot;
}
inline int myexp(int ia,int ib)
{
    long long ans=1;
    long long iab=ia;
    while(ib)
    {
        if(ib%2)
        {
            ans=(ans*iab)%1000000000;
        }
        iab=(iab*iab)%1000000000;
        ib/=2;
    }
    return ans;
}
int getlastans()
{
    long long ans=1;
    int ip;
    int tpc=0;
    for(int i=1;nprime[i]<=na;++i)
    {
        ip=nprime[i];
        tpc=getpcount(ip,na)-getpcount(ip,nb)-getpcount(ip,nc);
        //for each(k,tpc)ans=(ans*ip)%1000000000;
        ans=(ans*myexp(ip,tpc))%1000000000;
    }
    return (int)ans;
} 
int gettop()
{
    twc=(int)log10l((double)res)+1;
    long double tres=res/powl(10,twc-3);
    return (int)tres;
}
int main()
{
    freopen("1300.in","r",stdin);
    freopen("1300.out","w",stdout);
    scanf("%d%d",&na,&nb);
    preprime();
    if(nb*2>na)nb=na-nb;
    long double t10=powl(10,10);
    nc=na-nb;
    int tlast=getlastans();
    res=1;
    for each(i,na)
    {
        res*=i;
        if(log10l((double)res)>10)
        {twc+=10;res/=t10;}
        //cout<<res<<endl;
    }
    for each(i,nb)
    {
        res/=i;
        if(log10l((double)res)<10)
        {twc-=10;res*=t10;}
        //cout<<res<<endl;
    }
    for each(i,nc)
    {
        res/=i;
        if(log10l((double)res)<10)
        {twc-=10;res*=t10;}
        //cout<<res<<endl;
    }
    twc+=(int)log10l((double)res)+1;
    if(twc<=12)
    {
        int tw=(int)log10l((double)res)+1;
        res=res/powl(10,tw)*powl(10,twc);
        cout<<(long long)res;
    }
    else
    cout<<gettop()<<"..."<<setw(9)<<setfill('0')<<getlastans();
}
