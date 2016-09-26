#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define div(a,b) ((a)>(b)?(a)/(b):(b)/(a))
long double nsqr;
long double BAOLI(int num,long double x,long double y)
{
    
    if(x<y)swap(x,y);
    if(x<=1e-6||y<=1e-6)return 9e99;
    if(num==1)return x/y;
    long double ix=nsqr/y,iy=nsqr/x;
    long double res=9e99;
    for(int i=1;i<num;++i)
    res=min(res,min(
     max(BAOLI(i,ix*i,y),BAOLI(num-i,x-ix*i,y)),
     max(BAOLI(i,x,iy*i),BAOLI(num-i,x,y-iy*i))));
    //cout<<"Ans:"<<num<<":"<<x<<","<<y<<":"<<res<<endl;
    return res;
}
int main()
{
    freopen("1024.in","r",stdin);
    freopen("1024.out","w",stdout);
    int na,nb,n;
    scanf("%d%d%d",&na,&nb,&n);
    nsqr=na*nb/(long double)n;
    printf("%.6f",(double)BAOLI(n,na,nb));
}
    
