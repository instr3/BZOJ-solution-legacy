#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
#define sqr(a) ((a)*(a))

long double dp[11][11][11][11][11];
bool mk[11][11][11][11][11];
int data[11][11];
int sdata[11][11];
long long sum;
int na,nb,nk;
long double nu;
using namespace std;
long double gdp(int xf,int xt,int yf,int yt,int ik)
{
    if(mk[xf][xt][yf][yt][ik])return dp[xf][xt][yf][yt][ik];
    if(xf==xt&&yf==yt)
    {
        if(ik==1)return sqr(data[xf][yt]-nu);
        else return 1e30;
    }
    if(ik==1)
    {
        return
        sqr(sdata[xt][yt]-sdata[xf-1][yt]-sdata[xt][yf-1]+sdata[xf-1][yf-1]-nu);
    }
    long double res=1e30;
    for(int k=1;k<ik;++k)
    {
        for(int ix=xf;ix<xt;++ix)
        {
            res=min(res,
             gdp(xf,ix,yf,yt,k)+gdp(ix+1,xt,yf,yt,ik-k));
        }
        for(int iy=yf;iy<yt;++iy)
        {
            res=min(res,
             gdp(xf,xt,yf,iy,k)+gdp(xf,xt,iy+1,yt,ik-k));
        }
    }
    mk[xf][xt][yf][yt][ik]=true;
    return dp[xf][xt][yf][yt][ik]=res;
}
int main()
{
    freopen("1048.in","r",stdin);
    freopen("1048.out","w",stdout);
    int na,nb,nk;
    scanf("%d%d%d",&na,&nb,&nk);
    for(int i=1;i<=na;++i)
    for(int j=1;j<=nb;++j)
    {
        scanf("%d",&data[i][j]);
        sum+=data[i][j];
        sdata[i][j]=sdata[i-1][j]+sdata[i][j-1]-sdata[i-1][j-1]+data[i][j];
        //cout<<i<<","<<j<<":"<<sdata[i][j]<<endl;
    }
    nu=(long double)sum/(nk);
    printf("%.2f",(double)sqrt(gdp(1,na,1,nb,nk)/(nk)));
}
