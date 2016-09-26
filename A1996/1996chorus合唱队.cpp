#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
int n;
#define mod 19650827
int idata[1001];
int tdata[1001];
int tarr[1001];
int tdp[1001][1001][2];
void test()
{
    for each(i,n)tdata[i]=idata[i];
    int tot=0;
    do
    {
        tarr[1]=tdata[1];
        for every(i,2,n)
        {
            
            if(tdata[i]>tdata[i-1])
            {
                tarr[i]=tdata[i];
            }
            else
            {
                for(int k=i-1;k>=1;--k)tarr[k+1]=tarr[k];
                tarr[1]=tdata[i];
            }
        }
        //for each(i,n)cout<<tdata[i]<<" ";cout<<":";
        //for each(i,n)cout<<tarr[i]<<" ";cout<<endl;
        for each(i,n)if(idata[i]!=tarr[i])goto die;
        for each(i,n)cout<<tdata[i]<<" ";cout<<endl;
        tot++;
        die:;
    }while(next_permutation(tdata+1,tdata+n+1));
    cout<<"Total:"<<tot<<endl;
}
int getdp(int tl,int tr,bool tb)//tb=0:Left-In 
{
    if(tdp[tl][tr][tb]!=-1)return tdp[tl][tr][tb];
    if(tl==tr and tb==1)return 1;
    int tot=0;
    if(tb)
    {
        if(idata[tr-1]<idata[tr])tot=(tot+getdp(tl,tr-1,1))%mod;
        if(idata[tl]<idata[tr])tot=(tot+getdp(tl,tr-1,0))%mod;
    }
    else
    {
        if(idata[tr]>idata[tl])tot=(tot+getdp(tl+1,tr,1))%mod;
        if(idata[tl+1]>idata[tl])tot=(tot+getdp(tl+1,tr,0))%mod;
    }
    return tdp[tl][tr][tb]=tot;
}
int main()
{
    freopen("1996.in","r",stdin);
    freopen("1996.out","w",stdout);
    scanf("%d",&n);for each(i,n)scanf("%d",&idata[i]);
    memset(tdp,-1,sizeof tdp);
    //test();
    cout<<(getdp(1,n,0)+getdp(1,n,1))%mod;
}
