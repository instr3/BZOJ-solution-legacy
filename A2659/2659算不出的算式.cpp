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
int np,nq;
int tk;
int main()
{
    freopen("2659.in","r",stdin);
    freopen("2659.out","w",stdout);
    scanf("%d%d",&np,&nq);
    if(nq==np)nq+=2;
    cout<<(long long)(np>>1)*(nq>>1)<<endl;
    //return 0;
    int tk;
    tk=(np-1)/2;
    int res=0;
    for each(k,tk)
    {
        res+=(int)((double)(k*nq)/np);
    }
    tk=(nq-1)/2;
    for each(k,tk)
    {
        res+=(int)((double)(k*np)/nq);
    }
    cout<<res<<endl;
}
