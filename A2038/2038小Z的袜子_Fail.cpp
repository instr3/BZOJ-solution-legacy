#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
//TJ:http://hi.baidu.com/wjbzbmr/item/7ad9d409663db62fa0312dd0

int indata[50001];
int tcol[50001][501];int pcol[50001];
int texcol[501][50001];
int tpcol[50001];
int n,nm;
inline int binaryfind(int *idata,int il,int ir,int inum)
//寻找能够匹配的最后一个数字 
{
    //for every(i,il,ir)cout<<idata[i]<<" ";cout<<":"<<inum<<"  "<<":";
    
    if(il>=ir)return 0;
    int im;
    while(il+1!=ir)
    {
        im=(il+ir)/2;
        if(idata[im]<=inum)
        {
            il=im;
        }
        else
        {
            ir=im;
        }
    }
    //cout<<il;
    return il;
}
struct tnode
{
    int lt,rt;
    int num;long long ans;
    bool operator <(tnode ano)const
    {
        return rt<ano.rt;
    }
}myask[50001];
bool cmp1(tnode it1,tnode it2)
{
    return it1.num<it2.num;
}
struct megtree
{
    long long d[50001];
    #define lowbit(iv) ((iv)&-(iv))
    inline void add(int iv,int in)
    {
        while(iv<=n)
        {
            d[iv]+=in;
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
}myt;//Saves 50000 Steps OF ColorCount(tcc)
long long tres[50001];//Saves Sum(ColorCount 1..i)
int tbr[50001];int ptbr;
int tnextb[50001],tfirstb;
inline int gcd(int ia,int ib)
{
    int ir=ia%ib;
    while(ir)
    {
        ia=ib;ib=ir;ir=ia%ib;
    }
    return ib;
}
int main()
{
    freopen("2038.in","r",stdin);
    freopen("2038.out","w",stdout);
    scanf("%d%d",&n,&nm);
    for each(i,n)scanf("%d",&indata[i]);
    int tsqrtn=100+(int)sqrt((double)n);
    for each(i,n)
    {
        tcol[indata[i]][++pcol[indata[i]]]=i;
        
        tpcol[i]=pcol[indata[i]];
        
    }
    int tlast=0;
    for each(i,n)
    {
        if(pcol[i]>=tsqrtn)
        {
            tbr[i]=true;
            tnextb[tlast]=i;
            tlast=i;
        }
    }
    tfirstb=tnextb[0];
    for each(i,nm)
    {
        scanf("%d%d",&myask[i].lt,&myask[i].rt);
        myask[i].num=i;
    } 
    sort(myask+1,myask+nm+1);
    int tpask=0;
    int tl,tr;
    for each(i,n)
    {
        cout<<"Now:"<<i<<"(color:"<<indata[i]<<")"<<endl;
        if(!tbr[indata[i]])
        {
            for each(k,tpcol[indata[i]]-1)
            {
                tres[tcol[indata[i]][k]]++;
                cout<<i<<indata[i]<<","<<tpcol[indata[i]]<<endl;
                myt.add(tcol[indata[i]][k],1);
                cout<<tcol[indata[i]][k]<<"+1:"<<myt.sum(tcol[indata[i]][k])-myt.sum(tcol[indata[i]][k]-1)<<endl;
            }
        }
        while(myask[tpask+1].rt==i)
        {
            tpask++;
            myask[tpask].ans=myt.sum(i)-myt.sum(myask[tpask].lt-1);
            //cout<<tpask<<":"<<myask[tpask].ans<<endl;
            for(int p=tfirstb;p;p=tnextb[p])
            {
                tl=binaryfind(tcol[p],1,pcol[p]+1,myask[tpask].lt-1);
                tr=binaryfind(tcol[p],1,pcol[p]+1,myask[tpask].rt);
                myask[tpask].ans+=(tr-tl)*(tr-tl+1)/2;
                //cout<<"FindC:"<<p<<"("<<myask[tpask].lt<<","<<myask[tpask].rt<<")"<<(tr-tl)*(tr-tl+1)/2<<endl;
            }
        }
    }
    
    sort(myask+1,myask+nm+1,cmp1);
    long long tu,td,tg;
    
    for each(i,nm)
    {
        tu=myask[i].ans;
        td=(myask[i].rt-myask[i].lt)*(myask[i].rt-myask[i].lt+1)/2;
        if(tu==0)tg=td;else tg=gcd(tu,td);
        printf("%d/%d\n",(int)(tu/tg),(int)(td/tg));
    }
}

        
