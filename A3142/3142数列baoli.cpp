#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int nlim,nd,nup,nmod;
#define fc(a,b) (tcp[(a)+1][(b)+1])
int tcp[103][103];
void prec()
{
    tcp[1][1]=1;
    for every(i,2,102)
    for every(j,1,i)
    {
        tcp[i][j]=(tcp[i-1][j]+tcp[i-1][j-1])%nmod;
    }
}
int tot=0;
int tdp[5001][5001];

void dp()
{
    for each(j,nlim)tdp[1][j]=1;
    int timin;
    for every(i,2,nd)
    {
        for each(j,nlim)
        {
            timin=max(1,j-nup);
            for every(k,timin,j-1)
            {
                tdp[i][j]=(tdp[i][j]+tdp[i-1][k])%nmod;
            }
            //cout<<i<<","<<j<<":"<<tdp[i][j]<<endl;
        }
    } 

    for each(j,nlim)
    {
        cout<<tdp[nd][j]<<" ";
        tot=(tot+tdp[nd][j])%nmod;
    }cout<<endl;
    /*long long tres=0;
    for each(j,nlim)
    {
        if(j>=3)
        tres=tres+fc(2,j-3);
        cout<<tres<<" ";
    }*/
}
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    scanf("%d%d%d%d",&nlim,&nd,&nup,&nmod);
    //prec();
    dp();
    cout<<tot<<endl;
}
