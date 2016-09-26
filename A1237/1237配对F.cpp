#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n,ina[100001],inb[100001];
long long tdp[100001][8][8];
int pca[8]={0,1,1,2,1,2,2,3};
int tca[8][3]={{},{0},{0},{1,2},{0},{1,4},{2,4},{3,5,6}};
int tto[8][3]={{},{0},{1},{1,0},{2},{2,0},{2,1},{2,1,0}};
#define trans(a,b) b=min(b,a)
#define dist(a,b) (abs(ina[a]-inb[b]))
int main()
{
    freopen("1237.in","r",stdin);
    freopen("1237.out","w",stdout);
    memset(tdp,38,sizeof tdp);
    scanf("%d",&n);
    for each(i,n)
    {
        scanf("%d%d",&ina[i],&inb[i]);
    }
    sort(ina+1,ina+n+1);
    sort(inb+1,inb+n+1);
    tdp[1][1][1]=0;
    for each(i,n)
    {
        for(int ia=8;ia>=0;--ia)
        for(int ib=8;ib>=0;--ib)
        {
            for every(ita,0,pca[ia]-1)
            for every(itb,0,pca[ib]-1)
            {
                if(dist(i-tto[ia][ita],i-tto[ib][itb])!=0)
                {
                    trans(tdp[i][ia][ib]+dist(i-tto[ia][ita],i-tto[ib][itb]),tdp[i][tca[ia][ita]][tca[ib][itb]]);
                    //if(640034342!=tdp[i][tca[ia][ita]][tca[ib][itb]])cout<<"UP:"<<i<<","<<tca[ia][ita]<<","<<tca[ib][itb]<<":"<<tdp[i][tca[ia][ita]][tca[ib][itb]]<<endl;
                    
                }
            }
        }
        for every(ia,0,3)
        for every(ib,0,3)
        {
            trans(tdp[i][ia][ib],tdp[i+1][ia*2+1][ib*2+1]);
        }
    }
    if(tdp[n][0][0]==tdp[0][7][6])
    {
        printf("-1");
    }
    else printf("%d",tdp[n][0][0]);
}
