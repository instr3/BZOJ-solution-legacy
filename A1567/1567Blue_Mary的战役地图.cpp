#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n,map[2][51][51];
int thash1[2][51][51][51][51];
int thash2[2][51][51][51][51];
bool task(int ik)
{
    
    for each(ix1,n-ik+1)
    for each(iy1,n-ik+1)
    {
        for each(ix2,n-ik+1)
        for each(iy2,n-ik+1)
        {
            if(thash1[0][ix1][iy1][ix1+ik-1][iy1+ik-1]==
                thash1[1][ix2][iy2][ix2+ik-1][iy2+ik-1])
                 //thash2[0][ix1][iy1][ix1+ik-1][iy1+ik-1]==
                  //thash2[1][ix2][iy2][ix2+ik-1][iy2+ik-1]
            {
                //cout<<ik<<":"<<ix1<<","<<iy1<<","<<ix2<<","<<iy2<<endl;
                return true;
            }
        }
    }
    return false;
}
int main()
{
    freopen("1567.in","r",stdin);
    freopen("1567.out","w",stdout);
    scanf("%d",&n);
    for every(k,0,1)
    for each(i,n)
    {
        for each(j,n)
        {
            scanf("%d",&map[k][i][j]);
        }
    }
    for every(k,0,1)
    for each(ix1,n)
    for each(iy1,n)
    {
        for every(ix2,ix1,n)
        for every(iy2,iy1,n)
        {
            thash1[k][ix1][iy1][ix2][iy2]=map[k][ix2][iy2]+thash1[k][ix1][iy1][ix2-1][iy2]*29+
             thash1[k][ix1][iy1][ix2][iy2-1]*23-thash1[k][ix1][iy1][ix2-1][iy2-1]*23*29;
            //thash2[k][ix1][iy1][ix2][iy2]=map[k][ix2][iy2]+thash2[k][ix1][iy1][ix2-1][iy2]*37+
             //thash2[k][ix1][iy1][ix2][iy2-1]*19-thash2[k][ix1][iy1][ix2-1][iy2-1]*19*37;
            
        }
    }

    int tl=0,tr=n+1,tm=0;
    while(tl+1!=tr)
    {
        tm=(tl+tr)>>1;
        if(task(tm))
        {
            tl=tm;
        }
        else
        {
            tr=tm;
        }
    }
    cout<<tl;
}
