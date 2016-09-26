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
#define float double
#define cos cos
#define acos acos
#define sqr(x) ((x)*(x))
struct ccircle
{
    float x,y,r;
}indata[1001];
struct cangseg
{
    float l,r;
    bool operator <(cangseg ano)const
    {
        return l<ano.l;
    }

}tang[1001];int pang;
#define getdist(x1,y1,x2,y2) sqrt(sqr((x2)-(x1))+sqr((y2)-(y1)))
#define getcdist(i,j) getdist((indata[i].x),(indata[i].y),(indata[j].x),(indata[j].y))
#define getcos(a,b,c) ((sqr(a)+sqr(b)-sqr(c))/(2*(a)*(b)))
//#define getk(i,j) ((indata[j].y-indata[i].y)/(indata[j].x-indata[i].x))
int main()
{
    freopen("1043.in","r",stdin);
    freopen("1043.out","w",stdout);
    int n;scanf("%d",&n);
    for each(i,n)cin>>indata[i].r>>indata[i].x>>indata[i].y;
    float tdist,tnang,tvang;
    float tlast,tl,tres;
    float tot=0;
    for each(i,n)
    {
        pang=0;
        for every(j,i+1,n)
        {
            tdist=getcdist(i,j);
            if(indata[j].r+indata[i].r-1e-9<=tdist)continue;
            if(tdist-1e-9<=indata[j].r-indata[i].r)goto die;
            if(tdist-1e-9<=indata[i].r-indata[j].r)continue;
            //tnang=atan(getk(i,j));
            tnang=acos((indata[j].x-indata[i].x)/tdist);
            if(indata[j].y<=indata[i].y)tnang=-tnang;
            tvang=acos(getcos(indata[i].r,tdist,indata[j].r));
            //cout<<"Yes:"<<i<<j<<","<<tdist<<","<<tvang<<endl;
            if(tnang-tvang<0)tnang+=2*M_PI;
            tang[++pang].l=tnang-tvang;
            tang[pang].r=tnang+tvang;
            if(tang[pang].r>=2*M_PI)
            {
                
                ++pang;
                tang[pang].r=tang[pang-1].r-2*M_PI;
                tang[pang].l=0;
                tang[pang-1].r=2*M_PI;
            }
            //cout<<tang[pang].l<<" "<<tang[pang].r<<endl;
            
        }
        sort(tang+1,tang+pang+1);
        tlast=-99999999;
        tres=0;
        //cout<<i<<":"<<endl;
        for each(j,pang)
        {
            tl=max(tlast,tang[j].l);
            
            if(tl>=tang[j].r)continue;
            tlast=tang[j].r;
            tres+=tang[j].r-tl;
            //cout<<tang[j].l<<"-"<<tang[j].r<<endl;
        }
        //cout<<tres<<endl;
        tot+=(2*M_PI-tres)*indata[i].r;
        die:;
    }
    printf("%.3f",(double)tot);
}
