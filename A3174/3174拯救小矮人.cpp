#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n,nh;
struct dwarf
{
    int a,b;
    bool operator <(dwarf ano)const
    {
        return a+b<ano.a+ano.b;
    }
}ind[2001];
int tdp[2001][2001];

int main()
{
    memset(tdp,-37,sizeof tdp);
    freopen("3174.in","r",stdin);
    freopen("3174.out","w",stdout);
    scanf("%d",&n);
    int tot=0;
    for each(i,n)
    {
        scanf("%d%d",&ind[i].a,&ind[i].b);
        tot+=ind[i].a;
    }
    sort(ind+1,ind+n+1);
    scanf("%d",&nh);
    tdp[0][0]=0;
    for each(i,n)
    {
        tot-=ind[i].a;
        for every(j,0,i)
        {
            ////cout<<i<<","<<j<<endl;
            //cout<<ind[i].a+ind[i].b<<endl;
            if(j)
            if(tdp[i-1][j-1]+tot+ind[i].a+ind[i].b>=nh)
            {
                //cout<<i<<","<<j<<":"<<tdp[i-1][j-1]+tot+ind[i].a+ind[i].b<<endl;
                tdp[i][j]=max(tdp[i][j],tdp[i-1][j-1]);
            }
            tdp[i][j]=max(tdp[i][j],tdp[i-1][j]+ind[i].a);
        }
    }
    for every(j,0,n)
    {
       // cout<<tdp[1][j]<<" ";
        if(tdp[n][j]<0)
        {
            printf("%d",j-1),exit(0);
        }
    }
    printf("%d",n);
    
}
