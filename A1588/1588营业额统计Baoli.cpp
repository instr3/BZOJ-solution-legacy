#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define min(a,b) ((a)<(b)?(a):(b))
#define abs(a) ((a)<0?-(a):(a))
int n,indata[32768];
bool tsave[2002003];
#define save(i) (tsave[(i)+1001000])
int res;
int main()
{
    freopen("1588.in","r",stdin);
    freopen("1588.out","w",stdout);
    scanf("%d",&n);
    for each(i,n)
    {
        if(scanf("%d",&indata[i])==EOF)indata[i]=0;
    }
    int tmin;
    save(indata[1])=true;
    for every(i,2,n)
    {
        if(save(indata[i]))continue;
        save(indata[i])=true;
        for each(k,i)
        {
            if(save(indata[i]+k)){res+=k;goto die;}
            if(save(indata[i]-k)){res+=k;goto die;}
        }
        tmin=1999999999;
        for each(j,i-1)
        {
            tmin=min(tmin,abs(indata[j]-indata[i]));
        }
        res+=tmin;
        die:;
    }
    printf("%d",res+indata[1]);
}
