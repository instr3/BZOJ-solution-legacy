#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n,nm,nt;
#define tr(a,b) (b)=max((a),(b))
int ind[101][101];
int tdp[101][101][101];
int tdp2[101][2501];
int main()
{
    freopen("1296.in","r",stdin);
    freopen("1296.out","w",stdout);
    scanf("%d%d%d",&n,&nm,&nt);
    for each(i,n)
    {
        for each(j,nm)
        {
            scanf("%1d",&ind[i][j]);
        }
    }
    int tsc[2];
    int tc[2];
    for each(i,n)
    {
        for each(j,nm)
        {
            tsc[0]=tsc[1]=0;
            for every(k,0,nm)
            {
                if(k)tsc[ind[i][k]]++;
                if(k)tr(tdp[i][j][k-1],tdp[i][j][k]);
                tr(tdp[i][j-1][k],tdp[i][j][k]);
                tc[0]=tc[1]=0;
                for every(il,0,k)
                {
                    if(il)tc[ind[i][il]]++;
                    tr(tdp[i][j-1][il]+max(tsc[1]-tc[1],tsc[0]-tc[0]),tdp[i][j][k]);
                }
                
            }
            //printf("%d ",tdp[i][j][nm]);
        }
        //cout<<endl;
    }
    for each(i,n)
    {
        for each(j,nt)
        {
            tr(tdp2[i-1][j],tdp2[i][j]);
            tr(tdp2[i][j-1],tdp2[i][j]);
            for every(k,0,j)
            {
                tr(tdp2[i-1][k]+tdp[i][j-k][nm],tdp2[i][j]);
            }
            //cout<<tdp2[i][j]<<" ";
        }
        //cout<<endl;
    }
    printf("%d",tdp2[n][nt]);
}
