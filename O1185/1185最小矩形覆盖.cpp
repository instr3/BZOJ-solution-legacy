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
struct ck2dpoint
{
    double x,y;
}indata[50001],minpos;
bool operator<(ck2dpoint ia,ck2dpoint ano)
{
    return (ia.y-minpos.y)*(ano.x-minpos.x)<(ano.y-minpos.y)*(ia.x-minpos.x);
}
int n;
int tstk[100001],pstk,ans[5];
double operator *(ck2dpoint ia,ck2dpoint ib)
{
    return ia.x*ib.y-ib.x*ia.y;
}
double operator &(ck2dpoint ia,ck2dpoint ib)
{
    return ia.x*ib.x+ia.y*ib.y;
}
double abs(ck2dpoint ia){return sqrtl(ia.x*ia.x+ia.y*ia.y);}
double getcos(ck2dpoint ia,ck2dpoint ib)
{
    return (ia&ib)/abs(ia)/abs(ib);
}

ck2dpoint operator +(ck2dpoint ia,ck2dpoint ib)
{
    return (ck2dpoint){ia.x+ib.x,ia.y+ib.y};
}
ck2dpoint operator -(ck2dpoint ia,ck2dpoint ib)
{
    return (ck2dpoint){ia.x-ib.x,ia.y-ib.y};
}
int tspos[5];
ck2dpoint tvec;
inline ck2dpoint gettrans(int in)
{
    if(in==1)return tvec;
    if(in==2)return (ck2dpoint){-tvec.y,tvec.x};
    if(in==3)return (ck2dpoint){-tvec.x,-tvec.y};
    if(in==4)return (ck2dpoint){tvec.y,-tvec.x};
}
inline double getarea(ck2dpoint ia,ck2dpoint ib,ck2dpoint ic)
{
    return (ia*ib+ib*ic+ic*ia)/2;
}
int minatx,minaty,maxatx,maxaty;
inline double getdist(ck2dpoint iv,ck2dpoint ia)
{
    return abs(iv.y*ia.x-iv.x*ia.y)/abs(iv);
}
int main()
{
    freopen("1185.in","r",stdin);
    freopen("1185.out","w",stdout);
    scanf("%d",&n);
    double minx=9e99,miny=9e99,maxx=-9e99,maxy=-9e99;
    
    for each(i,n)
    {
        cin>>indata[i].x>>indata[i].y;
        if(indata[i].x<minx)
        {
            minx=indata[i].x;
            minatx=i;
        }
        if(indata[i].y<miny)
        {
            miny=indata[i].y;
            minaty=i;
        }
        if(indata[i].x>maxx)
        {
            maxx=indata[i].x;
            maxatx=i;
        }
        if(indata[i].y>maxy)
        {
            maxy=indata[i].y;
            maxaty=i;
        }
    }
    /*for each(i,n)
    {
        indata[i].x+=-minx+1.0L;
        indata[i].y+=-miny+1.0L;
    }*/
    minpos=indata[minatx];
    sort(indata+1,indata+n+1);
    for each(i,n)
    {
        //cout<<indata[i].x<<","<<indata[i].y<<endl;
        while(true)
        {
            if(pstk<=1)break;
            if((indata[tstk[pstk]]-indata[tstk[pstk-1]])*
             (indata[i]-indata[tstk[pstk-1]])<=0)
            {
                pstk--;
            }else break;
        }
        if(pstk)
        if(abs(indata[tstk[pstk]]-indata[i])<=1e-4)continue;
        tstk[++pstk]=i;
    }
    
    for each(i,pstk)
    {
        if(indata[tstk[i]].y==miny)tspos[1]=i;
        if(indata[tstk[i]].x==maxx)tspos[2]=i;
        if(indata[tstk[i]].y==maxy)tspos[3]=i;
        if(indata[tstk[i]].x==minx)tspos[4]=i;
        tstk[pstk+i]=tstk[i];
    }
    for each(i,pstk)
    {
        cout<<indata[tstk[i]].x<<","<<indata[tstk[i]].y<<endl;
    }
    double mincos,tcos;int mcat;
    bool tlev=false;
    tvec=(ck2dpoint){1,0};
    double tot=99999999,tget;
    do
    {
        mincos=-999999;
        for each(i,4)
        {
            tcos=getcos(gettrans(i),indata[tstk[tspos[i]+1]]-indata[tstk[tspos[i]]]);
            //cout<<tcos<<":"<<gettrans(i).x<<","<<(indata[tstk[tspos[i]+1]]-indata[tstk[tspos[i]]]).x<<endl;
            if(tcos>mincos)
            {
                mincos=tcos;
                mcat=i;
            }
        }
        tvec=indata[tstk[tspos[mcat]+1]]-indata[tstk[tspos[mcat]]];
        for(int i=mcat;i!=5;++i)
        {
            swap(tvec.x,tvec.y);
            tvec.x=-tvec.x;
        }
        #define qmax(a,b,c,d) max(max(max(a,b),c),d)
        tspos[mcat]++;
        cout<<"TVEC:"<<tvec.x<<","<<tvec.y<<";"
        <<indata[tstk[tspos[1]]].x<<","<<indata[tstk[tspos[1]]].y<<";"
        <<indata[tstk[tspos[2]]].x<<","<<indata[tstk[tspos[2]]].y<<";"
        <<indata[tstk[tspos[3]]].x<<","<<indata[tstk[tspos[3]]].y<<";"
        <<indata[tstk[tspos[4]]].x<<","<<indata[tstk[tspos[4]]].y<<endl;
        
        
        tget=max(min(getdist(gettrans(1),indata[tstk[tspos[3]]]-indata[tstk[tspos[1]]]),
        getdist(gettrans(2),indata[tstk[tspos[4]]]-indata[tstk[tspos[2]]])),
        min(getdist(gettrans(3),indata[tstk[tspos[1]]]-indata[tstk[tspos[3]]]),
        getdist(gettrans(4),indata[tstk[tspos[2]]]-indata[tstk[tspos[4]]]))
        );
        if(tget<tot)
        {
            tot=tget;
        }
        //cout<<tot<<endl;
        if(abs(indata[tstk[tspos[1]]].y-miny)>1e-3)tlev=true;
        //if(abs(tlev&&indata[tstk[tspos[1]]].y-miny)<=1e-3)break;
    }while(true);
    pstk*=2;
    
    printf("%.5f",(float)(tot*tot));
}
