#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=n;++i)
#define MAXN 1001
struct enode{int w,to,next;}mye[MAXN];int pmye=1;
struct vnode{int first,h;int rfirst;}myv[MAXN];int pmyv=1;
struct queue
{
    int fr,bk,data[MAXN],h[MAXN];queue(){bk=1;}
    inline bool empty() const{return bk==fr+1;}
}myq;
int n,nm;
bool tprevisit[MAXN];
int road[MAXN],proad;
int roade[MAXN];
int tot;
inline void addedge(int pf,int pt,int pw)
{
    cout<<"Add:"<<pf<<","<<pt<<","<<pw<<endl;
    mye[++pmye].to=pt;
    mye[pmye].w=pw;
    mye[pmye].next=myv[pf].first;
    myv[pf].first=pmye;
    
    mye[++pmye].to=pf;
    mye[pmye].w=0;
    mye[pmye].next=myv[pt].first;
    myv[pt].first=pmye;
}/*
inline void preSAP()
{
    int pf,ph;
    tprevisit[n]=true;
    myq.data[++myq.fr]=n;
    while(!myq.empty())
    {
        pf=myq.data[myq.bk];
        ph=myq.h[myq.bk++];
        myv[pf].h=ph;
        //cout<<pf<<":"<<ph<<endl;
        for(int p=myv[pf].rfirst;p;p=myer[p].next)
        {
            if(!tprevisit[myer[p].to])
            {
                tprevisit[myer[p].to]=true;
                myq.data[++myq.fr]=myer[p].to;
                myq.h[myq.fr]=ph+1;
            }
        }
    }
}*/
void SAP()
{
    int pf,pt=0;
    int minw;
    for(int iT=1;iT<=4;++iT)
    {
        proad=1;road[1]=1;
        pf=1;
        minw=99999999;
        while(pf!=n)
        {
            for(int p=myv[pf].first;p;p=mye[p].next)
            if(mye[p].w>0)
            {
                pt=mye[p].to;
                
                if(myv[pt].h==myv[pf].h-1)
                {
                    pf=pt;
                    road[++proad]=pf;
                    roade[proad]=p;
                    minw=min(minw,mye[p].w);
                    goto search_done;
                }
            }
            myv[pt].h++;pf=road[--proad];
            if(proad==0)goto search_redo;
            search_done:;
        }
        cout<<minw<<":";
        for each(i,proad)
        {
            mye[roade[i]].w-=minw;
            mye[roade[i]^1].w+=minw;
            cout<<road[i]<<" ";
        }
        cout<<endl;
        tot+=minw;
        search_redo:;
    }
}
int pnf[101],pnd[101],pnc[101];
int main()
{
    freopen("1711.in","r",stdin);
    freopen("1711.out","w",stdout);
    int nc,nf,nd;
    scanf("%d%d%d",&nc,&nf,&nd);
    for each(i,nf)
    {
        pnf[i]=++pmyv;
        addedge(1,pnf[i],1);
    }
    for each(i,nc)pnc[i]=++pmyv;
    for each(i,nd)
    {
        pnd[i]=++pmyv;
    }
    int tpf,tpd;
    int tnf,tnd;
    for each(i,nc)
    {
        pnc[i]=++pmyv;
        scanf("%d%d",&tpf,&tpd);
        for each(j,tpf)
        {
            scanf("%d",&tnf);
            addedge(pnf[tnf],pnc[i],1);
        }
        for each(j,tpf)
        {
            scanf("%d",&tnd);
            addedge(pnc[i],pnd[tnd],1);
        }
    }
    n=++pmyv;
    for each(i,nd)
    {
        addedge(pnd[i],n,1);
    }
    //preSAP();
    SAP();
}
