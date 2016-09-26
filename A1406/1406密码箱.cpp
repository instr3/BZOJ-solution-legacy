#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <set>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define sqr(i) ((long long)(i)*(i))
set<int> mys;
int task(int n)
{
    int tot=0;
    for each(i,n)
    {
        if(sqr(i)%n==1)
        {
            printf("%d\n",i);
            tot++;
        }
    }
    return tot;
}
int main()
{
    freopen("1406.in","r",stdin);
    freopen("1406.out","w",stdout);
    int n;scanf("%d",&n);
    if(n==1)
    {
        printf("None");return 0;
    }
    //task(n);
    int tnum;
    int sqrtn=(int)sqrt(n);
    int ta,tb;
    for(ta=1;ta<=sqrtn;++ta)
    {
        if(n%ta==0)
        {
            tb=n/ta;
            for(int i=tb-1;i<=n&&i>0;i+=tb)
            {
                if((i-1)%ta==0)
                mys.insert(i);
            }
            for(int i=1;i<=n&&i>0;i+=tb)
            {
                if((i+1)%ta==0)
                mys.insert(i);
            }
        }
    }
    for(set<int>::iterator p=mys.begin();p!=mys.end();p++)
    {
        printf("%d\n",*p);
    }
    /*for each(i,n)
    {
        tnum=(1<<i)*10;
        cout<<tnum<<":"<<task(tnum)<<endl;
    }*/
}
