#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define every2(i,a,b) (int i=(b);i>=(a);--i)
int tdp[1001][256][16];
#define dp(x,y,z) tdp[x][y][(z)+8]
#define up(x,y) (x)=min((x),(y))

#define getbit(iz,n) ((iz)&(1<<(n)))
#define setbit(iz,n) ((iz)^=(1<<(n)))
#define dist(a,b) ((a)==0?0:(ind[a].w^ind[b].w))
int n;
int nzs[8]={2,4,8,16,32,64,128,256};
struct cstudent
{
    int w,b;
}ind[1001];
void task()
{
    scanf("%d",&n);
    for each(i,n)
    {
        scanf("%d%d",&ind[i].w,&ind[i].b);
        ind[i].b=min(ind[i].b,n-i);
    }
    memset(tdp,38,sizeof tdp);
    dp(1,nzs[ind[1].b]-1,-1)=0;
    int tb,tw;
    int tz;
    for each(i,n)
    {
        tb=ind[i].b;
        tw=ind[i].w;
        for every2(iz,0,nzs[7]-1)
        {
            //if(!getbit(iz,0))continue;
            for every(ipre,-8,7)
            {
                if(dp(i,iz,ipre)!=dp(0,0,0))cout<<i<<","<<iz<<","<<ipre<<":"<<dp(i,iz,ipre)<<endl;
                for every(ib,0,tb)
                {
                    if(!getbit(iz,ib))continue;
                    tz=iz;
                    setbit(tz,ib);
                    
                    up(dp(i,tz,ib),dp(i,iz,ipre)+dist(ipre+i,ib+i));
                    //if(i==1)if(iz==6)cout<<tz<<"!!!"<<i<<","<<tz<<","<<ib<<":"<<dp(i,tz,ib)<<endl;
                }
            }
        }
        /*if(ind[i+1].b>=ind[i].b-1)
        {
            for every(iz,0,nzs[tb]-1)
            {
                for every(ipre,-7,7)
                {
                    if(getbit(iz,0))continue;
                    //cout<<ind[i+1].b<<","<<ind[i].b<<"!!!"<<nzs[ind[i+1].b]-(nzs[ind[i].b]>>1)<<endl;
                    up(dp(i+1,(iz>>1)+nzs[ind[i+1].b]-(nzs[ind[i].b]>>1),ipre-1),dp(i,iz,ipre));
                }
            }
        }
        else
        {
            for every(iz,0,nzs[tb]-1)
            {
                for every(ipre,-7,7)
                {
                    if(getbit(iz,0))continue;
                    up(dp(i+1,(iz>>1),ipre-1),dp(i,iz,ipre));
                }
            }
        }*/
        for every(iz,0,nzs[7]-1)
        {
            for every(ipre,-7,7)
            {
                if(getbit(iz,0))continue;
                up(dp(i+1,(iz>>1),ipre-1),dp(i,iz,ipre));
            }
        }
    }
    int tot=99999999;
    for every(ipre,-8,0)
    {
        tot=min(tot,dp(n,0,ipre));
    }
    printf("%d\n",tot);
}
int main()
{
    freopen("1226.in","r",stdin);
    freopen("1226.out","w",stdout);
    int nt;scanf("%d",&nt);
    while(nt--)task();
}
