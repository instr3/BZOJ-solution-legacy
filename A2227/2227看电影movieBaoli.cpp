#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iomanip>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n,nk;
bool taken[101];
#define double long double
struct anode
{
    double d[101];
    anode operator +(anode ano)
    {
        anode tnew;
        for each(i,nk)
        {
            tnew.d[i]=d[i]+ano.d[i];
        }
        return tnew;
    }
    anode operator /(double in)
    {
        anode tnew;
        for each(i,nk)
        {
            tnew.d[i]=d[i]/in;
        }
        return tnew;
    }
};
double dfs(int ip)
{
    if(ip==0)return 1;
    double tres=0;
    for each(i,nk)
    {
        for every(j,i,nk)
        {
            if(!taken[j])
            {
                taken[j]=true;
                tres+=dfs(ip-1)/nk;
                taken[j]=false;
                break;
            }
        }
    }
    return tres;
}
void task()
{

    cout<<setprecision(12)<<dfs(n)*pow(nk,(double)n)/pow(nk+1,n-1.0);
}
int main()
{
    freopen("2227.in","r",stdin);
    freopen("2227.out","w",stdout);
    int nn,nnk;
    scanf("%d%d",&nn,&nnk);
    for each(i,nnk)
    {
        for each(j,i)
        {
            n=j;nk=i;
            task();cout<<" ";
        }
        cout<<endl;
    }
}
