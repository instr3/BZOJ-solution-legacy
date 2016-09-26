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
int indata[10001];
int zcon[10001][2];
//int zmap[501][501];
int zx[10001],zy[10001];
bool visit[10001];
inline void addedge(int pf,int pt1,int pt2)
{
    //cout<<pf<<","<<pt<<endl;
    //zmap[pf][pt]=1;
    zcon[pf][0]=min(pt1,pt2);
    zcon[pf][1]=max(pt1,pt2);
}
bool zpath(int ix)
{
    int iy;
    for every(i,0,1)
    {
        iy=zcon[ix][i];
        //if(!zmap[ix][iy])continue;
        if(visit[iy])continue;
        visit[iy]=true;
        if(!zy[iy])
        {
            zy[iy]=ix;
            zx[ix]=iy;
            return true;
        }
        else if(zpath(zy[iy]))
        {
            zy[iy]=ix;
            zx[ix]=iy;
            return true;
        }
    }
    return false;
}
int main()
{
    freopen("1562.in","r",stdin);
    freopen("1562.out","w",stdout);
    scanf("%d",&n);
    int tot=0;
    for each(i,n)
    {
        scanf("%d",&indata[i]);
        //if(n-indata[i]<indata[i])goto die;
        addedge(i,(i+indata[i]-1)%n+1,(i+n-indata[i]-1)%n+1);
    }
    for (int ix=n;ix>=1;--ix)
    {
        memset(visit,0,sizeof visit);
        if(zpath(ix))tot++;
    }
    if(tot<n)
    {
        die:;
        cout<<"No Answer";return 0;
    }
    for each(ix,n-1)
    {
        cout<<zx[ix]-1<<" ";
    }
    cout<<zx[n]-1<<endl;
        
}
