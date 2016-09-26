#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int map[101][11];
int tdp[2][12][59050][3];
#define getbit(iz,i) (iz&(1<<(i-1)))
#define setbit(iz,i) (iz^=(1<<(i-1)))

#define get2bit(iz,i) ((iz&(3<<((i<<1)-2)))>>(((i<<1)-2)))
#define set2bit(iz,i,k) (iz^=(1<<((i<<1)-2+k)))
int nx,ny;
int gtz;
#define compress(tza,iz) \
iz=0;\
for each(itc,ny)\
{\
    iz<<=2;\
    iz=iz+(tza)[itc];\
}
#define uncompress(tza,iz) \
gtz=iz;\
for each(itc,ny)\
{\
    (tza)[itc]=gtz&3;\
    gtz>>=2;\
}
#define inc(a,b) ((a)=((a)+(b))%20110520)
int tarr[100000];int parr;
int tanti[1048576];
inline void dp()
{
    int nz=1<<(ny*2);
    int tza[11];
    int tnza[11];
    int tnz;
    for every(iz,0,nz-1)
    {
        uncompress(tza,iz);
        for each(i,ny)
        {
            if(tza[i]==3)goto die2;
            tnza[i]=tza[i];
        }
        tarr[++parr]=iz;
        tanti[iz]=parr;
        die2:;
    }
    tdp[1][1][1][0]=1;
    int iz;
    int ix2;
    for each(ix,nx)
    {
        ix2=ix%2;
        memset(tdp[ix2^1],0,sizeof tdp[ix2^1]);
        for each(iy,ny)
        {
            for each(ipz,parr)
            {
                iz=tarr[ipz];
                uncompress(tza,iz);
                if(tdp[ix2][iy][ipz][0]==0&&tdp[ix2][iy][ipz][1]==0&&tdp[ix2][iy][ipz][2]==0)goto die;
                tnz=iz;
                //if(tdp[ix2][iy][ipz][0])cout<<ix<<","<<iy<<","<<ipz<<","<<0<<":"<<tdp[ix2][iy][ipz][0]<<endl;
                //if(tdp[ix2][iy][ipz][1])cout<<ix<<","<<iy<<","<<ipz<<","<<1<<":"<<tdp[ix2][iy][ipz][1]<<endl;
                //if(tdp[ix2][iy][ipz][2])cout<<ix<<","<<iy<<","<<ipz<<","<<2<<":"<<tdp[ix2][iy][ipz][2]<<endl;
                
                if(map[ix][iy])
                {
                    if(tza[iy]==0)
                    {
                        inc(tdp[ix2][iy+1][ipz][0],tdp[ix2][iy][ipz][0]);
                    }
                    goto die;
                }
                if(tza[iy]==0)
                {
                    tnz=iz;
                    set2bit(tnz,iy,0);
                    inc(tdp[ix2][iy+1][tanti[tnz]][0],tdp[ix2][iy][ipz][0]);
                    tnz=iz;
                    set2bit(tnz,iy,1);
                    inc(tdp[ix2][iy+1][tanti[tnz]][2],tdp[ix2][iy][ipz][0]);
                    inc(tdp[ix2][iy+1][tanti[tnz]][0],tdp[ix2][iy][ipz][1]);
                    tnz=iz;
                    inc(tdp[ix2][iy+1][tanti[tnz]][1],tdp[ix2][iy][ipz][0]);
                    inc(tdp[ix2][iy+1][tanti[tnz]][1],tdp[ix2][iy][ipz][1]);
                    inc(tdp[ix2][iy+1][tanti[tnz]][2],tdp[ix2][iy][ipz][2]);
                    inc(tdp[ix2][iy+1][tanti[tnz]][0],tdp[ix2][iy][ipz][2]);
                }
                else if(tza[iy]==1)
                {
                    
                    tnz=iz;
                    inc(tdp[ix2][iy+1][tanti[tnz]][0],tdp[ix2][iy][ipz][0]);
                    tnz=iz;
                    set2bit(tnz,iy,0);
                    inc(tdp[ix2][iy+1][tanti[tnz]][2],tdp[ix2][iy][ipz][0]);
                    inc(tdp[ix2][iy+1][tanti[tnz]][0],tdp[ix2][iy][ipz][1]);
                }
                else
                {
                    tnz=iz;
                    inc(tdp[ix2][iy+1][tanti[tnz]][0],tdp[ix2][iy][ipz][0]);
                    tnz=iz;
                    set2bit(tnz,iy,1);
                    inc(tdp[ix2][iy+1][tanti[tnz]][0],tdp[ix2][iy][ipz][0]);
                }
                die:;
            }
        }
        if(ix==nx)break;
        for each(ipz,parr)
        {
            inc(tdp[ix2^1][1][ipz][0],tdp[ix2][ny+1][ipz][0]);
        }
    }
}
int main()
{
    freopen("2331.in","r",stdin);
    freopen("2331.out","w",stdout);
    scanf("%d%d",&nx,&ny);
    //Make ny small
    char tc[102];
    if(nx<ny)
    {
        for each(i,nx)
        {
            scanf("%s",&tc[1]);
            for each(j,ny)
            {
                map[j][i]=tc[j]=='_'?0:1;
            }
        }
        swap(nx,ny);
    }
    else
    {
        for each(i,nx)
        {
            scanf("%s",&tc[1]);
            for each(j,ny)
            {
                map[i][j]=tc[j]=='_'?0:1;
            }
        }
    }
    dp();
    printf("%d",tdp[nx%2][ny+1][1][0]);
}
