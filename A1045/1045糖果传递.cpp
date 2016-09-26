#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,b,e) (int i=(b);i<=(e);++i)
#define myabs(x) ((x)>0?(x):(-x))
int idata[1000001],data[1000001];
long long allsum;
int n;
inline long long task(int tnum)
{
    long long tv1=tnum;//表示某个人前面的人给那个的数量
    long long tsum=0; 
    for each(i,n)
    {
        tsum+=myabs(tv1);
        tv1=data[i]+tv1;
    }
    return tsum;
}
int main()
{
    freopen("1045.in","r",stdin);
    freopen("1045.out","w",stdout);
    scanf("%d",&n);
    for each(i,n)
    {
        scanf("%d",&idata[i]);
        allsum+=idata[i];
    }
    int tv=allsum/n;
    for each(i,n)
    {
        data[i]=idata[i]-tv;
        //cout<<data[i]<<" ";
    }
    //for every(i,-10,10)
    //cout<<task(i)<<" ";
    int tl=-2147483647,tr=2147483647,tp;
    long long ttp,ttp1;
    while(tl<tr-3)
    {
        //cout<<tl<<","<<tr<<endl;
        tp=(tl+tr)/2;
        ttp=task(tp);
        ttp1=task(tp+1);
        if(ttp<ttp1)tr=tp+1;
        else if(ttp>ttp1)tl=tp;
        else{cout<<ttp;return 0;};
    }
    long long minans=9999999999999999LL;
    for every(i,tl,tr-1)
    {
        minans=min(minans,task(i));
    }
    cout<<minans;return 0;
}
        
