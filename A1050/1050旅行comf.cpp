#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
int n,nm;
struct enode{int to,fr,next,w;}mye[10002];
struct vnode{int first;}myv[501];
//long double dist[501];
//bool visit[501];
//int tmin[501],tmax[501];
int par[501];
long double res=199999999;int trmin,trmax;
struct tnode
{
    int w;
    int n;
    bool operator <(tnode ano)const{return w<ano.w;};
}tew[10002];
int ifr,ito;
int getleader(int iv)
{
    if(par[iv])
    return par[iv]=getleader(par[iv]);
    return iv;
}
inline int gcd(int in1,int in2)
{
    int tr=100;
    int tk;
    while(tr)
    {
        tr=in1%in2;
        tk=in1/in2;
        in1=in2;in2=tr;
    }
    return in1;
}
inline void setcon(int iv1,int iv2)
{
    if(getleader(iv1)!=getleader(iv2))
    par[getleader(iv1)]=getleader(iv2);
}
int main()
{
    freopen("1050.in","r",stdin);
    freopen("1050.out","w",stdout);
    scanf("%d%d",&n,&nm);
    int pf,pt,pw;
    for(int i=1,j=1;i<=nm;++i)
    {
        scanf("%d%d%d",&pf,&pt,&pw);
        mye[++j].to=pt;
        mye[j].fr=pf;
        mye[j].w=pw;
        mye[j].next=myv[pf].first;
        myv[pf].first=j;
        tew[j-1]=(tnode){pw,j};
        mye[++j].to=pf;
        mye[j].fr=pt;
        mye[j].w=pw;
        mye[j].next=myv[pt].first;
        myv[pt].first=j;
        tew[j-1]=(tnode){pw,j};
    }
    scanf("%d%d",&ifr,&ito);
    sort(tew+1,tew+nm*2+1);
    int tlast=-1;
    long double tres;
    for each(i,nm*2)
    {
        if(tew[i].w==tlast)continue;
        pw=tew[i].w;
        memset(par,0,sizeof par);
        //cout<<pw<<"::"<<endl;
        for every(j,i,nm*2)
        {
            pf=mye[tew[j].n].fr;
            pt=mye[tew[j].n].to;
            //cout<<"Testing:"<<j<<":"<<pf<<","<<pt<<endl;
            setcon(pf,pt);
            if(getleader(ifr)==getleader(ito))
            {
                tres=(long double)tew[j].w/pw;
                //cout<<pw<<","<<tew[j].w<<tres<<endl;
                if(res>tres)
                {
                    res=tres;
                    trmax=tew[j].w;
                    trmin=pw;
                }
                break;
            }
        }
        tlast=tew[i].w;
    }
    if(trmax==0)
    {
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
    }
    int tg=gcd(trmin,trmax);
    if(trmin/tg==1)
    {
        cout<<trmax/tg<<endl;
        return 0;
    }
    cout<<trmax/tg<<"/"<<trmin/tg<<endl;
    
    
}
    /*
    for each(i,n)dist[i]=9e99l;
    memset(tmin,37,sizeof tmin);
    dist[ifr]=0;
    long double mindist;
    for each(k,n)
    {
        mindist=9e99;
        for each(i,n)
        {
            if(!visit[i]&&dist[i]<mindist)
            {
                mindist=dist[i];
                pf=i;
            }
        }
        visit[pf]=true;
        int tnmin,tnmax;
        for(int p=myv[pf].first;p;p=mye[p].next)
        {
            pt=mye[p].to;
            if(!visit[pt])
            {
                tnmin=min(tmin[pf],mye[p].w);
                tnmax=max(tmax[pf],mye[p].w);
                cout<<pt<<":"<<tnmin<<"/"<<tnmax<<endl;
                if((long double)tnmax/tnmin<dist[pt])
                {
                    dist[pt]=(long double)tnmax/tnmin;
                    tmin[pt]=tnmin;
                    tmax[pt]=tnmax;
                }
            }
        }
    }
    cout<<tmin[ito]<<"/"<<tmax[ito]<<endl;
        
}*/
