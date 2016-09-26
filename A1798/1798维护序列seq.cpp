#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
struct tnode
{
    //int l,r;
    long long mulnum,addnum;
    long long sum;
}myt[400000];
int datain[100000];
int n,nmod,nm;
void build(int it,int il,int ir)
{
    //myt[it].l=il;
    //myt[it].r=ir;
    myt[it].mulnum=1;
    if(il+1==ir)
    {
        myt[it].addnum=myt[it].sum=datain[il]%nmod;
        //cout<<it<<":"<<il<<":"<<datain[il]<<endl;
        return;
    }
    build(it<<1,il,(il+ir)>>1);
    build((it<<1)+1,(il+ir)>>1,ir);
    myt[it].sum=(myt[it<<1].sum+myt[(it<<1)+1].sum)%nmod;
}
inline void mark(int it,int il,int ir,int ipt,long long ipnum)
{
    ipnum%=nmod;
    if(ipt==2)
    {
        myt[it].addnum=(myt[it].addnum+ipnum)%nmod;
        myt[it].sum=(myt[it].sum+ipnum*(ir-il))%nmod;
    }
    else 
    {
        myt[it].addnum=(myt[it].addnum*ipnum)%nmod;
        myt[it].mulnum=(myt[it].mulnum*ipnum)%nmod;
        myt[it].sum=(myt[it].sum*ipnum)%nmod;
    }
    
    //myt[it].sum=(myt[it<<1].sum+myt[(it<<1)+1].sum)
    //  *myt[it].mulnum+myt[it].addnum;
    
   // printf("CHG:%d-%d:%d\n",il,ir,myt[it].sum);
    //cout<<"  "<<myt[it<<1].sum<<","<<myt[(it<<1)+1].sum<<endl;
}
void pushdown(int it,int il,int ir)
{
    mark(it<<1,il,(il+ir)>>1,1,myt[it].mulnum);
    mark(it<<1,il,(il+ir)>>1,2,myt[it].addnum);
    mark((it<<1)+1,(il+ir)>>1,ir,1,myt[it].mulnum);
    mark((it<<1)+1,(il+ir)>>1,ir,2,myt[it].addnum);
    myt[it].mulnum=1;
    myt[it].addnum=0;
    myt[it].sum=(myt[it<<1].sum+myt[(it<<1)+1].sum)%nmod;
      //*myt[it].mulnum+myt[it].addnum;
}
void change(int it,int il,int ir,int pl,int pr,int ipt,long long ipnum)
{
    //cout<<it<<","<<il<<","<<ir<<endl;
    if(il>=pr||ir<=pl)return;
    if(il>=pl&&ir<=pr)
    {
        mark(it,il,ir,ipt,ipnum);
        return;
    }
    if(myt[it].mulnum!=1||myt[it].addnum!=0)
      pushdown(it,il,ir);
    change(it<<1,il,(il+ir)>>1,pl,pr,ipt,ipnum);
    change((it<<1)+1,(il+ir)>>1,ir,pl,pr,ipt,ipnum);
    myt[it].sum=((myt[it<<1].sum+myt[(it<<1)+1].sum)
      *myt[it].mulnum+myt[it].addnum)%nmod;
}
long long getsum(int it,int il,int ir,int pl,int pr)
{
    if(il>=pr||ir<=pl)return 0;
    if(il>=pl&&ir<=pr)
    {
        //printf("GET:%d-%d:%d\n",il,ir,myt[it].sum);
        return myt[it].sum;
    }
    if(myt[it].mulnum!=1||myt[it].addnum!=0)
      pushdown(it,il,ir);
    
    return (getsum(it<<1,il,(il+ir)>>1,pl,pr)+
      getsum((it<<1)+1,(il+ir)>>1,ir,pl,pr))%nmod;
}
/*
void printtree(int it,int il,int ir,int id,int iw)
{
    iw=iw*myt[it].mulnum+myt[it].addnum;
    
    if(it==1)
    {
        printf("Tree[%d]:%d\n",id,iw);
        return;
    }
    printtree(it/2,myt[it/2].l,myt[it/2].r,id,iw);
}*/
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    scanf("%d%d",&n,&nmod);
    for(int i=0;i<n;++i)
    {
        scanf("%d",&datain[i]);
    }
    build(1,0,n);
    scanf("%d",&nm);
    int pf,pt,pip,pnum;
    for(int i=1;i<=nm;++i)
    {
        scanf("%d%d%d",&pip,&pf,&pt);
        if(pip!=3)
        {
            scanf("%d",&pnum);
            change(1,0,n,pf-1,pt,pip,pnum);
        }
        else
        {
            printf("%I64d\n",getsum(1,0,n,pf-1,pt));
        }
        
    }
   /*for(int ip=0,i;ip<100;++ip)
    {
        if(myt[ip].l+1==myt[ip].r)
        {
            i=myt[ip].l;
            printtree(ip,i,i+1,i,0);
        }
    }*/
    
}
