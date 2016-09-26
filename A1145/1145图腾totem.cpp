#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
#define MD 16777216
int n;
int iny[200001];
#define ad(a,b) (a)=((a)+(b))%MD
struct ttree
{
    //int n;
    int d[200001];
    int s[200001];
    //ttree(int in){n=in;}
    #define lowbit(i) ((i)&-(i))
    inline void add(int ip,int iw)
    {
        ad(s[ip],iw);
        while(ip<=n)
        {
            ad(d[ip],iw);
            ip+=lowbit(ip);
        }
    }
    inline void set(int ip,int iw)
    {
        add(ip,iw-s[ip]);
    }
    inline int sum(int ip)
    {
        int res=0;
        while(ip)
        {
            ad(res,d[ip]);
            ip-=lowbit(ip);
        }
        return res;
    }
    #undef lowbit
}dp1,dp2,dp3,dp4,//dpn[i]：构成n段上升序列，第i个位置的方法 
dpd1,//dpd,
dpw1,dpw2;//dpw;
int tcarr[200001][5];
void getcarr()
{
    tcarr[1][1]=1;
    int tlj;
    for every(i,2,n)
    {
        tlj=min(i,4);
        for each(j,tlj)
        {
            tcarr[i][j]=(tcarr[i-1][j]+tcarr[i-1][j-1])%MD;
        }
    }
}
#define C(i,j) (tcarr[(i)+1][(j)+1])
int tarr1[200001],tarr2[200001];
int main()
{
    freopen("1145.in","r",stdin);
    freopen("1145.out","w",stdout);
    scanf("%d",&n);
    getcarr();
    int r1234=0,r1___=0,r13__=0,r1_2_=0;
    for each(i,n)
    {
        scanf("%d",&iny[i]);
    }
    for each(i,n)
    {
        dp4.set(iny[i],dp3.sum(iny[i]-1));
        dp3.set(iny[i],dp2.sum(iny[i]-1));
        dp2.set(iny[i],dp1.sum(iny[i]-1));
        dp1.set(iny[i],1);
        ad(r1___,C(n-iny[i]-i+dp1.sum(iny[i]),3));
        tarr1[i]=(n-iny[i]-i+dp1.sum(iny[i]))%MD;
        tarr2[i]=C(iny[i]-dp1.sum(iny[i]),2)%MD;

    }
    r1234=dp4.sum(n);
    for (int i=n;i;--i)
    {
        //dpd.set(iny[i],dpd1.sum(iny[i]-1));
        ad(r13__,((long long)tarr1[i]*(dpd1.sum(iny[i]-1)-tarr2[i]))%MD);
        //cout<<tarr1[i]<<","<<dpd1.sum(iny[i])<<","<<tarr2[i]<<endl;
        dpd1.set(iny[i],iny[i]-1);
    }
    for each(i,n)
    {
        //dpw.set(iny[i],(i-1)*dpw1.sum(iny[i]-1)-dpw2.sum(iny[i]-1));
        ad(r1_2_,((long long)tarr1[i]*((i-1)*dpw1.sum(iny[i]-1)-dpw2.sum(iny[i]-1)-
         C(dpw1.sum(iny[i]-1),2)))%MD);
        //cout<<tarr1[i]<<","<<(i-1)*dpw1.sum(iny[i]-1)<<":"<<dpw2.sum(iny[i]-1)<<","<<
         //dpw1.sum(iny[i]-1)<<endl;
         
        dpw1.set(iny[i],1);
        dpw2.set(iny[i],i);
    }
    //cout<<r1234<<","<<r1___<<","<<r13__<<","<<r1_2_<<endl;
    cout<<(((r1_2_+r1234+r13__-r1___)%MD)+MD)%MD;
}
