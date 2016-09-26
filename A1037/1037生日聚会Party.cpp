#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
//#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
int n1,n2,nk;
int tdp[152][152][22][22];
#define dp(a,b,c,d) (tdp[(a)][(b)][(c)][(d)])
#define MD 12345678
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    scanf("%d%d%d",&n1,&n2,&nk);
    dp(n1,n2,0,0)=1;
    for(int i1=n1;i1>=0;--i1)
    {
        for(int i2=n2;i2>=0;--i2)
        {
            for every(k1,0,nk)
            {
                for every(k2,0,nk)
                {
                    if(k1&&!k2)dp(i1,i2,k1,0)=(dp(i1,i2,k1,0)+dp(i1+1,i2,k1-1,0))%MD;
                    if(k2&&!k1)dp(i1,i2,0,k2)=(dp(i1,i2,0,k2)+dp(i1,i2+1,0,k2-1))%MD;
                    if(k1)dp(i1,i2,k1,k2)=(dp(i1,i2,k1,k2)+dp(i1+1,i2,k1-1,k2+1))%MD;
                    if(k2)dp(i1,i2,k1,k2)=(dp(i1,i2,k1,k2)+dp(i1,i2+1,k1+1,k2-1))%MD;
                    //cout<<i1<<","<<i2<<","<<k1<<","<<k2<<":"<<dp(i1,i2,k1,k2)<<endl; 
                }
            }
        }
    }
    long long tot=0;
    for every(k1,0,nk)
    {
        for every(k2,0,nk)
        {
            tot=(tot+dp(0,0,k1,k2))%MD;
        }
    }
    cout<<tot<<endl;
}
