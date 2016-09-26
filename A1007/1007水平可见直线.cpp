#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
struct lnode
{
    int k,b,pos;
    long double xb;
    bool operator < (lnode ano) const
    {
        return k<ano.k;
    }
}mys[50001],myh[50001];
bool ans[50001];
int pmys=0;
inline long double getins(lnode a,lnode b)
{
    return (b.b-a.b)/(long double)(a.k-b.k) +1e-6L;
}
int main()
{
    freopen("1007.in","r",stdin);
    freopen("1007.out","w",stdout);
    int n;scanf("%d",&n);
    long double trx;
    myh[0].k=-999999;
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&myh[i].k,&myh[i].b);
        myh[i].pos=i;
    }
    sort(myh+1,myh+n+1);
    for(int i=1;i<=n;++i)
    {
        mys[++pmys].k=myh[i].k;
        mys[pmys].b=myh[i].b;
        mys[pmys].pos=myh[i].pos;
        if(pmys==1)
        {
            mys[pmys].xb=-9e200L;
        }
        else for(;pmys;)
        {
            if(pmys==1)break;
            if(mys[pmys].k==mys[pmys-1].k)
            {
                if(mys[pmys].b>mys[pmys-1].b)
                {
                    mys[pmys-1].b=mys[pmys].b;
                    mys[pmys-1].pos=mys[pmys].pos;
                }
                pmys--;
                continue;
            }
            trx=getins(mys[pmys],mys[pmys-1]);
            mys[pmys].xb=trx;
            if(trx<=mys[pmys-1].xb)
            {
                mys[pmys-1]=mys[pmys];
                mys[pmys-1].xb=getins(mys[pmys-1],mys[pmys-2]);
                pmys--;
                continue;
            }
            break;
        }
    }
    for(int i=1;i<=pmys;++i)
    {
        ans[mys[i].pos]=true;
    }
    for(int i=1;i<=n;++i)
    {
        if(ans[i])printf("%d ",i);
    }
}
                
