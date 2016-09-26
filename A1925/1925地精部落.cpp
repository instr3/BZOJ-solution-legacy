#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
int tdata[5001];
int tdp[2][5001];
int np;
int main()
{
    freopen("1925.in","r",stdin);
    freopen("1925.out","w",stdout);
    int tot=0;
    int n;scanf("%d%d",&n,&np);
    tdp[1][1]=1;
    for every(i,2,n)
    {
        if(i%2)
        {
            tdp[1][i]=0;
            for(int j=i-1;j>=1;--j)
            {
                tdp[1][j]=(tdp[1][j+1]+tdp[1-1][j])%np;
            }
        }
        else
        {
            tdp[0][1]=0;
            for every(j,2,i)
            {
                tdp[0][j]=(tdp[0][j-1]+tdp[1][j-1])%np;
            }
        }
        
        /*for each(j,i-1)
        {
            if(i%2)
            {
                for every(k,1,j)
                {
                    tdp[i][k]+=tdp[i-1][j];
                }
            }
            else
            {
                for every(k,j+1,i)
                {
                    tdp[i][k]+=tdp[i-1][j];
                }
            }
        }*/
    }
    for each(i,n)
    {
        //cout<<i<<":"<<tdp[n%2][i]<<endl;
        tot=(tot+tdp[n%2][i])%np;
    }
    cout<<(tot*2)%np<<endl;
    
    return 0;
    for each(i,n)tdata[i]=i;
    do
    {
        for every(i,2,n-1)
        {
            if(!((tdata[i]>tdata[i-1]&&tdata[i]>tdata[i+1])||
             (tdata[i]<tdata[i-1]&&tdata[i]<tdata[i+1])))
            {
                goto die;
            }
        }
        tot++;
        die:;
    }while(next_permutation(tdata+1,tdata+n+1));
    cout<<tot<<endl;
}
