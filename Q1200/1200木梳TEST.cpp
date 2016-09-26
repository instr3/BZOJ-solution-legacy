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
int n;
int indata[101];
int tarr[101];
#define each_without_int(i,n) (i=0;i<=(n);++i)
#define fft(i) for each_without_int(tarr[i],((i)>(n)?0:(indata[i])))
int task()
{
    int tres;
    int tlast;
    int tsum=0;
    for each(i,n)tsum+=indata[i];
    int tmin=99999999;
    fft(1)fft(2)fft(3)fft(4)fft(5)fft(6)fft(7)fft(8)fft(9)fft(10)
    {
        for each(i,n)if(tarr[i]==0)goto die;
        tlast=0;
        for every(i,2,n)
        {
            if(tarr[i]>tarr[i-1])
            {
                if(tlast==1)goto die;
                tlast=1;
            }
            if(tarr[i]<tarr[i-1])
            {
                if(tlast==-1)goto die;
                tlast=-1;
            }
        }
        tres=0;
        for each(i,n)tres+=tarr[i];
        tmin=min(tmin,tsum-tres);
        die:;
    }
    return tmin;
}
int main()
{
    freopen("1200.in","r",stdin);
    freopen("1200.out","w",stdout);
    scanf("%d",&n);
    for each(i,n)scanf("%d",&indata[i]);
    int nn=n;
    for each_without_int(n,nn)
    cout<<task()<<endl;
}
