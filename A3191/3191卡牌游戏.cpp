#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define fc(num,mod) (((num)-1)%(mod)+1)
long double tdp[51][51];
long double tsum;
int n;
int nm;int inum[51];
int main()
{
    scanf("%d%d",&n,&nm);
    for each(i,nm)scanf("%d",&inum[i]);
    tdp[1][1]=1;
    for every(i,2,n)
    {
        tsum=0;
        for each(im,nm)
        {
            //tdp[i][fc(inum[im],i)]+=1;
            //cout<<fc(inum[im],i)<<endl;
            for each(j,i-1)
            {
                tdp[i][fc(inum[im]+j,i)]+=tdp[i-1][j];
            }
        }
        for each(j,i)tsum+=tdp[i][j];
        for each(j,i)
        {
            tdp[i][j]/=tsum;
            //cout<<tdp[i][j]<<" ";
        }
        //cout<<endl;
    }
    for each(i,n-1)
    {
        printf("%.2f%c ",(double)tdp[n][i]*100,'%');
    }
    printf("%.2f%c",(double)tdp[n][n]*100,'%');
}
        