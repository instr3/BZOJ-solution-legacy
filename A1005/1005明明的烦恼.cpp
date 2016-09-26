#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
typedef int bignum[5000];
bignum ans;
inline void dec0(bignum &a)
{
    while(a[0]&&!a[a[0]])a[0]--;
}
inline void mul(bignum &a,int b)
{
    for(int i=1;i<=a[0];++i)a[i]*=b;
    a[0]+=5;
    for(int i=1;i<=a[0];++i)
    {
        a[i+1]+=a[i]/10;
        a[i]%=10;
    }
    dec0(a);
}
inline void div(bignum &a,int b)
{
    int r=0;
    for(int i=a[0];i>=1;--i)
    {
        r=r*10+a[i];
        a[i]=0;
        a[i]=r/b;
        r%=b;
    }
    dec0(a);
}
inline void print(bignum &a)
{
    for(int i=a[0];i>=1;--i)
    {
        printf("%d",a[i]);
    }
}
int data[1001];
int tot;
int main()
{
    freopen("1005.in","r",stdin);
    freopen("1005.out","w",stdout);
    int n;
    scanf("%d",&n);
    ans[0]=ans[1]=1;
    int tnc=n;
    for each(i,n)
    {
        scanf("%d",&data[i]);
        if(data[i]>0)
        {
            tot+=data[i]-1;
            tnc--;
        }
    }
    if(tot>n-2){printf("-1");return 0;}
    for each(i,tot)mul(ans,n-i-1);
    for(int i=tot+1;i<=n-2;++i)mul(ans,tnc);
    
    for each(i,n)
    {
        if(data[i]>0)
        {
            for each(j,data[i]-1)div(ans,j);
        }
    }
    print(ans);
    
}
