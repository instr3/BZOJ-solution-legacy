#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define fc(a,b) (tdp[(a)+1][(b)+1])
int tdp[1003][1003];
void prec()
{
    tdp[1][1]=1;
    for every(i,2,1001)
    for every(j,1,i)
    {
        tdp[i][j]=(tdp[i-1][j]+tdp[i-1][j-1])%2007;
    }
}
long double tpos[100001],allpos;
int n,np,nred,nblue;
void task()
{
    memset(tpos,0,sizeof tpos);
    allpos=0;
    nblue=np-nred;
    for(int ired=0,iblue;ired<=n;++ired)
    {
        iblue=n-ired;
        if(ired<nred||iblue<nblue)continue;
        //cout<<"A:"<<nred<<","<<ired<<":"<<fc(nred,ired)<<endl;
        tpos[ired]=(fc(ired,nred)*fc(iblue,nblue))/(long double)fc(n,np);
        allpos+=tpos[ired];
    }
    long double res=0;
    for(int ired=0;ired<=n;++ired)
    {
        tpos[ired]/=allpos;
        res=res+tpos[ired]*(ired-nred)/(long double)(n-np);
        cout<<tpos[ired]<<endl;
    }
    cout<<res<<endl;
    cout<<(nred+1)/(long double)(np+2)<<endl;
}
int main()
{
    cout<<EOF<<endl;
    prec();
    while(scanf("%d%d%d",&n,&np,&nred)!=EOF)
    {
        task();
    }
    
}
