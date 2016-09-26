#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int d1[100001],d2[100001];
int main()
{
    int n;
    scanf("%d",&n);

    for(int i=1;i<=n;++i)
    {
        scanf("%d",&d1[i]);
    }
    sort(d1+1,d1+n+1);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&d2[i]);
    }
    sort(d2+1,d2+n+1);
    int rmax=0,rmin=0;
    int tp=1;
    int trms=0;
    for(int i=1;i<=n;++i)
    {
        while(d2[tp]<d1[i])
        {
            ++tp;
            if(trms){--trms;++rmin;};
            if(tp>n)goto text;
        }
        if(d2[tp]==d1[i]){++trms;++rmin;}else
        rmin+=2;
        ++tp;
        if(tp>n)goto text;
    }
    text:;
    rmin=
    trms=tp=0;
    for(int i=1;i<=n;++i)
    {
        while(d1[ tp]<d2[i])
        {
            ++tp;
            if(trms){--trms;++rmax;};
            if(tp>n)goto text2;
        }
        if(tp>n)break;
        if(d1[tp]==d2[i]){++trms;++rmax;}else
        rmax+=2;
        ++tp;
        if(tp>n)break;
    }
    text2:;
    printf("%d %d",rmax,(n<<1)-rmin);
    
    system("pause");
}
