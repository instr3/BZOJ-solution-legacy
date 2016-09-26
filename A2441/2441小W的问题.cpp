#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=n;++i)
#define MD 1000000007
int n;
struct inode1
{
    int x,y;
    int s;
    bool operator <(inode1 ano) const
    {
        return x==ano.x?(y>ano.y):(x<ano.x);
    }
}myi1[200001];
//Usage:  *
//       *   compare
struct inode2
{
    int x,y;
    int s;
    bool operator <(inode2 ano) const
    {
        return x==ano.x?(y<ano.y):(x<ano.x);
    }
}myi2[200001];
//Usage: *
//        *  compare


struct ttree
{
    int d[200001];
    int s[200001];
    #define lowbit(i) ((i)&-(i))
    inline void add(int ip,int iw)
    {
        s[ip]+=iw;
        while(ip<=n)
        {
            d[ip]=(d[ip]+iw)%MD;
            ip+=lowbit(ip);
        }
    }
    inline int sum(int ip)
    {
        int res=0;
        while(ip)
        {
            res=(res+d[ip])%MD;
            ip-=lowbit(ip);
        }
        return res;
    }
}dp1,dp2,dp3,dp4;
int tarr1[200001];
int tarr2[200001];
int tarr3[200001];
int tarr4[200001];
int tvar1,tvar2;
int tzip;
struct tnode
{
    int t;
    int ts;
    bool operator <(tnode ano)const
    {
        return t<ano.t;
    }
}ty[200001];
int tyt[200001];
int main()
{
    freopen("2441.in","r",stdin);
    freopen("2441.out","w",stdout);
    scanf("%d",&n);
    for each(i,n)
    {
        scanf("%d%d",&myi1[i].x,&myi1[i].y);
        
        ty[i].t=myi1[i].y;
        ty[i].ts=i;
        myi1[i].s=i;
    }
    sort(ty+1,ty+n+1);
    ty[0].t=-9;
    int ttyt=0;
    for each(i,n)
    {
        if(ty[i].t==ty[i-1].t)tyt[i]=ttyt;
        else tyt[i]=++ttyt;
        myi1[ty[i].ts].y=tyt[i];
        myi2[ty[i].ts].x=myi1[ty[i].ts].x;
        myi2[ty[i].ts].y=myi1[ty[i].ts].y;
        myi2[ty[i].ts].s=myi1[ty[i].ts].s;
    }
    sort(myi1+1,myi1+n+1);
    sort(myi2+1,myi2+n+1);

    tzip=0;
    int tsame=0;
    myi2[0].x=-9;
    myi1[n+1].x=-9;
    for(int i=1;i<=n;++i)
    {
        if(myi2[i].x==myi2[i-1].x)tsame++;else tsame=0;
        tvar1=(i-1-dp2.sum(myi2[i].y))%MD;
        tarr1[myi2[i].s]=(((long long)(i-tsame-1)*tvar1-(dp1.sum(n)-dp1.sum(myi2[i].y)))
         -((long long)tvar1*(tvar1-1))/2-tarr2[myi2[i].y])%MD;
        
        //cout<<myi2[i].y<<":"<<tarr1[i]<<endl;
        //cout<<i-tsame-1<<","<<tvar1<<";"<<(dp1.sum(n)-dp1.sum(myi2[i].y))<<","<<
        //((long long)tvar1*(tvar1-1))/2<<","<<tarr2[myi2[i].y]<<endl;
        dp1.add(myi2[i].y,i);
        dp2.add(myi2[i].y,1);
        tzip++;
        if(myi2[i].y==myi2[i+1].y&&myi2[i].x==myi2[i+1].x)continue;
        tarr2[myi2[i].y]=(tarr2[myi2[i].y]+(long long)tzip*tvar1)%MD;
        //cout<<myi2[i].y<<"::"<<tarr2[myi2[i].y]<<endl;
        tzip=0;
    }
    tzip=0;
    for(int i=n;i;--i)
    {
        if(myi1[i].x==myi1[i+1].x)tsame++;else tsame=0;
        tvar1=(n-i-dp4.sum(myi1[i].y))%MD;
        tarr3[myi1[i].s]=(((long long)(n-tsame-i)*tvar1-(dp3.sum(n)-dp3.sum(myi1[i].y)))
         -((long long)tvar1*(tvar1-1))/2-tarr4[myi1[i].y])%MD;
        //cout<<tarr3[i]<<endl;
        dp3.add(myi1[i].y,n-i+1);
        dp4.add(myi1[i].y,1);
        tzip++;
        if(myi1[i].y==myi1[i-1].y&&myi1[i].x==myi1[i-1].x)continue;
        tarr4[myi1[i].y]=(tarr4[myi1[i].y]+(long long)tzip*tvar1)%MD;
        tzip=0;
    }
    int tot=0;
    for each(i,n)
    {
        //cout<<tarr1[i]<<","<<tarr3[i]<<endl;
        tot=(tot+((long long)tarr1[i]*tarr3[i])%MD)%MD;
    }
    cout<<(tot+MD)%MD;
}
    
