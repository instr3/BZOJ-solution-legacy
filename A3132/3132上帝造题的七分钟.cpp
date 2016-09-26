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
struct bit2tree
{
    int d[2049][2049];
    #define lowbit(iv) ((iv)&-(iv))
    inline void change(int ivx,int ivy,int iw)
    {
        if(ivx*ivy==0)return;
        for(int ix=ivx;ix<=nx;ix+=lowbit(ix))
        {
            for(int iy=ivy;iy<=ny;iy+=lowbit(iy))
            {
                //cout<<"CH"<<ix<<","<<iy<<endl;
                d[ix][iy]+=iw;
            }
        }
    }
    inline int ask(int ivx,int ivy)
    {
        int sum=0;
        for(int ix=ivx;ix;ix-=lowbit(ix))
        {
            for(int iy=ivy;iy;iy-=lowbit(iy))
            {
                sum+=d[ix][iy];
            }
        }
        return sum;
    }
}mytxy,mytx,myty,myt;
int n,nop;
inline void changedd(int ix,int iy,int iw)
{
    if(ix>nx||iy>ny)return;
    myt.change(ix,iy,iw);
    mytx.change(ix,iy,iw*ix);
    myty.change(ix,iy,iw*iy);
    mytxy.change(ix,iy,iw*ix*iy);
}
inline int ask(int ix,int iy)
{
    //cout<<ix<<","<<iy<<":"<<(nx+1)*(ny+1)*myt.ask(ix,iy)-(nx+1)*myty.ask(ix,iy)-(ny+1)*mytx.ask(ix,iy)+mytxy.ask(ix,iy)<<endl;
    return (ix+1)*(iy+1)*myt.ask(ix,iy)-(ix+1)*myty.ask(ix,iy)-(iy+1)*mytx.ask(ix,iy)+mytxy.ask(ix,iy);
}
int main()
{
    freopen("3132.in","r",stdin);
    freopen("3132.out","w",stdout);
    char tc[2];
    int ix1,ix2,iy1,iy2,pw;
    while(scanf("%s",&tc[0])!=EOF)
    {
        //cout<<tc[0]<<endl;
        switch(tc[0])
        {
            case 'L':
                scanf("%d%d%d%d%d",&ix1,&iy1,&ix2,&iy2,&pw);
                //myt.change(ix2,iy2,pw);
                //myt.change(ix2,iy1-1,-pw);
                //myt.change(ix1-1,iy2,-pw);
                //myt.change(ix1-1,iy1-1,pw);
                changedd(ix2+1,iy2+1,pw);
                changedd(ix2+1,iy1,-pw);
                changedd(ix1,iy2+1,-pw);
                changedd(ix1,iy1,pw);
                /*for each(ix,nx)
                {
                    for each(iy,ny)
                    {
                        cout<<ask(ix,iy)<<" ";
                    }
                    cout<<endl;
                }*/
                break;
            case 'k':
                scanf("%d%d%d%d",&ix1,&iy1,&ix2,&iy2);
                printf("%d\n",ask(ix2,iy2)-
                 ask(ix2,iy1-1)-
                  ask(ix1-1,iy2)+
                   ask(ix1-1,iy1-1));
                break;
            case 'X':
                scanf("%d%d",&nx,&ny);
                break;
            default:;
        }
    }
}
