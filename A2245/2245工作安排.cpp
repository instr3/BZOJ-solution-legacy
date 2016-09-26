#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=n;++i)
#define MAXN 10001
#define OO 9999999
struct enode{long long w;int c,fr,to,next;}mye[100000];int pmye=1;
struct vnode{long long wp;int pre,first;}myv[MAXN];int pmyv=1;
//int mys[MAXN],pmys;
struct queue
{
    int ft,bk;
    int d[MAXN];
    queue(){ft=1;};
    inline void clean(){ft=1;bk=0;};
    inline void push(int iv)
    {
        ++ft;if(ft==MAXN)ft-=MAXN;
        d[ft]=iv;
    }
    inline int pop()
    {
        ++bk;if(bk==MAXN){bk-=MAXN;return d[MAXN-1];}
        else return d[bk-1];
    }
    inline bool empty(){return ft+1==bk;}
}myq;bool inque[MAXN];
int n,nm;
long long tot;
inline void addedge(int pf,int pt,int pw,int pc)
{
    //cout<<"Adding:"<<pf<<","<<pt<<","<<pw<<","<<pc<<endl;
    mye[++pmye].to=pt;
    mye[pmye].fr=pf;
    mye[pmye].w=pw;
    mye[pmye].c=pc;
    mye[pmye].next=myv[pf].first;
    myv[pf].first=pmye;
    
    mye[++pmye].to=pf;
    mye[pmye].fr=pt;
    mye[pmye].w=0;
    mye[pmye].c=-pc;
    mye[pmye].next=myv[pt].first;
    myv[pt].first=pmye;
}
void spfa()
{
    int pf,pt;
    myq.clean();
    for each(i,n) myv[i].wp=OO;
    myv[1].wp=0;
    myq.push(1);
    inque[1]=true;
    while(!myq.empty())
    {
        pf=myq.pop();
        inque[pf]=false;
        for(int p=myv[pf].first;p;p=mye[p].next)
        {
            pt=mye[p].to;
            if(myv[pt].wp>myv[pf].wp+mye[p].c&&mye[p].w>0)
            {
                myv[pt].wp=myv[pf].wp+mye[p].c;
                myv[pt].pre=p;
                if(!inque[pt])
                {
                    myq.push(pt);
                    inque[pt]=true;
                }
            }
        }
    }  
}
void mincostflow()
{
    long long minw;
    while(true)
    {
        spfa();
        if(myv[n].wp==OO)return;
        minw=OO;
        for(int ie=myv[n].pre;;ie=myv[mye[ie].fr].pre)
        {
            //cout<<mye[ie].fr<<" ";
            minw=min(minw,mye[ie].w);
            if(mye[ie].fr==1)break;
        }
        //cout<<":"<<minw<<endl;
        tot+=(long long)myv[n].wp*minw;
        for(int ie=myv[n].pre;;ie=myv[mye[ie].fr].pre)
        {
            //cout<<mye[ie].fr<<endl;
            mye[ie].w-=minw;
            mye[ie^1].w+=minw;
            //tot+=minw*mye[ie].c;
            if(mye[ie].fr==1)break;
        }
    }
}
typedef int vnodep;
vnodep pwk1[251],pwk2[251],ptk[251];
int main()
{
    freopen("2245.in","r",stdin);
    freopen("2245.out","w",stdout);
    int nc;
    scanf("%d%d",&nc,&nm);
    for each(i,nc)
    {
        pwk1[i]=++pmyv;
        //cout<<"pwk1["<<i<<"]="<<pmyv<<endl;
        pwk2[i]=++pmyv;
        //cout<<"pwk2["<<i<<"]="<<pmyv<<endl;
    }
    for each(i,nm)
    {
        ptk[i]=++pmyv;
        //cout<<"ptk["<<i<<"]="<<pmyv<<endl;
    }
    n=++pmyv;
    int /*pf,pt,*/pw/*,pc*/;
    for each(i,nm)
    {
        scanf("%d",&pw);
        addedge(ptk[i],n,pw,0);
    }
    for each(i,nc)
    for each(j,nm)
    {
        scanf("%d",&pw);
        if(pw==1)addedge(pwk2[i],ptk[j],9999999,0);
    }
    int ia;
    int itij[100]={},iwij;
    for each(i,nc)
    {
        scanf("%d",&ia);
        
        for each(j,ia)
        {
            scanf("%d",&itij[j]);
        }
        itij[ia+1]=9999999;
        for each(j,ia+1)
        {
            scanf("%d",&iwij);
            addedge(pwk1[i],pwk2[i],itij[j]-itij[j-1],iwij);
        }
    }
    for each(i,nc)
    {
        addedge(1,pwk1[i],9999999,0);
    }
    mincostflow();
    printf("%lld",tot);
}
