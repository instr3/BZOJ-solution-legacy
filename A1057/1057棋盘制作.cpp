#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int indata[2001][2001];
int tup[2001][2001];
int nx,ny;
int ans1,ans2;
struct tnode
{
    int y,h;
}mys[2001];int pmys;
inline void popele(int iy)
{
    //cout<<"Poping:"<<mys[pmys].y<<"By"<<iy<<endl;
    int tlen=iy-mys[pmys-1].y-1;
    int tsqr=min(tlen,mys[pmys].h);
    ans1=max(ans1,tsqr*tsqr);
    ans2=max(ans2,tlen*mys[pmys].h);
    //cout<<"Get:"<<tlen*mys[pmys].h<<endl;
    --pmys;
}
inline void task()
{
    memset(tup,0,sizeof tup);
    for each(iy,ny)
    {
        for each(ix,nx)
        {
            if(!indata[ix][iy])continue;
            tup[ix][iy]=tup[ix-1][iy]+1;
        }
    }
    for each(ix,nx)
    {
        mys[0].y=0;
        for each(iy,ny)
        {
            if(!indata[ix][iy])
            {
                while(pmys)popele(iy);
                mys[0].y=iy;
                continue;
            }
            while(pmys&&mys[pmys].h>tup[ix][iy])
            {
                popele(iy);
            }
            ++pmys;
            mys[pmys]=(tnode){iy,tup[ix][iy]};
            //cout<<"Adding:"<<iy<<","<<tup[ix][iy]<<endl;
        }
        while(pmys)popele(ny+1);
    }
}
int main()
{
    freopen("1057.in","r",stdin);
    freopen("1057.out","w",stdout);
    scanf("%d%d",&nx,&ny);
    for each(i,nx)
    {
        for each(j,ny)
        {
            scanf("%d",&indata[i][j]);
            if((i+j)%2)indata[i][j]=1-indata[i][j];
            //cout<<indata[i][j]<<" ";
        }
        //cout<<endl;
    }
    task();
    for each(i,nx)
    {
        for each(j,ny)
        {
            indata[i][j]=1-indata[i][j];
        }
    }
    task();
    printf("%d\n%d",ans1,ans2);
    
}
