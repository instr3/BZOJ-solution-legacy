#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n,nk;
int tdp[1001];
long long getsum(int ibeg,int iinc,int ilen)
{
    if(ilen<0)return 0;
    return (2*ibeg+(iinc*(ilen-1LL)))*ilen/2;
}
long long calc(int in,int ik)
{
    long long res=0;
    for each(i,in)
    {
        res+=ik%i;
    }
    return res;
}
long long calc2(int n,int nk)
{
    long long tres=0;
    tres=tres+getsum(nk,0,n-nk);
    tres=tres+getsum(nk%(nk/2+1),-1,min(n,nk/1)-nk/2);
    tres=tres+getsum(nk%(nk/3+1),-2,min(n,nk/2)-nk/3);
    tres=tres+getsum(nk%(nk/4+1),-3,min(n,nk/3)-nk/4);
    tres=tres+getsum(nk%(nk/5+1),-4,min(n,nk/4)-nk/5);
    tres=tres+getsum(nk%(nk/6+1),-5,min(n,nk/5)-nk/6);
    tres=tres+getsum(nk%(nk/7+1),-6,min(n,nk/6)-nk/7);
    tres=tres+getsum(nk%(nk/8+1),-7,min(n,nk/7)-nk/8);
    tres=tres+getsum(nk%(nk/9+1),-8,min(n,nk/8)-nk/9);
    tres=tres+getsum(nk%(nk/10+1),-9,min(n,nk/9)-nk/10);
    tres=tres+calc(min(nk/10,n),nk);
    return tres;
}
int main()
{
    freopen("1257.in","r",stdin);
    freopen("1257.out","w",stdout);
    scanf("%d%d",&n,&nk);
    
    /*for each(i,n)
    {
        //cout<<i<<","<<nk<<":"<<nk%i<<endl;
        cout<<calc(i,nk)<<","<<calc2(i,nk)<<endl;
    }*/
    //cout<<calc(n,nk)<<","<<calc2(n,nk);
    cout<<calc2(n,nk);
}
