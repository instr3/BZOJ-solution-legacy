#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n;
int ind[100001];
int tres;
struct segtree
{
    int d[100002];
    
    #define lowbit(iv) ((iv)&-(iv))
    inline void add(int iv,int iw)
    {
        while(iv<=n)
        {
            d[iv]+=iw;
            iv+=lowbit(iv);
        }
    }
    inline int sum(int iv)
    {
        int res=0;
        while(iv)
        {
            res+=d[iv];
            iv-=lowbit(iv);
        }
        return res;
    }
}myt;
inline int search(int iw)
{
    int il=0,ir=tres+1,im;
    while(il+1!=ir)
    {
        im=(il+ir)>>1;
        if(myt.sum(im)>=iw)
        {
            ir=im;
        }
        else
        {
            il=im;
        }
    }
    return ++il;
}

int main()
{
    freopen("3173.in","r",stdin);
    freopen("3173.out","w",stdout);
    scanf("%d",&n);
    if(n==0)return 0;
    for each(i,n)scanf("%d",&ind[i]);
    myt.add(1,1);tres=1;printf("1\n");
    int tm;
    int tv;
    for every(i,2,n)
    {
        
        tm=search(ind[i]+1);
        //cout<<i<<":"<<endl;
        //for each(j,tres)cout<<myt.sum(j)<<" ";cout<<endl;
        
        if(tm>tres)
        {
            tres++;
            myt.add(tm,1);
            tv=myt.sum(tm);
            myt.add(tm,ind[i]+1-tv);
            myt.add(tm+1,tv-1-ind[i]);
        }
        else
        {//cout<<i<<","<<tm<<","<<myt.sum(tm)<<","<<ind[i]+1<<endl;
            tv=myt.sum(tm);
            if(tv>=ind[i]+1)
            {
                myt.add(tm,ind[i]+1-tv);
                myt.add(tm+1,tv-1-ind[i]);
                ++tm;
            }
            myt.add(tm,1);
        }
        printf("%d\n",tres);
    }
    
}
