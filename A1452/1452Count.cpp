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
#define lowbit(i) ((i)&-(i))
struct ltree
{
    int n;
    struct l2tree
    {
        int n;
        //int s[301];
        int w[301];
        inline void add(int iv,int iw)
        {
            //s[iv]+=iw;
            while(iv<=n)
            {
                //cout<<iv<<","<<iw<<endl;
                w[iv]+=iw;
                iv+=lowbit(iv);
            }
        }
        inline int sum(int iv)
        {
            int res=0;
            while(iv)
            {
                //cout<<iv<<","<<res<<endl;
                res+=w[iv];
                iv-=lowbit(iv);
            }
            return res;
        }
        inline void init(int n1)
        {
            n=n1;
        }
    }w[301];
    inline void add(int iv,int iv2,int iw)
    {
        //s[iv]+=iw;
        while(iv<=n)
        {
            //cout<<iv<<","<<iv2<<","<<iw<<endl;
            w[iv].add(iv2,iw);
            iv+=lowbit(iv);
        }
    }
    inline int sum(int iv,int iv2)
    {
        int res=0;
        while(iv)
        {
            //cout<<iv<<","<<iv2<<","<<res<<endl;
            res+=w[iv].sum(iv2);
            iv-=lowbit(iv);
        }
        return res;
    }
    #define asksum(wt,ix1,iy1,ix2,iy2) (wt.sum(ix2,iy2)-wt.sum((ix1)-1,iy2)-wt.sum(ix2,(iy1)-1)+wt.sum((ix1)-1,(iy1)-1))
    inline void init(int n1,int n2)
    {
        n=n1;
        for each(i,n1)w[i].init(n2);
    }
}myt[101];
int main()
{
    freopen("1452.in","r",stdin);
    freopen("1452.out","w",stdout);
    int n,nm;
    scanf("%d%d",&n,&nm);
    for each(i,100)myt[i].init(n,nm);
    int indata[301][301];;
    for each(i,n)
    {
        for each(j,nm)
        {
            scanf("%d",&indata[i][j]);
            myt[indata[i][j]].add(i,j,1);
        }
    }
    int nop;
    scanf("%d",&nop);
    int top;
    int tx1,tx2,ty1,ty2,tc;
    
    for each(i,nop)
    {
        scanf("%d",&top);
        if(top==2)
        {
            scanf("%d%d%d%d%d",&tx1,&tx2,&ty1,&ty2,&tc);
            printf("%d\n",asksum(myt[tc],tx1,ty1,tx2,ty2));
        }
        else
        {
            scanf("%d%d%d",&tx1,&ty1,&tc);
            myt[indata[tx1][ty1]].add(tx1,ty1,-1);
            indata[tx1][ty1]=tc;
            myt[indata[tx1][ty1]].add(tx1,ty1,1);
        }
    }
    return 0;
    //myt.init(n,nm);
    //myt.add(1,1,1);
    //myt.add(3,2,2);
    //cout<<asksum(myt,2,2,3,4);
    
}
