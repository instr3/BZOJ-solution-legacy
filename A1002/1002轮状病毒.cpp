
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)

typedef int bignum[5000];
inline void dec0(bignum &a)
{
    while(a[0]&&!a[a[0]])a[0]--;
}
inline void add(bignum &a,bignum &b,bignum &c)
{
    memset(c,0,sizeof(c));
    c[0]=max(a[0],b[0])+1;
    for(int i=1;i<=c[0];++i)
    {
        c[i]+=a[i]+b[i];
        if(c[i]>=10)c[i]-=10,c[i+1]+=1;
    }
    dec0(c);
}
inline void sub(bignum &a,bignum &b,bignum &c)
{
    memset(c,0,sizeof(c));
    c[0]=max(a[0],b[0])+1;
    for(int i=1;i<=c[0];++i)
    {
        --c[i+1];c[i]+=10;
        c[i]+=a[i]-b[i];
        if(c[i]>=10)c[i]-=10,c[i+1]+=1;
    }
    dec0(c);
}
inline void mul(bignum &a,bignum &b,bignum &c)
{
    memset(c,0,sizeof(c));
    c[0]=a[0]+b[0];
    for(int i=1;i<=a[0];++i)
    for(int j=1;j<=a[0];++j)
    {
        c[i+j-1]+=a[i]*b[j];
        c[i+j]+=c[i+j-1]/10;
        c[i+j-1]%=10;
    }
    dec0(c);
}
inline void mul2(bignum &a,int b,bignum &c)
{
    memset(c,0,sizeof(c));
    c[0]=a[0]+6;
    for(int i=1;i<=a[0];++i)
    {
        c[i]+=a[i]*b;
        c[i+1]=c[i]/10;
        c[i]=c[i]%10;
    }
    dec0(c);
}
inline void print(bignum &a)
{
    for(int i=a[0];i>=1;--i)
    {
        printf("%d",a[i]);
    }
}
inline void tonum(string &s,bignum &a)
{
    memset(a,0,sizeof(a));
    a[0]=s.size();
    for(int i=1;i<=a[0];i++)
    {
        a[i]=s[a[0]-i]-'0';
    }
}
bignum tarr[100];
int main()
{
    //freopen("in","r",stdin);
    //freopen("out","w",stdout);
    /*string sa,sb;cin>>sa>>sb;
    bignum ta,tb,tc;
    tonum(sa,ta);
    tonum(sb,tb);
    sub(ta,tb,tc);
    print(tc);
    system("pause");
    return 0;*/
    int n;scanf("%d",&n);
    bignum tbig,tbig2;
    if(n%2)
    {
        tarr[1][1]=1;tarr[1][0]=1;
        tarr[2][1]=4;tarr[2][0]=1;
        for every(i,3,50)
        {
            mul2(tarr[i-1],3,tbig);
            sub(tbig,tarr[i-2],tarr[i]);
            //print(tarr[i]);cout<<endl;
        }
        mul(tarr[(n+1)/2],tarr[(n+1)/2],tbig);
        print(tbig);
    }
    else
    {
        tarr[1][1]=1;tarr[1][0]=1;
        tarr[2][1]=3;tarr[2][0]=1;
        for every(i,3,50)
        {
            mul2(tarr[i-1],3,tbig);
            sub(tbig,tarr[i-2],tarr[i]);
        }
        mul(tarr[(n)/2],tarr[(n)/2],tbig);
        mul2(tbig,5,tbig2);
        print(tbig2);
    }
    system("pause");
}
    
