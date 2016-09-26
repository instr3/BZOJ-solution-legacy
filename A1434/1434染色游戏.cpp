#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int nx,ny;
inline int get2(int inum)
{
    int tres=0;
    while(inum)
    {
        if(inum%2)break;
        inum/=2;++tres;
    }
    return tres;
}
inline int getsg(int ix,int iy)
{
    if(ix>iy)swap(ix,iy);
    if(ix==1)
    {
        return get2(iy);
    }
    else
    {
        return ix+iy-2;
    }
}

int tres[203];
void task()
{
    memset(tres,0,sizeof tres);
    scanf("%d%d",&nx,&ny);
    char tc[102];
    for each(ix,nx)
    {
        scanf("%s",&tc[1]);
        for each(iy,ny)
        {
            if(tc[iy]=='T')
            tres[getsg(ix,iy)]^=1;
        }
    }
    for every(i,0,nx+ny+2)
    {
        if(tres[i])
        {
            printf("-_-\n");return;
        }
    }
    printf("=_=\n");
}
int main()
{
    freopen("1434.in","r",stdin);
    freopen("1434.out","w",stdout);
    int nt;scanf("%d",&nt);
    for each(i,nt)task();
}
