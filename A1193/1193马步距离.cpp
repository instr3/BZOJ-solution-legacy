#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n;
int tdist[1002][1002];
int tinq[1002][1002];
#define dist(i,j) (tdist[(i)+500][(j)+500])
#define inq(i,j) (tinq[(i)+500][(j)+500])
#define limit 50
int nx,ny;
void spfa()
{
    memset(tdist,38,sizeof tdist);
    queue<pair<int,int> >myq;
    dist(0,0)=0;
    myq.push(make_pair(0,0));
    inq(0,0)=true;
    pair<int,int>tget;
    int tx,ty;
    #define testif(nx,ny)\
    do{\
        if(abs(tx+nx)<=limit&&abs(ty+ny)<=limit)\
        {\
            if(dist(tx+nx,ty+ny)>dist(tx,ty)+1)\
            {\
                dist(tx+nx,ty+ny)=dist(tx,ty)+1;\
                if(!inq(tx+nx,ty+ny))\
                {\
                    myq.push(make_pair(tx+nx,ty+ny));\
                    inq(tx+nx,ty+ny)=true;\
                }\
            }\
        }\
    }while(0);
        
    while(!myq.empty())
    {
        tget=myq.front();myq.pop();
        tx=tget.first;
        ty=tget.second;
        inq(tx,ty)=false;
        testif(2,1);
        testif(2,-1);
        testif(-2,1);
        testif(-2,-1);
        testif(1,2);
        testif(1,-2);
        testif(-1,2);
        testif(-1,-2);
    }
}
        
int main()
{
    freopen("1193.in","r",stdin);
    freopen("1193.out","w",stdout);
    spfa();
    /*for every(i,-14,14)
    {
        for every(j,-14,14)
        {
            (i+j)%2?(cout<<dist(i,j)<<" "):cout<<"  ";
        }
        cout<<endl;
    }*/
    int tv1,tv2,tv3,tv4;
    scanf("%d%d%d%d",&tv1,&tv2,&tv3,&tv4);
    nx=abs(tv1-tv3);
    ny=abs(tv4-tv2);
    int tot=0;
    if(ny>nx)swap(nx,ny);
    //cout<<dist(nx,ny)<<endl;
    while(nx>20||ny>20)
    {
        if(nx<ny*2)
        {
            nx-=3;ny-=3;tot+=2;
        }
        else
        {
            nx-=2;ny-=1;tot+=1;
            if(ny==-1)ny=1;
        }
    }
    cout<<tot+dist(nx,ny)<<endl;
    
    /*int tp;
    if(nx>14)
    {
        tp=(nx-14)/2;
        nx-=tp*2;
        ny-=tp;
        if(ny<0)ny=ny%2;
    }*/
    
}
