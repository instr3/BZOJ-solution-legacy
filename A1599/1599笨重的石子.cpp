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
int tres[81];
int n1,n2,n3;
int main()
{
    freopen("1599.in","r",stdin);
    freopen("1599.out","w",stdout);
    scanf("%d%d%d",&n1,&n2,&n3);
    srand(321);
    int n=n1+n2+n3;
    int tot=99999999;
    int tmin=0,tminat;
    for each(i1,n1)
    for each(i2,n2)
    for each(i3,n3)
    {
        tres[i1+i2+i3]+=1;
    }
    for each(i,n)
    {
        if(tmin<tres[i])
        {
            tmin=tres[i];
            tminat=i;
        }
    }
    cout<<tminat<<endl;
    return 0;
    int t1,t2,t3;
    for each(j,10)
    {
        memset(tres,0,sizeof tres);
        for each(i,10000000)
        {
            t1=rand()%n1+1;
            t2=rand()%n2+1;
            t3=rand()%n3+1;
            //cout<<t1<<","<<t2<<","<<t3<<endl;
            tres[t1+t2+t3]++;
        }
        tmin=0;
        for each(i,n)
        {
            if(tmin<tres[i])
            {
                tmin=tres[i];
                tminat=i;
            }
        }
        cout<<tminat<<" ";
        tot=min(tot,tminat);
    }
    cout<<tot<<endl;
    for each(i,n)
    cout<<tres[i]<<endl;
}
