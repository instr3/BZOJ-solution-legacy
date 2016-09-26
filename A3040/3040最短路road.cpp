#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int nh;
struct enode{int to,w,next;}mye[10000001];
struct vnode{int first;}myv[1000001];
int n,nm;
struct hnode
{
    int n;long long w;
    bool operator < (hnode ano)const
    {
        return w<ano.w;
    }
}heap[1000001];//小顶堆,排序后为前大后小 
int hplace[1000001];
inline void swapheap(int ih1,int ih2)
{
    hplace[heap[ih1].n]=ih2;
    hplace[heap[ih2].n]=ih1;
    long long tv=heap[ih1].w;heap[ih1].w=heap[ih2].w;heap[ih2].w=tv;
    int tv2=heap[ih1].n;heap[ih1].n=heap[ih2].n;heap[ih2].n=tv2;
    
    //swap(heap[ih1],heap[ih2]);
}
inline void pushheap()
{
    int th=nh;
    while(th>1&&heap[th]<heap[th>>1])
    swapheap(th,th>>1);
}
inline void popheap()
{
    int th=1;
    while((th<<1)<=nh)
    {
        if((th<<1)+1<=nh&&heap[(th<<1)+1]<heap[th<<1])
        {
            swapheap(th,(th<<1)+1);
            th=(th<<1)+1;
        }
        else
        {
            swapheap(th,th<<1);
            th=th<<1;
        }
    }
    swapheap(th,nh);
}
inline void adjustheap(int ih)//保证ih被增加 
{
    int th=ih;
    while(th>1&&heap[th]<heap[th>>1])
    swapheap(th,th>>1),th>>=1;
}
int main()
{
    freopen("3040.in","r",stdin);
    freopen("3040.out","w",stdout);
    scanf("%d%d",&n,&nm);
    int nt,nrxa,nrxc,nrya,nryc,nrp;
    long long tx=0,ty=0;
    scanf("%d%d%d%d%d%d",&nt,&nrxa,&nrxc,&nrya,&nryc,&nrp);
    int pf,pt,pw;
    for each(i,nt)
    {
        tx=(tx*nrxa+nrxc)%nrp;
        ty=(ty*nrya+nryc)%nrp;
        pf=min(tx%n+1,ty%n+1);
        pt=max(tx%n+1,ty%n+1);
        pw=100000000-100*pf;
        mye[i].to=pt;
        mye[i].w=pw;
        mye[i].next=myv[pf].first;myv[pf].first=i;
    
    }
    for every(i,nt+1,nm)
    {
        scanf("%d%d%d",&pf,&pt,&pw);
        mye[i].to=pt;
        mye[i].w=pw;
        mye[i].next=myv[pf].first;myv[pf].first=i;
    }
    heap[++nh]=(hnode){1,0};
    for every(i,2,n)
    {
        heap[++nh]=(hnode){i,999999999999999999LL};
        hplace[i]=nh;
    }
    for each(i,n)
    {
        popheap();
        pf=heap[nh].n;
        //cout<<pf<<":"<<heap[nh].w<<endl;
        if(pf==n)
        {
            printf("%lld",heap[nh].w);
            return 0;
        }
        for(int p=myv[pf].first;p;p=mye[p].next)
        {
            pt=mye[p].to;
            if(heap[hplace[pt]].w>heap[nh].w+mye[p].w)
            {
                heap[hplace[pt]].w=heap[nh].w+mye[p].w;
                adjustheap(hplace[pt]);
            }
        }
        --nh;
    }
        
}
