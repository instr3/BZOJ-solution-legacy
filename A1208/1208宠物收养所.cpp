#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define min(a,b) ((a)<(b)?(a):(b))
#define abs(a) ((a)<0?-(a):(a))
int n;
int tdata[20001];
#define save(i) (tsave[(i)+1001000])

int res;
int tct=0;
bool tlock;
int tmul=1;
void printarr()
{
    for each(i,tct)cout<<tdata[i]<<" ";cout<<endl;
}
int main()
{
    freopen("1208.in","r",stdin);
    freopen("1208.out","w",stdout);
    scanf("%d",&n);
    int tm,tl,tr;
    int top,tw;
    int nowop=0;
    int tot=0;

    for each(i,n)
    {
        scanf("%d%d",&top,&tw);
        if(!tlock)
        {
            if(tct!=0)
            {
                tlock=true;
                tmul=tw>tdata[1]?1:-1;
                if(tmul==-1)
                {
                    tdata[1]=-tdata[1];
                    tw=-tw;
                }
            }
        }else if(tmul==-1)tw=-tw;
        if(tct==0)
        {
            nowop=top;
            tdata[++tct]=tw;
            //cout<<"New "<<tw<<"!"<<endl;
            continue;
        }
        if(top==nowop)
        {
            tl=2,tr=tct+2;
            if(tw<tdata[1])tl=1;
            else
            while(tl+1!=tr)
            {
                tm=(tl+tr)>>1;
                if(tw>tdata[tm-1])
                {
                    tl=tm;
                }
                else
                {
                    tr=tm;
                }
            }
            ++tct;
            for(int j=tct;j>tl;--j)
            {
                tdata[j]=tdata[j-1];
            }
            tdata[tl]=tw;
            
            //cout<<"Added "<<tl<<":"<<tw<<"!"<<endl;
            //printarr();
        }
        else
        {
            tl=1,tr=tct+1;
            while(tl+1!=tr)
            {
                tm=(tl+tr)>>1;
                if(tdata[tm]<=tw)
                {
                    tl=tm;
                }
                else
                {
                    tr=tm;
                }
            }
            if(tl<tct&&abs(tdata[tl]-tw)>abs(tdata[tl+1]-tw))++tl;
            tct--;
            tot=(tot+abs(tdata[tl]-tw))%1000000;
            //cout<<"Removed "<<tl<<":"<<tdata[tl]<<"!"<<endl;
            for(int j=tl;j<=tct;++j)
            {
                tdata[j]=tdata[j+1];
            }
            //printarr();
        }
    }
    printf("%d",tot);
}
