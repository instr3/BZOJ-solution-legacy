#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n,nm,nx,ny;
#define double double
#define mod 10007
int tdp[51][11][10007];
bool tbool[51][11][10007];
int tref[51];
int tix;
double tfref[51];
double tfix;
inline int gcd(int ia,int ib)
{
    int ir=ia%ib;
    cout<<"GCD:"<<ia<<","<<ib<<":";
    while(ir)
    {
        ia=ib;ib=ir;ir=ia%ib;
    }
    cout<<ib<<endl;
    return abs(ib);
}
inline int getdp(int im,int in,int ix)
{
    if(in==n&&ix==0)
    {
        tbool[im][in][ix]=1;
        return 1;
    }
    if(im==0)return 0;
    if(in>=n)return 0;
    //if(ix<=0)return 0;
    //if(iy>500)return 0;
    if(tdp[im][in][ix]!=-1)return tdp[im][in][ix];
    int res=getdp(im-1,in,ix);
    int tnx=(ix-tref[im]+mod+mod)%mod;
    //int tny=gcd(iy,im)*iy*im,tnx=tny/iy*ix-tny/im;
    //int tg=gcd(tnx,tny);tnx/=tg,tny/=tg;
    //cout<<tnx<<","<<tny<<endl;
    res+=getdp(im-1,in+1,tnx);
    //if(res)cout<<"DP:"<<im<<","<<in<<","<<ix<<":"<<res<<endl;
    tbool[im][in][ix]=res;
    //if(tbool[im][in][ix])cout<<"DP:"<<im<<","<<in<<","<<ix<<":"<<res<<endl;
    return tdp[im][in][ix]=res;
}
#define abs(a) ((a)<0?-(a):a)
int dfs(int im,int in,double ifx,int ix)
{
    
    if(in==n&&abs(ifx)<1e-8)return 1;
    //if(im==0)return 0;
    if(in>=n)return 0;
    int res=0;
    if(tbool[im-1][in][ix])
    res=dfs(im-1,in,ifx,ix);
    double tnfx=ifx-(double)1/im;
    int tnx=(ix-tref[im]+mod+mod)%mod;
    if(tbool[im-1][in+1][tnx])
    res+=dfs(im-1,in+1,tnfx,tnx);
    return res;
}
int main()
{
    freopen("1224.in","r",stdin);
    freopen("1224.out","w",stdout);
    scanf("%d%d%d%d",&n,&nm,&nx,&ny);
    for each(i,nm)
    {
        tref[i]=1;
        tfref[i]=((double)1)/i;
        for each(j,nm)
        {
            if(j==i)continue;
            tref[i]=(tref[i]*j)%mod;
        }
        //cout<<i<<","<<tref[i]<<endl;
    }
    
    tix=1;
    for each(j,nm)
    {
        if(j==ny)continue;
        tix=(tix*j)%mod;
    }
    tix=(tix*nx)%mod;
    tfix=((double)nx)/ny;
    memset(tdp,-1,sizeof tdp);
    getdp(nm,0,tix);
    cout<<dfs(nm,0,tfix,tix);
    
}
