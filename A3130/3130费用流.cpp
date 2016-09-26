#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n,nm;
double nw;
struct enode{int fr,to,next,c;double f;}mye[2002];int pmye=1;
struct vnode{int first;}myv[101];
int th[101];
int thct[101];
int testk[2002],pestk;
double tot;
double tlim;
void addedge(int pf,int pt,int pc)
{
    mye[++pmye].to=pt;
    mye[pmye].fr=pf;
    mye[pmye].c=pc;
    mye[pmye].f=0;
    mye[pmye].next=myv[pf].first;myv[pf].first=pmye;
    
    mye[++pmye].to=pf;
    mye[pmye].fr=pt;
    mye[pmye].c=0;
    mye[pmye].f=0;
    mye[pmye].next=myv[pt].first;myv[pt].first=pmye;
    
}
    
void sap(double ilim)
{
    int pf,pt;
    double tminf;
    for each(i,n)thct[i]=0;
    for each(i,n)th[i]=0;
    for each(i,pmye)mye[i].f=0.0;
    thct[0]=n;
    tot=0;
    while(true)
    {
        pestk=0;
        pf=1;
        while(true)
        {
            for(int p=myv[pf].first;p;p=mye[p].next)
            {
                pt=mye[p].to;
                if(min((double)mye[p].c,ilim)-mye[p].f>0)
                {
                    if(th[pf]-1!=th[pt])continue;
                    testk[++pestk]=p;
                    pf=pt;
                    if(pf==n)
                    {
                        tminf=99999999;
                        for each(i,pestk)
                        {
                            p=testk[i];
                            tminf=min(tminf,min((double)mye[p].c,ilim)-mye[p].f);
                            //cout<<mye[p].fr<<" ";
                        }
                        //cout<<n<<":"<<tminf<<endl;
                        tot+=tminf;
                        //minf=min(minf,ilim);
                        for each(i,pestk)
                        {
                            p=testk[i];
                            mye[p].f+=tminf;
                            mye[p^1].f-=tminf;
                        }
                        pestk=0;
                        goto die;
                    }
                    goto recalculate;
                }
            }
            thct[th[pf]]--;
            if(thct[th[pf]]==0)return;
            th[pf]++;
            thct[th[pf]]++;
            /*if(th[pf]>n)
            {
                return;
            }*/
            if(pestk)
            pf=mye[testk[pestk--]].fr;
            else goto die;
            recalculate:;
        }
        die:;
    }
}

int main()
{
    freopen("3130.in","r",stdin);
    freopen("3130.out","w",stdout);
    scanf("%d%d",&n,&nm);cin>>nw;
    int pf,pt,pc;
    for each(i,nm)
    {
        scanf("%d%d%d",&pf,&pt,&pc);
        addedge(pf,pt,pc);
    }
    int stot;
    sap(9e99);printf("%d\n",stot=(int)tot);
    double tl=0,tr=(double)tot,tm;
    while(tr-tl>10e-6)
    {
        tm=(tl+tr)*0.5;
        sap(tm);
        if(stot-tot>10e-6)
        {
            tl=tm;
        }
        else
        {
            tr=tm;
        }
    }
    //sap(20);
    //cout<<tot<<endl;
    printf("%.5f",tl*nw);
    
}
