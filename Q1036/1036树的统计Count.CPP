#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define lowbit(iv) ((iv)&(-(iv)))
int tarr[30001];
int tsarr[30001];
struct tnode
{
    int bg,len;
    tnode(int ibg ,int ilen){bg=ibg;len=ilen;};
    inline void modify(int iv,int iw)
    {
        int ti=iw-tsarr[iv];
        tsarr[iv]=iw;
        tarr[iv]+=ti;
        while(iv-bg+1<=bg+len-1)
        {
            iv+=lowbit(iv-bg+1);
            tarr[iv]+=ti;
        }
    }
    inline int getsum(int iv)
    {
        int res=tarr[iv];
        while(iv-bg+1>0)
        {
            iv-=lowbit(iv-bg+1);
            res+=tarr[iv];
        }
        return res;
    }
};
            
int main()
{
    freopen("1036.in","r",stdin);
    freopen("1036.out","w",stdout);
    tnode myt(111,15);
    myt.modify(115,5);
    myt.modify(116,4);
    myt.modify(117,3);
    myt.modify(118,2);
    for(int i=myt.bg;i<myt.len+myt.bg-1;++i)
    cout<<myt.getsum(i)<<" ";
}
