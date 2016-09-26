#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
//#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
int n;
struct CK2DPoint
{
    int x,y;
}indata[20001];
int minx=1000000001,maxx=-1000000001,miny=1000000001,maxy=-1000000001;
inline bool check(int in,int ix1,int iy1,int ix2,int iy2)
{
    int tminx=1000000001,tmaxx=-1000000001;
    int tminy=1000000001,tmaxy=-1000000001;
    for each(i,n)
    {
        if(indata[i].x>=ix1&&indata[i].x<=ix1+in&&
         indata[i].y>=iy1&&indata[i].y<=iy1+in)continue;
        if(indata[i].x>=ix2&&indata[i].x<=ix2+in&&
         indata[i].y>=iy2&&indata[i].y<=iy2+in)continue;
        tminx=min(tminx,indata[i].x);
        tmaxx=max(tmaxx,indata[i].x);
        tminy=min(tminy,indata[i].y);
        tmaxy=max(tmaxy,indata[i].y);
    }
    //cout<<"Test:"<<tmaxx<<","<<tminx<<","<<tmaxy<<","<<tminy<<endl;
    return (tmaxx-tminx)<=in&&(tmaxy-tminy)<=in;
}
int trmaxx,trmaxy,trminx,trminy;
inline void getres(int in,int ix1,int iy1)
{
    trminx=1000000001,trmaxx=-1000000001;
    trminy=1000000001,trmaxy=-1000000001;
    for each(i,n)
    {
        if(indata[i].x>=ix1&&indata[i].x<=ix1+in&&
         indata[i].y>=iy1&&indata[i].y<=iy1+in)continue;
        trminx=min(trminx,indata[i].x);
        trmaxx=max(trmaxx,indata[i].x);
        trminy=min(trminy,indata[i].y);
        trmaxy=max(trmaxy,indata[i].y);
    }
    trmaxy-=in;
    trmaxx-=in;
}
bool task(int in)
{
    int tx1,ty1;
    tx1=minx,ty1=miny;
    getres(in,tx1,ty1);
    if(check(in,tx1,ty1,trminx,trminy))return true;
    if(check(in,tx1,ty1,trmaxx,trminy))return true;
    if(check(in,tx1,ty1,trminx,trmaxy))return true;
    if(check(in,tx1,ty1,trmaxx,trmaxy))return true;
    tx1=maxx-in,ty1=miny;
    getres(in,tx1,ty1);
    if(check(in,tx1,ty1,trminx,trminy))return true;
    if(check(in,tx1,ty1,trmaxx,trminy))return true;
    if(check(in,tx1,ty1,trminx,trmaxy))return true;
    if(check(in,tx1,ty1,trmaxx,trmaxy))return true;
    tx1=minx,ty1=maxy-in;
    getres(in,tx1,ty1);
    if(check(in,tx1,ty1,trminx,trminy))return true;
    if(check(in,tx1,ty1,trmaxx,trminy))return true;
    if(check(in,tx1,ty1,trminx,trmaxy))return true;
    if(check(in,tx1,ty1,trmaxx,trmaxy))return true;
    tx1=maxx-in,ty1=maxy-in;
    getres(in,tx1,ty1);
    if(check(in,tx1,ty1,trminx,trminy))return true;
    if(check(in,tx1,ty1,trmaxx,trminy))return true;
    if(check(in,tx1,ty1,trminx,trmaxy))return true;
    if(check(in,tx1,ty1,trmaxx,trmaxy))return true;
    //cout<<minx<<","<<miny<<","<<maxx<<","<<maxy<<endl;
    /*
    if(check(in,minx,miny,maxx-in,maxy-in))return true;
    if(check(in,minx,maxy-in,maxx-in,miny))return true;
    for each(i,n)
    {
        ty1=indata[i].y;
        if(check(in,minx,ty1,maxx-in,miny))return true;
        if(check(in,minx,ty1,maxx-in,maxy-in))return true;
    }
    for each(i,n)
    {
        ty2=indata[i].y;
        if(check(in,minx,miny,maxx-in,ty2))return true;
        if(check(in,minx,maxy-in,maxx-in,ty2))return true;
    }
    */
    return false;
}
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    scanf("%d",&n);
    for each(i,n)
    {
        scanf("%d%d",&indata[i].x,&indata[i].y);
        minx=min(minx,indata[i].x);
        maxx=max(maxx,indata[i].x);
        miny=min(miny,indata[i].y);
        maxy=max(maxy,indata[i].y);
    }
    int tl=-1,tr=max(maxx-minx,maxy-miny)+1,tm;
    while(tl+1!=tr)
    {
        //tl维护第一个不可行解 
        tm=(tl+tr)>>1;
        if(task(tm))
        {
            tr=tm;
        }
        else
        {
            tl=tm;
        }
    }
    
    cout<<tl+1;
}
