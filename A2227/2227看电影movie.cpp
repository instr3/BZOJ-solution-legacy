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
double res;
int tprime[48]=
{0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,199999999};
int pprime=46;
int tmularr[48];
//int isprime[206];
typedef int bignum[1001];
inline void dec0(bignum &ir)
{
    while(ir[0]&&ir[ir[0]]==0)--ir[0];
}
inline void smul(bignum &ir,int ib)
{
    for each(i,ir[0])
    {
        ir[i]*=ib;
    }
    ir[0]+=8;
    for each(i,ir[0])
    {
        ir[i+1]+=ir[i]/10;
        ir[i]%=10;
    }
    dec0(ir);
}
inline void print(bignum ia)
{
    for(int i=ia[0];i;--i)printf("%d",ia[i]);
}
/*void getprime()
{
    memset(isprime,1,sizeof isprime);
    for every(i,2,205)
    {
        if(isprime[i])
        {
            for(int j=i*i;j<=205;j+=i)isprime[j]=false;
            cout<<i<<",";
        }
    }
    for each(i,pprime)isprime[tprime[i]]=true;
}*/
inline void mulprime(int in)
{
    int ip;
    for each(i,pprime)
    {
        ip=tprime[i];
        while(in%ip==0)
        {
            in/=ip;
            tmularr[i]++;
        }
        if(in==1)break;
    }
}
inline void divprime(int in)
{
    int ip;
    for each(i,pprime)
    {
        ip=tprime[i];
        while(in%ip==0)
        {
            in/=ip;
            tmularr[i]--;
        }
        if(in==1)break;
    }
}
void task()
{
    scanf("%d%d",&n,&nk);
    //res=(nk-n+1)*pow(nk+1,n-1.0)/pow(nk,(double)n);
    //cout<<res<<endl;
    if(n>nk){printf("0 1\n");return;}
    memset(tmularr,0,sizeof tmularr);
    for each(i,n-1)mulprime(nk+1);
    for each(i,n)divprime(nk);
    mulprime(nk-n+1);
    bignum tr1={},tr2={};
    tr1[0]=tr1[1]=tr2[0]=tr2[1]=1;
    for each(i,pprime)
    {
        //cout<<tprime[i]<<":"<<tmularr[i]<<endl;
        if(tmularr[i]>0)
        {
            for each(j,tmularr[i])
            {
                smul(tr1,tprime[i]);
            }
        }
        else if (tmularr[i]<0)
        {
            for each(j,-tmularr[i])
            {
                smul(tr2,tprime[i]);
            }
        }
    }
    print(tr1);printf(" ");print(tr2);printf("\n");
}
int main()
{
    freopen("2227.in","r",stdin);
    freopen("2227.out","w",stdout);
    int nt;scanf("%d",&nt);
    for each(i,nt)task();
}
