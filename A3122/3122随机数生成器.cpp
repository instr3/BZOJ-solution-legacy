#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int nmod,na,nb,nx1,npage;
#define hmod 999997
struct hashtable
{
    struct lnode{int num,r,next;}myl[100000];int pmyl;
    struct hnode{int first;}myh[1000001];
    inline void add(int inum,int ir)
    {
        //cout<<"Add:"<<inum<<","<<ir<<endl;
        int tenhash=ir%hmod;
        myl[++pmyl].num=inum;
        myl[pmyl].r=ir;
        myl[pmyl].next=myh[tenhash].first;
        myh[tenhash].first=pmyl;
    }
    inline int ask(int ir)
    {
        int tenhash=ir%hmod;
        for(int p=myh[tenhash].first;p;p=myl[p].next)
        {
            if(myl[p].r==ir)
            {
                return myl[p].num;
            }
        }
        return -1;
    }
    inline void clean()
    {
        memset(myh,0,sizeof myh);
        pmyl=0;
    }
}thash;
inline int fastmod(int ib,int ip)
{
    long long res=1;
    while(ip)
    {
        if(ip%2)
        {
            res=(res*ib)%nmod;
        }
        ib=(ib*(long long)ib)%nmod;
        ip/=2;
    }
    return res;
}
int tr1,tr2;
inline int exgcd(long long ia,long long ib)
{
    long long x0=1,y0=0,x1=0,y1=1,x2,y2;
    long long ir=ia%ib,ip=ia/ib;
    while(ib)
    {
        ir=ia%ib;ip=ia/ib;
        x2=x0-ip*x1;
        y2=y0-ip*y1;
        x0=x1;y0=y1;x1=x2;y1=y2;
        ia=ib;ib=ir;
    }
    return (y0%nmod+nmod)%nmod;
}
void task()
{
    thash.clean();
    scanf("%d%d%d%d%d",&nmod,&na,&nb,&nx1,&npage);
    if(nx1==npage){printf("%d\n",1);return;}
    if(na==1)
    {
        npage=(npage-nx1+nmod)%nmod;
        if(nb==0)
        {
            printf("-1\n");return;
        }
        else
        {
            printf("%d\n",1+(exgcd(nmod,nb)*(long long)npage)%nmod);
            return;
        }
        //cout<<"Solve:"<<tx<<"*"<<na<<"^? mod "<<nmod<<"="<<npage<<endl;
    }
    int tx=(nx1*(long long)(na-1)+nb)%nmod;npage=(npage*(long long)(na-1)+nb+nmod)%nmod;
    
    
    /*for every(i,2,nmod)
    {
        tx=(na*(long long)tx)%nmod;
        if(tx==npage)
        {
            printf("%d\n",i);
            return;
        }
        //if(tx==nx1)break;
    }
    printf("-1\n");return;*/
    if(na==0)
    {
        if(npage==0)
        {
            printf("2\n");return;
        }
        else printf("-1\n");return;
    }
    if(tx==0)
    {
        if(npage==0)
        {
            printf("2\n");return;
        }
        else printf("-1\n");return;
    }
    int sqrtmod=(int)sqrt((double)nmod);
    int nblock=(nmod-1)/sqrtmod+1;
    int tfast;
    for each(i,nblock)
    {
        tfast=(tx*(long long)fastmod(na,i*sqrtmod))%nmod;
        //cout<<i*sqrtmod<<":"<<tfast<<endl;
        if(thash.ask(tfast)==-1)
        thash.add(i*sqrtmod,tfast);
    }
    tx=npage;
    int minans=1999999999;
    for every(i,0,sqrtmod-1)
    {
        //cout<<"Asking:"<<i<<":"<<tx<<endl;
        if(thash.ask(tx)!=-1)
        {
            minans=min(minans,thash.ask(tx)-i+1);
        }
        tx=(na*(long long)tx)%nmod;
        //if(tx==nx1)break;
    }
    if(minans==1999999999)
    printf("-1\n");
    else printf("%d\n",minans);
}
int main()
{
    freopen("3122.in","r",stdin);
    freopen("3122.out","w",stdout);
    int nt;scanf("%d",&nt);
    for each(i,nt)task();
}
