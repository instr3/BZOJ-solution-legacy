#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define double long double
#define sqrt sqrtl
int nb;
struct crect
{
    int x1,y1,x2,y2;
}indata[2001];
struct cfense
{
    int x,y1,y2;
}tfen[2001];
struct zdpoint
{
    int x,y;
    int operator * (zdpoint ano)
    {
        return x*ano.y-y*ano.x;
    }
    zdpoint operator -(zdpoint ano)
    {
        return (zdpoint){x-ano.x,y-ano.y};
    }
    /*void print()
    {
        cout<<"("<<x<<","<<y<<")";
    }*/
}tups[4013],tdns[4013],ibeg,iend;int np,nt;
double abs(zdpoint ia)
{
    return sqrt((double)(ia.x*ia.x+ia.y*ia.y));
}
double tdp[8013];
inline void addedge(int ist,int ito,double idist)
{
    tdp[ito]=min(tdp[ito],tdp[ist]+idist);
    //cout<<ist<<","<<ito<<"-"<<tdp[ito]<<"("<<idist<<endl;
}
inline void flink(int ifr,zdpoint ist)
{
    zdpoint tpt;
    zdpoint tup={0,1},tdn={0,-1};
    for every(j,1,np)
    {
        if(tups[j].x<ist.x)continue;
        if((tups[j]-ist)*tdn>0)return;
        if((tdns[j]-ist)*tup<0)return;
        tpt=tups[j]-ist;
        if(tpt*tup<0)goto dnext;
        //cout<<ifr<<","<<j<<"--"<<tups[j].y<<endl;
        addedge(ifr,j,abs(tups[j]-ist));
        tup=tpt;
        dnext:;
        tpt=tdns[j]-ist;
        if(tpt*tdn>0)continue;
        addedge(ifr,j+2*nb,abs(tdns[j]-ist));
        tdn=tpt;
        //tup.print();tdn.print();cout<<endl;
    }
    if((iend-ist)*tdn>0||(iend-ist)*tup<0)return;
    addedge(ifr,nt,abs(iend-ist));
}
int main()
{
    freopen("2433.in","r",stdin);
    freopen("2433.out","w",stdout);
    scanf("%d",&nb);
    nt=4*nb+1;
    for each(i,nt)tdp[i]=9e99;
    for each(i,nb)
    {
        scanf("%d%d%d%d",&indata[i].x1,&indata[i].y1,&indata[i].x2,&indata[i].y2);
        ++np;
        tups[np]=(zdpoint){indata[i].x1,indata[i].y2};
        tdns[np]=(zdpoint){indata[i].x1,indata[i].y1};
        ++np;
        tups[np]=(zdpoint){indata[i].x2,indata[i].y2};
        tdns[np]=(zdpoint){indata[i].x2,indata[i].y1};
        if(i==1)continue;
        tfen[i-1]=(cfense){indata[i].x1,max(indata[i].y1,indata[i-1].y1),min(indata[i].y2,indata[i-1].y2)};
        
    }
    scanf("%d%d",&ibeg.x,&ibeg.y);
    scanf("%d%d",&iend.x,&iend.y);
    if(ibeg.x>iend.x)
    {
        swap(ibeg,iend);
    }
    flink(0,ibeg);
    for each(i,nb*2)
    {
        flink(i,tups[i]);
        //tdns[i].print();
        flink(i+nb*2,tdns[i]);
    }
    /*for each(i,nt)
    {
        cout<<tdp[i]<<endl;
    }*/
    double ivelocity;cin>>ivelocity;
    #undef double
    printf("%.10f",(double)(tdp[nt]/ivelocity));
}
