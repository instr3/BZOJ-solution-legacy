#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
struct carr
{
    int indata[100001];//数据结构：块状数组 
    int n;
    struct cbox
    {
        int size;
        int fr;
        int sum;
        bool rev;
    }mybox[1001];int pmybox;
    void print()
    {
        for each(i,n)
        {
            cout<<indata[i]<<" ";
        }
        cout<<endl;
        for each(i,pmybox)
        {
            cout<<"["<<mybox[i].fr<<"-"<<mybox[i].fr+mybox[i].size-1<<"]"<<":"<<mybox[i].sum<<","<<mybox[i].rev<<endl;
        }
    }
    void init(int in,int insize)
    {
        n=in;
        for(int i=1;i<=n;i+=insize)
        {
            mybox[++pmybox].size=insize;
            mybox[pmybox].fr=i;
            mybox[pmybox].sum=0;
        }
        mybox[pmybox].size=n-mybox[pmybox].fr+1;
    }
    void changenode(int ik)//,int iw)
    {
        int iw;
        if(indata[ik])iw=-1;else iw=1;
        indata[ik]+=iw;
        int tk=0;
        for each(tpb,pmybox)
        {
            tk+=mybox[tpb].size;
            if(tk>=ik)
            {
                mybox[tpb].sum+=iw;
                return;
            }
            
        }
    }
    void change(int il,int ir)
    {
        int res=0;
        for each(tpb,pmybox)
        {
            if(mybox[tpb].fr>ir||(mybox[tpb].fr+mybox[tpb].size-1)<il)continue;
            //cout<<mybox[tpb].fr<<"->"<< mybox[tpb].fr+mybox[tpb].size-1<<endl;
            if(mybox[tpb].fr>=il&&(mybox[tpb].fr+mybox[tpb].size-1)<=ir)
            {
                mybox[tpb].sum=mybox[tpb].size-mybox[tpb].sum;
                mybox[tpb].rev^=1;
            }
            else
            {
                if(mybox[tpb].fr<=il&&(mybox[tpb].fr+mybox[tpb].size-1)>=ir)
                {
                    res=0;
                    for every(j,il,ir)
                    res+=(indata[j]==0?1:-1),indata[j]^=1;
                    mybox[tpb].sum+=mybox[tpb].rev?-res:res;
                    continue;
                }
                if(mybox[tpb].fr<=il) 
                {
                    res=0;
                    for every(j,il,mybox[tpb].fr+mybox[tpb].size-1)
                    res+=(indata[j]==0?1:-1),indata[j]^=1;
                    mybox[tpb].sum+=mybox[tpb].rev?-res:res;
                }
                else
                {
                    res=0;
                    for every(j,mybox[tpb].fr,ir)
                    res+=(indata[j]==0?1:-1),indata[j]^=1;
                    mybox[tpb].sum+=mybox[tpb].rev?-res:res;
                }
                    
            }
        }
    }
    int ask(int il,int ir)
    {
        int res=0;
        for each(tpb,pmybox)
        {
            if(mybox[tpb].fr>ir||(mybox[tpb].fr+mybox[tpb].size-1)<il)continue;
            //cout<<mybox[tpb].fr<<"->"<< mybox[tpb].fr+mybox[tpb].size-1<<endl;
            if(mybox[tpb].fr>=il&&(mybox[tpb].fr+mybox[tpb].size-1)<=ir)
            {
                res+=mybox[tpb].sum;
            }
            else
            {
                if(mybox[tpb].fr<=il&&(mybox[tpb].fr+mybox[tpb].size-1)>=ir)
                {
                    for every(j,il,ir)
                    res+=mybox[tpb].rev?!indata[j]:indata[j];
                    continue;
                }
                if(mybox[tpb].fr<=il) 
                for every(j,il,mybox[tpb].fr+mybox[tpb].size-1)
                res+=mybox[tpb].rev?!indata[j]:indata[j];
                else
                for every(j,mybox[tpb].fr,ir)
                res+=mybox[tpb].rev?!indata[j]:indata[j];
            }
        }
        return res;
    }
}mya;
int main()
{
    freopen("1230.in","r",stdin);
    freopen("1230.out","w",stdout);
    //int n;
    int n,nm;scanf("%d%d",&n,&nm);
    int tfr,tto;
    mya.init(n,(int)sqrt(n));
    //mya.change(2,7);
    //mya.change(5,8);
    //mya.print();
    //cout<<mya.ask(5,10);
    //return 0;
    int top;
    for each(i,nm)
    {
        scanf("%d",&top);
        scanf("%d%d",&tfr,&tto);
        if(top==0)
        {
            mya.change(tfr,tto);
        }
        else
        {
            printf("%d\n",mya.ask(tfr,tto));
        }
    }
}


//历史版本
/* 
int n,nm,n2;           //100000
struct tnode
{
    int l,r;
    int mk,sum;
}tdata[262145];//1-262144 重口味线段树 
int main()
{
    freopen("1230.in","r",stdin);
    freopen("1230.out","w",stdout);
    scanf("%d%d",&n,&nm);
    n2=(1<<((int)(log2(n+1))+1));
    int ipi,il,ir; 
    for(int i=0;i<n2;++i)
    {
        tdata[i+n2].l=i;
        tdata[i+n2].r=i+1;
        cout<<i+n2<<":"<<i<<","<<i+1<<endl;
    }
    for(int i=0;i+n2;--i)
    {
        tdata[i+n2].l=tdata[(i+n2)*2].l;
        tdata[i+n2].r=tdata[(i+n2)*2+1].r;
        cout<<i+n2<<":"<<tdata[i+n2].l<<","<<tdata[i+n2].r<<endl;
    }
    for(int i=1;i<=nm;++i)
    {
        scanf("%d%d%d",&ipi,&il,&ir);
        if(ipi==1)
        {
            for(il=il+n2-1,ir=ir+n2+1;il^ir^1;il>>=1,ir>>=1)
            {
                if(il+1<n2)tdata[il+1].sum=tdata[(il+1)<<1].sum+tdata[((il+1)<<1)+1].sum;
                if(~il&1)
                {
                    tdata[il+1].mk=!tdata[il+1].mk;
                    cout<<il+1<<"Chg"<<endl;
                }
                if( ir&1)
                {
                    tdata[ir-1].mk=!tdata[ir-1].mk;
                    cout<<ir-1<<"Chg"<<endl;
                }
                
            }
        }
        else
        {
            for(int ti=il+n2;ti>1;ti>>=1)
            {
                if(tdata[ti].mk)
        }
    }
    bool topen;
    for(int i=1;i<n2-1;++i)
    {
        topen=false;
        for(int ti=i+n2;ti>1;ti>>=1)
        {
            if(tdata[ti].mk)topen=!topen;
        }
        cout<<"Debug["<<i<<"]:"<<topen<<endl;
    }
}*/
