#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=n;++i)
#define MAXN 1000002
struct enode{int w,to,next;}mye[6000002],myer[MAXN];int pmye=1;
struct vnode{int first,h;int rfirst;}myv[MAXN];int pmyer=0;
struct queue
{
    int fr,bk,data[MAXN],h[MAXN];queue(){bk=1;}
    inline bool empty() const{return bk==fr+1;}
}myq;
int n,nm;
bool tprevisit[MAXN];
int road[MAXN],proad;
int roade[MAXN];
int hcount[MAXN];
int res;
void addedge(int pf,int pt,int pw)
{
    mye[++pmye].to=pt;
    mye[pmye].w=pw;
    mye[pmye].next=myv[pf].first;
    myv[pf].first=pmye;
    
    mye[++pmye].to=pf;
    mye[pmye].w=pw;
    mye[pmye].next=myv[pt].first;
    myv[pt].first=pmye;
    
    myer[++pmyer].to=pf;
    myer[pmyer].w=0;
    myer[pmyer].next=myv[pt].rfirst;
    myv[pt].rfirst=pmyer;
}
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
        hcount[ph]++;
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
}
void SAP()
{
    int pf,pt=0;
    int minw;
    for(;;)
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
            hcount[myv[pf].h]--;
            if(hcount[myv[pf].h]==0)
            {
                //cout<<myv[pf].h<<"Died!Game Over"<<endl;
                return;
            }
            myv[pf].h++;
            hcount[myv[pf].h]++;
            if(myv[pf].h>=n)return;
            //printf("dis[%d]->%d!\n",pf,myv[pf].h);
            pf=road[--proad];
            if(proad==0)goto search_redo;
            search_done:;
        }
        //cout<<minw<<":";
        for each(i,proad)
        {
            mye[roade[i]].w-=minw;
            mye[roade[i]^1].w+=minw;
            //cout<<road[i]<<" ";
        }
        //cout<<endl;
        res+=minw;
        search_redo:;
    }
}
int main()
{
    freopen("1001.in","r",stdin);
    freopen("1001.out","w",stdout);
    int na,nb;
    scanf("%d%d",&na,&nb);
    if(na==1&&nb==1)
    {
        cout<<"0";
        return 0;
    }
    n=na*nb;
    #define pos(x,y) (((x)-1)*nb+(y))
    int pw;
    for(int ia=1;ia<=na;++ia)
    for(int ib=1;ib<=nb-1;++ib)
    {
        scanf("%d",&pw);
        addedge(pos(ia,ib),pos(ia,ib+1),pw);
    }
    for(int ia=1;ia<=na-1;++ia)
    for(int ib=1;ib<=nb;++ib)
    {
        scanf("%d",&pw);
        addedge(pos(ia,ib),pos(ia+1,ib),pw);
    }
    for(int ia=1;ia<=na-1;++ia)
    for(int ib=1;ib<=nb-1;++ib)
    {
        scanf("%d",&pw);
        addedge(pos(ia,ib),pos(ia+1,ib+1),pw);
    }
    preSAP();
    SAP();
    printf("%d",res);
}
