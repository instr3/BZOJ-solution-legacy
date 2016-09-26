#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
const double six=1/6.0;
int n;
struct ck2dpoint
{
    int x,y;
};
struct ck2dvector
{
    double x,y;
};
struct ckconvex
{
    int ne;
    ck2dpoint p[51];
    ck2dvector asklen(double ix)
    {
        double minres=9e99,maxres=-9e99;
        double tins;
        for each(i,ne)
        {
            if((p[i].x<=ix and p[i+1].x>=ix)or(p[i].x>=ix and p[i+1].x<=ix))
            {
                if(p[i].y==p[i+1].y)
                {
                    tins=p[i].y;
                }
                else
                {
                    tins=(p[i+1].y-p[i].y)/(double)(p[i+1].x-p[i].x)*(ix-p[i].x)+p[i].y;
                }
                minres=min(minres,tins);
                maxres=max(maxres,tins);
            }
        }
        return (ck2dvector){minres,maxres};
    }
}ind[11];
double tf(double ix)
{
    double minres=-9e99,maxres=9e99;
    ck2dvector tget;
    for each(i,n)
    {
        tget=ind[i].asklen(ix);
        if(tget.x>=tget.y)
        {
            //cout<<"Getting:"<<ix<<":"<<0<<endl;
            return 0.0;
        }
        minres=max(minres,tget.x);
        maxres=min(maxres,tget.y);
    }
    //cout<<"Getting:"<<ix<<":"<<max(maxres-minres,0.0)<<endl;
    return max(maxres-minres,0.0);
}
inline double calc(double il,double ir)
{
    double im=(il+ir)*0.5;
    return (tf(il)+tf(ir)+4*tf(im))*six*(ir-il);
}
double simpson(double il,double ir,double ires)
{
    double im=(il+ir)*0.5;
    double tget1=calc(il,im);
    double tget2=calc(im,ir);
    if(abs(ires-(tget1+tget2))>=1e-5||(ir-il>1&&tget1+tget2<1e-5))
    {
        return simpson(il,im,tget1)+simpson(im,ir,tget2);
    }
    return tget1+tget2;
}
int main()
{
    freopen("2618.in","r",stdin);
    freopen("2618.out","w",stdout);
    scanf("%d",&n);
    int minx=9999,maxx=-9999;
    for each(i,n)
    {
        scanf("%d",&ind[i].ne);
        for each(j,ind[i].ne)
        {
            scanf("%d%d",&ind[i].p[j].x,&ind[i].p[j].y);
            minx=min(minx,ind[i].p[j].x);
            maxx=max(maxx,ind[i].p[j].x);
        }
        ind[i].p[ind[i].ne+1]=ind[i].p[1];
    }
    printf("%.3f",(double)simpson(minx,maxx,-9));
    
}
