#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
typedef int bignum[301];
int n;
bignum res;
inline void dec0(bignum &ia)
{
    while(ia[0]&&!ia[ia[0]])--ia[0];
}
inline void add(bignum ia,bignum ib,bignum &ir)
{
    memset(ir,0,sizeof ir);
    ir[0]=max(ia[0],ib[0])+1;
    for each(i,ir[0])
    {
        ir[i]=ia[i]+ib[i];
        if(ir[i]>10)ir[i]-=10,ir[i+1]+=1;
    }
    dec0(ir);
}
inline void sadd(bignum ia,bignum &ir)
{
    ir[0]=max(ia[0],ir[0])+1;
    for each(i,ir[0])
    {
        ir[i]+=ia[i];
        if(ir[i]>10)ir[i]-=10,ir[i+1]+=1;
    }
    dec0(ir);
}
inline void mul(bignum ia,bignum ib,bignum &ir)
{
    memset(ir,0,sizeof ir);
    ir[0]=ia[0]+ib[0];
    for each(i,ia[0])
    for each(j,ib[0])
    {
        ir[i+j-1]+=ia[i]*ib[j];
    }
    for each(i,ir[0])
    {
        ir[i+1]+=ir[i]/10;
        ir[i]%=10;
    }
    dec0(ir);
}
inline void sdiv(bignum &ir,int in)
{
    int iy=0;
    for(int i=ir[0];i;--i)
    {
        iy=iy*10+ir[i];
        ir[i]=iy/in;
        iy%=in;
    }
    dec0(ir);
}
inline void smul(bignum &ir,int in)
{
    ir[0]+=4;
    for each(i,ir[0])ir[i]*=in;
    for each(i,ir[0])
    {
        ir[i+1]+=ir[i]/10;
        ir[i]%=10;
    }
    dec0(ir);
}
inline void print(bignum ia)
{
    for(int i=ia[0];i;i--)printf("%d",ia[i]);
    cout<<endl;
}
bignum tbig;
int main()
{
    freopen("2822.in","r",stdin);
    freopen("2822.out","w",stdout);
    scanf("%d",&n);
    res[0]=1;res[1]=1;
    
    
    for each(k,n)
    {
        smul(res,4*k-2);
        sdiv(res,k+1);
    }
    print(res);
}
