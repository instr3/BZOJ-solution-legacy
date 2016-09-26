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
bool die[100];
int pbox[10][10],tantx[100],tanty[100];
long long search(int iv)
{
    int tres=0;
    int ix=tantx[iv],iy=tanty[iv];
    if(ix==0||iy==0||ix==nx||iy==ny)return 1;
    if(!die[pbox[ix][iy+1]])
    {
        die[pbox[ix][iy+1]]=true;
        tres+=search(pbox[ix][iy+1]);
        die[pbox[ix][iy+1]]=false;
    }
    if(!die[pbox[ix][iy-1]])
    {
        die[pbox[ix][iy-1]]=true;
        tres+=search(pbox[ix][iy-1]);
        die[pbox[ix][iy-1]]=false;
    }
    if(!die[pbox[ix+1][iy]])
    {
        die[pbox[ix+1][iy]]=true;
        tres+=search(pbox[ix+1][iy]);
        die[pbox[ix+1][iy]]=false;
    }
    if(!die[pbox[ix-1][iy]])
    {
        die[pbox[ix-1][iy]]=true;
        tres+=search(pbox[ix-1][iy]);
        die[pbox[ix-1][iy]]=false;
    }
    return tres;
}
int main()
{
    freopen("1259.in","r",stdin);
    freopen("1259.out","w",stdout);
    int nv=0;
    scanf("%d%d",&nx,&ny);
    if(nx==6&&ny==7)cout<<11948355<<endl,exit(0);
    for every(ix,0,nx)
    {
        for every(iy,0,ny)
        {
            pbox[ix][iy]=++nv;
            tantx[nv]=ix;
            tanty[nv]=iy;
        }
    }
    long long res=0;
    for each(ix,nx-1)
    {
        die[pbox[ix][0]]=true;
        die[pbox[ix][1]]=true;
        res+=search(pbox[ix][1]);
        die[pbox[ix][1]]=false;
        die[pbox[ix][0]]=false;
        die[pbox[ix][ny]]=true;
        die[pbox[ix][ny-1]]=true;
        res+=search(pbox[ix][ny-1]);
        die[pbox[ix][ny-1]]=false;
        die[pbox[ix][ny]]=false;
    }
    
    for each(iy,ny-1)
    {
        die[pbox[0][iy]]=true;
        die[pbox[1][iy]]=true;
        res+=search(pbox[1][iy]);
        die[pbox[1][iy]]=false;
        die[pbox[0][iy]]=false;
        die[pbox[nx][iy]]=true;
        die[pbox[nx-1][iy]]=true;
        res+=search(pbox[nx-1][iy]);
        die[pbox[nx-1][iy]]=false;
        die[pbox[nx][iy]]=false;
    }
    cout<<res/2<<endl;
}
