#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int indata[51],tdata[51],inget[1001];
int n,nget;
bool task(int ig,int il=1)
{
    //cout<<ig<<","<<il<<endl;
    if(ig==0)
    {
        //for each(i,n)cout<<tdata[i]<<",";cout<<endl;
        return true;
    }
    for every(i,il,n)
    {
        if(tdata[i]>=inget[ig])
        {
            tdata[i]-=inget[ig];
            if(inget[ig-1]==inget[ig])
            {
                if(task(ig-1,i))return true;
            }
            else if(task(ig-1))return true;
            tdata[i]+=inget[ig];
        }
    }
    return false;
}
int main()
{
    freopen("1082.in","r",stdin);
    freopen("1082.out","w",stdout);
    scanf("%d",&n);
    for each(i,n)scanf("%d",&indata[i]);
    sort(indata+1,indata+n+1);
    scanf("%d",&nget);
    for each(i,nget)scanf("%d",&inget[i]);
    sort(inget+1,inget+nget+1);
    int nsum=0;
    for each(i,n)nsum+=indata[i];
    int tsum=0;
    for each(i,nget)tsum+=inget[i];
    while(tsum>nsum){tsum-=inget[nget--];}
    int tl=0,tr=nget+1,tm;
    while(tl+1!=tr)
    {
        //cout<<tl<<","<<tr<<","<<endl;
        tm=(tl+tr)>>1;
        for each(i,n)tdata[i]=indata[i];
        if(task(tm))tl=tm;else tr=tm;
    }
    cout<<tl;
}
