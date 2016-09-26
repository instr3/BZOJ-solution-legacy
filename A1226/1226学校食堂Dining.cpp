#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int tdp[1002][256][16];
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
    /*ind[n].b=0;
    for(int i=n-1;i;--i)
    {
        ind[i].b=min(ind[i].b,ind[i+1].b+1);
    }*/
    memset(tdp,38,sizeof tdp);
    dp(1,0,-1)=0;
    int tb,tw;
    int tz;
    int tlim;
    for each(i,n)
    {
        tb=ind[i].b;
        tw=ind[i].w;
        for every(iz,0,nzs[7]-1)
        {
            if(getbit(iz,0))continue;
            for every(ipre,-8,7)
            {
                //if(dp(i,iz,ipre)!=dp(0,0,0))cout<<i<<","<<iz<<","<<ipre<<":"<<dp(i,iz,ipre)<<endl;
                tlim=tb;
                for every(ib,0,tb)
                {
                    if(ib>tlim)break;
                    if(getbit(iz,ib))continue;
                    tlim=min(tlim,ind[i+ib].b+ib);
                    tz=iz;
                    setbit(tz,ib);
                    
                    up(dp(i,tz,ib),dp(i,iz,ipre)+dist(ipre+i,ib+i));
                    //if(i==1)if(iz==6)cout<<tz<<"!!!"<<i<<","<<tz<<","<<ib<<":"<<dp(i,tz,ib)<<endl;
                }
            }
        }
        for every(iz,0,nzs[7]-1)
        {
            for every(ipre,-7,7)
            {
                if(!getbit(iz,0))continue;
                up(dp(i+1,(iz>>1),ipre-1),dp(i,iz,ipre));
                //if(i==1)if(iz==7)if(ipre==0)cout<<"@@@"<<i<<","<<iz<<","<<ipre<<":"<<dp(i+1,iz>>1,ipre-1)<<endl;
                
            }
        }
    }
    int tot=99999999;
    for every(ipre,-8,-1)
    {
        tot=min(tot,dp(n+1,0,ipre));
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
