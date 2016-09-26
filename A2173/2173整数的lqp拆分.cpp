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
int n;
int tf[1000001];
int tdp[1000001];
inline void getf()
{
    tf[1]=1;
    for every(i,2,n)
    {
        tf[i]=(tf[i-1]+tf[i-2])%mod;
    }
}
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    scanf("%d",&n);
    getf();
    tdp[1]=1;
    for every(i,2,n)
    {
        /*for each(j,i-1)
        {
            tdp[i]=(tdp[i]+tdp[j]*tf[i-j])%mod;
        }
        tdp[i]=(tdp[i]+tf[i])%mod;
        cout<<tdp[i]<<endl;*/
        tdp[i]=(tdp[i-1]*2LL+tdp[i-2])%mod;
        //cout<<tdp[i]<<endl;
    }
    cout<<tdp[n]<<endl;
}
