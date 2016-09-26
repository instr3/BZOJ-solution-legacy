#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define tlimit 1000000000000000000LL
int n,nl,np;
char tc[32];
int inlen[100001];
long double dp[100001];
int minat[100001];
long long tw[100001];
long long tsum[100001];
//long long ttv;
inline long double mypow(long double ib,int ip)
{
    if(ib==0)return 0;
    long double res=1;
    for each(i,ip)
    {
        res=res*ib;
    }
    return res;
}
inline long double mypow2(long long ib,int ip)
{
    if(ib==0)return 0;
    long double res=1;
    for each(i,ip)
    {
        res=res*ib;
    }
    return res;
}
struct tnode
{
    int lt,w;
}mys[100001];int pml=1,pmr;
void task()
{
    scanf("%d%d%d",&n,&nl,&np);
    memset(dp,38,sizeof dp);
    pml=1,pmr=0;
    
    for each(i,n)
    {
        scanf("%s",&tc[0]);
        inlen[i]=strlen(tc);
        tw[i]=inlen[i];
        tsum[i]=tsum[i-1]+tw[i];
    }
    dp[0]=0;
    mys[++pmr]=(tnode){1,0};
    int tl,tr,tm;
    #define getw(i,ik) (dp[(ik)]+mypow(abs(tsum[i]-tsum[(ik)]+(i)-(ik)-1-nl),np))
    //#define getw2(i,ik) (dp[(ik)]+mypow2(abs(tsum[i]-tsum[(ik)]+(i)-(ik)-1-nl),np))
    
    for each(i,n)
    {
        while(pml+1<=pmr&&mys[pml+1].lt<=i)pml++;
        int ik=mys[pml].w;
        dp[i]=getw(i,ik);
        //cout<<dp[i]<<":"<<ik<<endl;
        if(dp[i]>tlimit)
        {
            //cout<<"dead"<<endl;
            dp[i]=tlimit+1;
            continue; 
        }
        tl=i;
        while(pmr>=pml)
        {
            if(getw(mys[pmr].lt,i)<=getw(mys[pmr].lt,mys[pmr].w))
            {
                //cout<<"Removed:"<<mys[pmr].w<<endl;
                pmr--;
                continue;
            }
            tl=max(mys[pmr].lt,i);tr=n+1;
            while(tl+1!=tr)
            {
                //cout<<tl<<'#'<<tr<<endl;
                tm=(tl+tr)>>1;
                //cout<<getw(tm,i)<<","<<getw(tm,mys[pmr].w)<<endl;
                bool tb;
                //if(getw(tm,i)>tlimit and getw(tm,mys[pmr].w)>tlimit)
                //{
                //    tb=getw2(tm,i)>getw2(tm,mys[pmr].w)*0.999;
                //}
                /*else*/ tb=getw(tm,i)>getw(tm,mys[pmr].w);
                if(tb)
                {
                    tl=tm;
                }
                else
                {
                    tr=tm;
                }
            }
            break;
        }
        //cout<<"Add:"<<i<<"-"<<tl+1<<endl;
        if(tl<n)
        {
            mys[++pmr]=(tnode){tl+1,i};
            
        }
    }
    if(dp[n]>tlimit)
    {
        printf("Too hard to arrange\n");
        //printf("%I64d\n",dp[n]);
    }
    else
    {
        printf("%lld\n",(long long)dp[n]);
    }
}
        
int main()
{
    freopen("1563.in","r",stdin);
    freopen("1563.out","w",stdout);
    int nt;scanf("%d",&nt);
    for each(i,nt)
    {
        task();
        printf("--------------------\n");
    }
    
}
