#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
struct inode
{
    int w,n;
    bool operator <(inode ano)const
    {
        return w<ano.w;
    }
}indata[100001];
struct bittree
{
    int n;
    int d[100001];
    #define lowbit(iv) ((iv)&-(iv))
    inline void add(int iv,int iw) 
    {
        while(iv<=n)
        {
            d[iv]+=iw;
            iv=iv+lowbit(iv);
        }
    }
    inline int sum(int iv)
    {
         
        int ans=0;
        while(iv)
        {
            ans+=d[iv];
            iv-=lowbit(iv);
        }
        return ans;
    }
}myt;
int n1,n2;
int n;
//int indata[100001];
int place[100001];
int main()
{
    scanf("%d%d",&n1,&n2);
    int tp=n1;
    for each(i,n1)
    {
        scanf("%d",&indata[n1+1-i].w);
    }
    for each(i,n2)
    {
        scanf("%d",&indata[n1+i].w);
    }
    n=myt.n=n1+n2;
    for each(i,n)
    {
        indata[i].n=i;
    }
    sort(indata+1,indata+n+1);
     
    for each(i,n)
    {
        place[i]=indata[i].n;
        //cout<<place[i]<<endl;
    }
    long long tw,tot=0;
    for(int i=n;i;--i)
    {
        //cout<<"Deal:"<<i<<":"<<tot<<endl;
        if(place[i]==tp)
        {
            myt.add(place[i],1);
            continue;
        }
        if(place[i]>tp)
        {
            tw=place[i]-1-tp-(myt.sum(place[i]-1)-myt.sum(tp));
            tot+=tw;
            myt.add(place[i],1);
            tp=place[i]-1;
        }
        else
        {
            tw=tp-place[i]-(myt.sum(tp)-myt.sum(place[i]));
            tot+=tw;
            myt.add(place[i],1);
            tp=place[i];
        }
    }
    printf("%lld",tot);
}
        