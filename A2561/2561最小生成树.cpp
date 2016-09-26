#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
struct enode{int fr,to,c,f,w,next;}mye[800002];int pmye=1;
struct vnode{int first,h;}myv[20001];
int n,nm;
int testk[800002],pestk;
int th[20001];
int ttw;
inline void addedge(int pf,int pt,int pw)
{
    mye[++pmye].to=pt;
    mye[pmye].fr=pf;
    mye[pmye].w=pw;
    mye[pmye].c=1;
    mye[pmye].f=0;
    mye[pmye].next=myv[pf].first;
    myv[pf].first=pmye;
    
    mye[++pmye].to=pf;
    mye[pmye].fr=pt;
    mye[pmye].w=pw;
    mye[pmye].c=0;
    mye[pmye].f=0;
    mye[pmye].next=myv[pt].first;
    myv[pt].first=pmye;
    
}
struct cflow
{
    cflow(){pmye=1;}
    int n;
    int tot;
    //enode mye[100001];int pmye;
    //vnode myv[100001];

    int ifr,ito;
    void sap(bool ib)
    {
        memset(th,0,sizeof th);
        th[0]=n;
        int pf,pt,pe;
        int minw;
        while(true)
        {
            restart:;
            pestk=0;
            pf=ifr;
            while(true)
            {
                for(int p=myv[pf].first;p;p=mye[p].next)
                {
                    pt=mye[p].to;
                    if(mye[p].c-mye[p].f<=0)continue;
                    if(ib)
                    {if(mye[p].w<=ttw)continue;}
                    else {if(mye[p].w>=ttw)continue;}
                    if(myv[pf].h==myv[pt].h+1)
                    {
                        testk[++pestk]=p;
                        
                        pf=pt;
                        if(pf==ito)
                        {
                            minw=99999999;
                            for(int i=pestk;i;--i)
                            {
                                pe=testk[i];
                                minw=min(minw,mye[pe].c-mye[pe].f);
                            }
                            //cout<<minw<<":"<<ito<<" ";
                            tot+=minw;
                            for(int i=pestk;i;--i)
                            {
                                pe=testk[i];
                                mye[pe].f+=minw;
                                mye[pe^1].f-=minw;
                                //cout<<mye[pe].fr<<" ";
                            }
                            //cout<<endl;
                            
                            goto restart;
                        }
                        goto die;
                    }
                }
                th[myv[pf].h]--;
                if(th[myv[pf].h]==0)return;
                myv[pf].h++;
                th[myv[pf].h]++;
                pestk--;
                pf=mye[testk[pestk]].to;
                if(pestk<=0)break;
                die:;
            }
        }
    }
}myf1,myf2;
int main()
{
    freopen("2561.in","r",stdin);
    freopen("2561.out","w",stdout);
    scanf("%d%d",&n,&nm);
    int pf,pt,pw;
    for(int i=1;i<=nm;++i)
    {
        scanf("%d%d%d",&pf,&pt,&pw);
        addedge(pt,pf,pw);
        addedge(pf,pt,pw);
    }
    scanf("%d%d%d",&pf,&pt,&ttw);
    myf1.n=myf2.n=n;
    myf1.ifr=myf2.ifr=pf;
    myf1.ito=myf2.ito=pt;
    myf1.sap(0);
    //cout<<"--"<<endl;
    for each(i,pmye)mye[i].f=0;
    for each(i,n)myv[i].h=0;
    myf2.sap(1);
    cout<<myf1.tot+myf2.tot<<endl;
}
    
