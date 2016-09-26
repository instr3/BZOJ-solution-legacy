#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
int n;
int indata[200002];
struct clist
{
    int dsize;
    int s[200002];
    int ct[200002];
    int to[200002];
    int bnum;
    struct cbox
    {
        int lt,rt;
        inline int size(){return rt-lt+1;};
    }b[2001];
    inline void updata(cbox &ib,int ir)
    {
        for(int i=ir;i>=ib.lt;--i)
        {
            if(i+s[i]>ib.rt)
            {
                ct[i]=1;to[i]=i+s[i];
            }
            else
            {
                ct[i]=ct[i+s[i]]+1;to[i]=to[i+s[i]];
            }
        }
    }
    inline cbox *locate(int ik)
    {
        for each(i,bnum)
        {
            if(ik>=b[i].lt&&ik<=b[i].rt)return &b[i];
        }
        return 0;
    }
    inline void print()
    {
        for each(k,bnum)
        {
            for every(i,b[k].lt,b[k].rt)cout<<s[i]<<" ";cout<<":";
            cout<<b[k].lt<<"-"<<b[k].rt<<endl;
        }
    }
    inline void init()
    {
        dsize=(int)sqrt(n);
        bnum=(n-1)/dsize+1;
        int ti=0;
        for each(i,bnum)
        {
            b[i].lt=ti+1;
            b[i].rt=min(ti+dsize,n);
            ti+=dsize;
            updata(b[i],b[i].rt);
        }
    }
}myl;
int main()
{
    freopen("2002.in","r",stdin);
    freopen("2002.out","w",stdout);
    scanf("%d",&n);
    for each(i,n)scanf("%d",&myl.s[i]);
    myl.init();
    
    //myl.print();
    int nm;
    scanf("%d",&nm);
    int top,tv,tk;
    int res;
    for each(i,nm)
    {
        scanf("%d%d",&top,&tv);
        tv++;
        if(top==1)
        {
            res=0;
            for each(i,myl.bnum)
            {
                res+=myl.ct[tv];
                tv=myl.to[tv];
                if(tv>n)break;
            }
            printf("%d\n",res);
        }
        else
        {
            scanf("%d",&tk);
            myl.s[tv]=tk;
            myl.updata(*myl.locate(tv),tv);
        }
    } 
}
    
