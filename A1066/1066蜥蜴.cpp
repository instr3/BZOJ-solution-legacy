#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=n;++i)
#define MAXN 10001
struct enode{int w,to,next;}mye[2*MAXN+10],myer[MAXN];int pmye=1;
struct vnode{int first,h;int rfirst;}myv[MAXN];
struct queue
{
    int fr,bk,data[MAXN],h[MAXN];queue(){bk=1;}
    inline bool empty() const{return bk==fr+1;}
}myq;
int n,nm;
bool tprevisit[MAXN];
int road[MAXN],proad;
int roade[MAXN];
int res;
void addedge(int pf,int pt,int pw)
{
    //cout<<pf<<","<<pt<<","<<pw<<endl;
    mye[++pmye].to=pt;
    mye[pmye].w=pw;
    mye[pmye].next=myv[pf].first;
    myv[pf].first=pmye;
    
    mye[++pmye].to=pf;
    mye[pmye].w=0;
    mye[pmye].next=myv[pt].first;
    myv[pt].first=pmye;
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
                //cout<<pt<<endl;
                if(myv[pt].h==myv[pf].h-1)
                {
                    pf=pt;
                    road[++proad]=pf;
                    roade[proad]=p;
                    minw=min(minw,mye[p].w);
                    goto search_done;
                }
            }
            myv[pf].h++;
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
struct xynode
{
    int x,y;
    int w;
}myxy[401];int pmxy;
int map[50][50]; 
int main()
{
    int na,nb,nd;
    freopen("1066.in","r",stdin);
    freopen("1066.out","w",stdout);
    scanf("%d%d%d",&na,&nb,&nd);
    char tc[50];
    int allcount=0;
    n=1000;
    for(int i=1;i<=na;++i)
    {
        scanf("%s",&tc[0]);
        for(int j=1;j<=nb;++j)
        {
            if(tc[j-1]!='0')
            {
                myxy[++pmxy].x=i;
                myxy[pmxy].y=j;
                myxy[pmxy].w=tc[j-1]-'0';
                map[i][j]=pmxy;
                addedge((pmxy+1)*2-1,(pmxy+1)*2,myxy[pmxy].w);
                if(i<=nd||j<=nd||(na+1-i)<=nd||(nb+1-j)<=nd)
                addedge((pmxy+1)*2,1000,99999999);
            }
        }
    }
    #define abz(x) ((x)>0?(x):(-(x)))
    for(int i=1;i<=pmxy;++i)
    for(int j=1;j<=pmxy;++j)
    if(i!=j)
    {
        if(abz(myxy[i].x-myxy[j].x)+abz(myxy[i].y-myxy[j].y)<=nd)
        {
            addedge((i+1)*2,(j+1)*2-1,99999999);
            addedge((j+1)*2,(i+1)*2-1,99999999);
        }
    }

    for(int i=1;i<=na;++i)
    {
        scanf("%s",&tc[0]);
        for(int j=1;j<=nb;++j)
        {
            if(tc[j-1]=='L')
            {
                addedge(1,(map[i][j]+1)*2-1,1);
                ++allcount;
            }
        }
    }
    SAP();
    cout<<allcount-res<<endl;
}
