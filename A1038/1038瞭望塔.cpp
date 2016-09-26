#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
//#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
struct zdpoint
{
    long double x,y;
}indata[301],tdata[301];int ptdata;
inline long double getk(zdpoint ip1,zdpoint ip2)
{
    return (ip2.y-ip1.y)/(ip2.x-ip1.x);
}
inline long double getb(zdpoint ip1,long double ik)
{
    return (ip1.y-ip1.x*ik);
}
int n;
long double tk1,tb1,tk2,tb2;
inline long double getbyx(long double ix)
{
    if(ix>indata[n].x)return 9e999L;
    if(ix<indata[1].x)return 9e999L;
    long double tkn;
    int ti=-99999999;
    for each(i,n)
    {
        if(indata[i].x>=ix)
        {
            ti=i-1;
            break;
        }
    }

    if(ti==0)++ti;

    long double tk,tb,tyh=0;
    tk=getk(indata[ti],indata[ti+1]);
    tb=getb(indata[ti],tk);
    for each(j,n-1)
    {
        tkn=getk(indata[j],indata[j+1]);
        tyh=max(tyh,tkn*ix+getb(indata[j],tkn));
    }
    //tyh=max(tk1*ix+tb1,tk2*ix+tb2);
    //cout<<ix<<":"<<fixed<<tyh-(tk*ix+tb)<<endl;
    return tyh-(tk*ix+tb);
}
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    scanf("%d",&n);
    for each(i,n)cin>>indata[i].x; 
    for each(i,n)cin>>indata[i].y;
    tdata[1]=indata[1];
    ptdata=1;
    for every(i,2,n)
    {
        while(ptdata>=2&&getk(tdata[ptdata-1],tdata[ptdata])<getk(tdata[ptdata-1],indata[i]))
        {
            --ptdata;
        }
        tdata[++ptdata]=indata[i];
    }
    long double tgmin=9e99L;
    long double tx;
    for every(i,2,n+ptdata)
    {
        if(i<=n)
        {
            tk1=getk(indata[i+1],indata[i]);
            tb1=getb(indata[i],tk1);
        }
        else
        {
            tk1=getk(tdata[i-n+1],tdata[i-n]);
            tb1=getb(tdata[i-n],tk1);
        }
        for every(j,2,n+ptdata)
        {
            if(i==j)continue;
            if(j<=n)
            {
                tk2=getk(indata[j+1],indata[j]);
                tb2=getb(indata[j],tk2);
            }
            else
            {
                tk2=getk(tdata[j-n+1],tdata[j-n]);
                tb2=getb(tdata[j-n],tk2);
            }
            if(tk2==tk1)continue;
            tx=(tb1-tb2)/(tk2-tk1);
            tgmin=min(tgmin,getbyx(tx));
        }
    }
    for each(i,n)
    {
        tgmin=min(tgmin,getbyx(indata[i].x));
    }
    /*
    tk1=getk(tdata[1],tdata[2]);
    tb1=getb(tdata[1],tk1);
    tk2=getk(tdata[ptdata],tdata[ptdata-1]);
    tb2=getb(tdata[ptdata],tk2);
    *//*
    long double tlastk=9e99L,tk,tx,ty;
    long double tmin;
    long double tl,tr,tm,tgmin=9e99L;
    for each(i,ptdata)
    {
        tmin=0;
        tx=tdata[i].x;
        ty=tdata[i].y;
        
        for each(j,n-1)
        {
            tk=getk(indata[j],indata[j+1]);
            tmin=max(tmin,tk*tx+getb(indata[j],tk)-ty);
        }
        //cout<<"Pt["<<i<<"]:"<<tdata[i].x<<","<<tdata[i].y<<":"<<tmin<<endl;
        //tgmin=min(tgmin,tmin);
    }
    
    for each(i,n-1)
    {
        tl=indata[i].x;
        tr=indata[i+1].x;
        while(tr-tl>1e-9L)
        {
            tm=(tl+tr)/2;
            if(getbyx(tm)<getbyx(tl))tl=tm;else tr=tm;
        }
        tgmin=min(tgmin,getbyx(tl));
    }*/
    printf("%.3f",(double)tgmin);
}

