#include <iostream>
#include <cstring>
#include <cstdlib>
//#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
#define iif(statement,truepart,falsepart) ((statement)?(truepart):(falsepart))
int gdata[6][6];
int tnx,tny;
int tlimit=3;
int resdata[6][6]=
{0,0,0,0,0,0,
 0,1,1,1,1,1,
 0,0,1,1,1,1,
 0,0,0,9,1,1,
 0,0,0,0,0,1,
 0,0,0,0,0,0};
inline int precheck()
{
    int res=0;
    for each(ix,5)
    for each(iy,5)
    {
        if(ix!=tnx||iy!=tny)
        if(gdata[ix][iy]!=resdata[ix][iy])++res;
    }
    return res;
}
inline bool check()
{
    {
        for each(iy,5)
        {
            if(gdata[1][iy]==0)return false;
        }
        for every(iy,2,5)
        {
            if(gdata[2][iy]==0)return false;
        }
        for every(iy,4,5)
        {
            if(gdata[3][iy]==0)return false;
        }
        if(gdata[4][5]==0)return false;
    }
    return true;
}
bool search(int idp)
{
    int tres=precheck();
    if(idp>tlimit)return false;
    if(tres+idp-1>tlimit)return false;
    if(tres==0)return true;
    //if(tnx==3&&tny==3)if(check()){ans=idp;return true;}
    int tx=-9999,ty=9999;
    for each(i,8)
    {
        switch(i)
        {
            case 1:tx=+2,ty=+1;break;
            case 2:tx=+2,ty=-1;break;
            case 3:tx=-2,ty=+1;break;
            case 4:tx=-2,ty=-1;break;
            case 5:ty=+2,tx=+1;break;
            case 6:ty=+2,tx=-1;break;
            case 7:ty=-2,tx=+1;break;
            case 8:ty=-2,tx=-1;break;
        }
        if(tnx+tx>5||tnx+tx<1||tny+ty>5||tny+ty<1)continue;
        gdata[tnx][tny]=gdata[tnx+tx][tny+ty];
        tnx+=tx,tny+=ty;
        if(search(idp+1))return true;
        tnx-=tx,tny-=ty;
        gdata[tnx+tx][tny+ty]=gdata[tnx][tny];
    }
    return false;
}
inline void task()
{
    char tc[7];
    for each(ix,5)
    {
        scanf("%s",&tc[1]);
        for each(iy,5)
        {
            
            gdata[ix][iy]=iif(tc[iy]=='1',1,0);
            if(tc[iy]=='*'){tnx=ix;tny=iy;}
        }
    }
    for(tlimit=1;tlimit<=15;++tlimit)
    if(search(0))
    {
        printf("%d\n",tlimit);
        return;
    }
    printf("-1\n");
}
int main()
{
    freopen("1085.in","r",stdin);
    freopen("1085.out","w",stdout);
    int n;
    scanf("%d",&n);
    for each(i,n)
    {
        task();
    }
}
