#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n;
int nlog2;
int tdata[15];
int tot=0;
int tdp[1000001];
int mod;
long long exgcd(long long ia,long long ib)
{
    long long x0=1,y0=0,
              x1=0,y1=1,
              x2  ,y2  ;
    long long tr,tp;
    tr=ia%ib,tp=ia/ib;
    while(tr)
    {
        x2=x0-x1*tp;
        y2=y0-y1*tp;
        x0=x1;x1=x2;y0=y1;y1=y2;
        ia=ib;ib=tr;tr=ia%ib;tp=ia/ib;
    }
    return x1;
}
long long getanti(long long ia)
{
    return (((exgcd(ia,mod))%mod)+mod)%mod;
}
int calc(int in,int im)
{
    long long res=1;
    for every(i,in-im+1,in)res=(res*i)%mod;
    for each(i,im)res=(res*getanti(i))%mod;
    return res;
}
int getdp(int in)
{
    //cout<<"Testing:"<<in<<endl;
    if(tdp[in])return tdp[in];
    int tlog2,tbt,tup;
    tlog2=(int)floor(log2((double)in))+1;
    tbt=1<<(tlog2-2);
    tup=(1<<(tlog2-1))-1;
    //cout<<tbt<<","<<tup<<endl;
    if(in>=tbt+tup)
    {
        //cout<<"God"<<endl;
        return tdp[in]=((((long long)getdp(tup)*getdp(in-1-tup))%mod)*calc(in-1,in-1-tup))%mod;
    }
    else 
    {
        //cout<<"Dog"<<endl;
        return tdp[in]=((((long long)getdp(tup/2)*getdp(in-1-tup/2))%mod)*calc(in-1,tup/2))%mod;
    }
}
int main()
{
    freopen("2111.in","r",stdin);
    freopen("2111.out","w",stdout);
    mod=10007;
    tdp[1]=1;
    tdp[2]=1;
    scanf("%d",&n);
    scanf("%d",&mod);
    cout<<getdp(n)<<endl;
    /*for(int i=1;i<=n;i+=100)
    {
        cout<<i<<":"<<getdp(i)<<endl;
    }*/
    return 0;
    for each(i,n)tdata[i]=i;
    do
    {
        for every(i,2,n)
        {
            if(tdata[i]<tdata[i/2])goto die;
        }
        for each(i,n)cout<<tdata[i]<<" ";cout<<endl;
        tot++;
        die:;
    }while(next_permutation(tdata+2,tdata+n+1));
    cout<<tot<<endl;
}
