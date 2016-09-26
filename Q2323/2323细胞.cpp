#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define mod 1000000007
int fastdp(long long in)
{
    in-=1;
    int tout[2]={0,1};
    int tnout[2]={};
    int tmat[2][2]={0,1,1,1};
    int tnmat[2][2]={};
    while(in)
    {
        if(in%2)
        {
            for every(i,0,1)
            for every(k,0,1)
            {
                tnout[i]=(tnout[i]+tmat[i][k]*(long long)tout[k])%mod;
            }
            for every(i,0,1)
            {
                tout[i]=tnout[i];
                tnout[i]=0;
            }
        }
        in/=2;
        for every(i,0,1)
        for every(j,0,1)
        for every(k,0,1)
        {
            tnmat[i][j]=(tnmat[i][j]+tmat[i][k]*(long long)tmat[k][j])%mod;
        }
        for every(i,0,1)
        for every(j,0,1)
        {
            tmat[i][j]=tnmat[i][j];
            tnmat[i][j]=0;
        }
    }
    return tout[1];
}
int n;
int indigit[1001];
int tdp[1001];
long long tmod=mod*(long long)mod-1;
inline long long getdit(int fr,int to)
{
    unsigned long long res=0;
    for every(i,fr,to)
    {
        res=(res*10+indigit[i])%tmod;
    }
    return res;
}
int main()
{
    freopen("2323.in","r",stdin);
    freopen("2323.out","w",stdout);
    
    scanf("%d",&n);
    for each(i,n)
    {
        scanf("%1d",&indigit[i]);
        for every(j,0,i-1)
        {
            tdp[i]=tdp[i]+tdp[j]*getdit(j+1,i)
        dssddsdxdxdd
}
