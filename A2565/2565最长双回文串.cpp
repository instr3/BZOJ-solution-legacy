#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define each2(i,n) (int i=n;i;--i)
#define every2(i,a,b) (int i=(b);i.=(a);--i)
int n;
char indata[100002];
int tdata[200012];
int tres[200012];
void manacher()
{
    int tmax=0,tmaxat=0;
    for each(i,n)
    {
        if(tmax>i)
        {
            tres[i]=min(tmax-i,tres[tmaxat*2-i]);
        }
        else tres[i]=1;
        while(tdata[i-tres[i]]==tdata[i+tres[i]])++tres[i];
        if(i+tres[i]>tmax)
        {
            tmax=i+tres[i];
            tmaxat=i;
        }
        //cout<<tres[i]<<" ";
    }//cout<<endl;
}
//int tmax[200012];
int tright[200012];
struct qnode
{
    int l,r,m;
}myq[200012];
inline bool fcmp1(qnode ia,qnode ib)
{
    return ia.l<ib.l;
};
inline bool fcmp2(qnode ia,qnode ib)
{
    return ia.r<ib.r;
};
int main()
{
    freopen("2565.in","r",stdin);
    freopen("2565.out","w",stdout);
    scanf("%s",&indata[1]);
    n=strlen(&indata[1]);
    for each(i,n)
    {
        tdata[i*2-1]='#';
        tdata[i*2]=indata[i];
    }
    tdata[n*2+1]='#';
    tdata[n*2+2]='_';
    n=n*2+1;
    //for each(i,n)cout<<(char)tdata[i]<<" ";
    manacher();
    for each(i,n)
    {
        myq[i].m=i;
        myq[i].l=i-tres[i]+1;
        myq[i].r=i+tres[i]-1;
        tright[myq[i].l]=max(tright[myq[i].l],tres[i]*2-1);
    }
    for each(i,n)
    {
        tright[i]=max(tright[i],tright[i-1]-2);
        //cout<<tright[i]<<" ";
    }
    //sort(myq+1,myq+n+1,fcmp1);
    int tot=0;
    for each(i,n)
    {
        tot=max(tot,(myq[i].r-myq[i].l)/2+tright[myq[i].r]/2+1);
    }
    cout<<tot-1<<endl;
}
