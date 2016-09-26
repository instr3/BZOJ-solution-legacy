#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
struct enode{int to,f,c,next;}mye[80002];int pmye=1;
struct vnode{int first,h;}myv[10001];
int testk[800002];int pestk;
int n;
int tot;
int th[10001];
inline void addedge(int pf,int pt,int pw)
{
    //cout<<pf<<","<<pt<<","<<pw<<endl;
    mye[++pmye].to=pt;
    mye[pmye].f=0;
    mye[pmye].c=pw;
    mye[pmye].next=myv[pf].first;
    myv[pf].first=pmye;
    
    mye[++pmye].to=pf;
    mye[pmye].f=0;
    mye[pmye].c=0;
    mye[pmye].next=myv[pt].first;
    myv[pt].first=pmye;
}
void sap()
{
    int pf,pt;
    bool tfind;
    int minw;
    th[0]=n;
    while(true)
    {
        pestk=0;
        pf=1;
        while(true)
        {
            tfind=false;
            for(int p=myv[pf].first;p;p=mye[p].next)
            {
                pt=mye[p].to;
                if(mye[p].f<mye[p].c&&myv[pf].h==myv[pt].h+1)
                {
                    testk[++pestk]=p;
                    pf=pt;
                    tfind=true;
                    if(pt==n)
                    {
                        minw=99999999;
                        for each(i,pestk)
                        {
                            minw=min(minw,mye[testk[i]].c-mye[testk[i]].f);
                        }
                        tot+=minw;
                        //cout<<minw<<":1 ";
                        for each(i,pestk)
                        {
                            mye[testk[i]].f+=minw;
                            mye[testk[i]^1].f-=minw;
                            //cout<<mye[testk[i]].to<<" ";
                        }
                        //cout<<endl;
                        pestk=0;
                        goto m_break;
                    }
                    break;
                }
            }
            if(!tfind)
            {
                th[myv[pf].h]--;
                if(!th[myv[pf].h])return;
                myv[pf].h++;
                th[myv[pf].h]++;
                if(myv[pf].h>n)return;
                if(pestk>=2)
                {
                    pestk--;
                    pf=mye[testk[pestk]].to;
                    continue;
                }
                else break;
            }
        }
m_break:; 
    }
}
int ps,pt;
int indata[2001];
int pin[2001],pout[2001];
int task()
{
    ps=n=2;
    pt=n=3;
    addedge(pt,ps,99999999);
    int nt;scanf("%d",&nt);
    for each(i,nt)
    {
        scanf("%d",&indata[i]);
        pin[i]=++n;
        pout[i]=++n;
        //addedge(pin[i],pout[i],0);
        addedge(ps,pin[i],1);
        addedge(pout[i],pt,1);
    }
    ++n;
    for each(i,nt)
    {
        for every(j,i+1,nt)
        {
            if(indata[i]<indata[j])
            {
                addedge(pout[i],pin[j],1);
            }
        }
    }
    for each(i,nt)
    {
        addedge(1,pout[i],1);
        addedge(pin[i],n,1);
    }
    sap();
    cout<<tot<<endl;
}
        
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    task();
    char *tc=new char[5]();
}
