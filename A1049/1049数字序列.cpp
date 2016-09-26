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
int n;
int insdata[35001];
int indata[35001];
struct inode
{
    int n,w;
    bool operator <(inode ano)const{return w<ano.w;}
}myi[35001];
struct stack
{
    int s[351];
    int n;
}mys[35001];
stack minat[35001];
struct rtree
{
    int s[35001];
    int w[35001];
    #define lowbit(i) ((i)&-(i))
    void set(int iv,int iw,int inum)
    {
        s[iv]=iw;
        while(iv<=n)
        {
            if(w[iv]<=iw)
            {
                if(w[iv]<iw)
                {
                    w[iv]=iw;
                    minat[iv].n=1;
                    minat[iv].s[1]=inum;
                }
                else minat[iv].s[++minat[iv].n]=inum;
            }
            iv=iv+lowbit(iv);
        }
    }
    int ask(int iv,int inum)
    {
        int res=0;
        while(iv)
        {
            //res=max(res,w[iv]);
            if(w[iv]>=res)
            {
                if(w[iv]>res)
                {
                    res=w[iv];
                    mys[inum].n=0;
                    for each(i,minat[iv].n)
                    mys[inum].s[++mys[inum].n]=minat[iv].s[i];
                }
                else
                {
                    for each(i,minat[iv].n)
                    mys[inum].s[++mys[inum].n]=minat[iv].s[i];
                }
            }
            iv-=lowbit(iv);
        }
        return res;
    } 
}myt;
int tdp[35001];
int trdp[35001];
#define myabs(ix) ((ix)<0?-(ix):(ix))
int getrdp(int iv)
{
    if(iv==0)return 0;
    if(trdp[iv]!=-1)return trdp[iv];
    int res=1999999999;
    int tmin;
    int tres;
    int tl,tr;
    if(mys[iv].n==0){mys[iv].n=1;mys[iv].s[1]=0;}
    for each(i,mys[iv].n)
    {
        tl=mys[iv].s[i]+1;tr=iv-1;
        tres=0;
        tmin=1999999999;
        for every(j,tl,tr)
        {
            tres+=myabs(insdata[iv]-insdata[j]);
            //cout<<j<<":"<<tres<<endl;
        }
        tmin=min(tmin,tres);
        if(tl==1)goto die;
        for every(j,tl,tr)
        {
            tres=tres-myabs(insdata[iv]-insdata[j])+
             myabs(insdata[mys[iv].s[i]]-insdata[j]);
            tmin=min(tmin,tres);
        }
        die:;
        tmin+=getrdp(mys[iv].s[i]);
        res=min(res,tmin);
    }
    //cout<<"GEt"<<iv<<":"<<res<<endl;
    return trdp[iv]=res;
}
int main()
{
    freopen("1049.in","r",stdin);
    freopen("1049.out","w",stdout);
    memset(trdp,-1,sizeof trdp);
    scanf("%d",&n);
    //insdata[0]=-99999;
    for each(i,n)
    {
        scanf("%d",&insdata[i]);
        insdata[i]-=i;
        
        myi[i]=(inode){i,insdata[i]};
    }
    sort(myi+1,myi+n+1);
    int tlast=-1999999999;int ti=0;
    for each(i,n)
    {
        if(myi[i].w==tlast)
        {
            indata[myi[i].n]=ti;
        }
        else
        {
            indata[myi[i].n]=++ti;
            tlast=myi[i].w;
        }
    }
    //for each(i,n)printf("%d ",insdata[i]);
    int tot=1999999999;
    int tres;
    int minout=-1999999999;
    for each(i,n)
    {
        tdp[i]=myt.ask(indata[i],i)+1;
        minout=max(minout,tdp[i]);
        myt.set(indata[i],tdp[i],i);
        /*cout<<tdp[i]<<":";
        for each(j,mys[i].n)
        {
            cout<<mys[i].s[j]<<" ";
        }
        cout<<endl;*/
    }
    
    cout<<n-minout<<endl;
    for each(j,n)
    {
        if(tdp[j]!=minout)continue;
        tres=getrdp(j);
        for every(k,j+1,n)
        {
            tres=tres+myabs(insdata[k]-insdata[j]);
        }
        tot=min(tot,tres);
    }
    cout<<tot<<endl;
}
