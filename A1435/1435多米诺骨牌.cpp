#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
//#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
int nx,ny;
int indata[16][16];
int tdata[16][16][16][16];
int ttdp[17][32768];
#define getbit(i,k) ((i)&(1<<(k-1)))
#define setbit(i,k) (i)^=(1<<(k-1))
#define mod 19901013
#define a(x,y) (x)=((x)+(y))%mod
#define s(x,y) (x)=((x)-(y)%mod+mod)%mod
#define m(x,y) (x)=((long long)(x)*(y))%mod
inline int dp(int ix1,int iy1,int ix2,int iy2)
{
    
    if(tdata[ix1][iy1][ix2][iy2]!=-1)return tdata[ix1][iy1][ix2][iy2];
    int tnx=ix2-ix1+1;
    int tny=iy2-iy1+1;
    int tnz=(1<<tny)-1;
    
    //if(tnx<=3&&tny<=3)return tdata[ix1][iy1][ix2][iy2]=0;
    memset(ttdp,0,sizeof ttdp);
    ttdp[0][0]=1;
    int tz;
    int res;
    for every(ix,1,tnx)
    {
        for every(iy,1,tny)
        {
            for every(iz,0,tnz)
            {
                tz=iz;
                if(!ttdp[iy-1][iz])continue;
                if(indata[ix+ix1-1][iy+iy1-1])
                {
                    if(ix>1)if(indata[ix+ix1-2][iy+iy1-1])
                    if(!getbit(iz,iy))
                    {
                        setbit(tz,iy);
                        a(ttdp[iy][tz],ttdp[iy-1][iz]);
                    }
                    tz=iz;
                    if(getbit(tz,iy))setbit(tz,iy);
                    if(iy>1)if(indata[ix+ix1-1][iy+iy1-2])
                    if(!getbit(iz,iy-1))
                    {
                        setbit(tz,iy-1);
                        setbit(tz,iy);
                        a(ttdp[iy][tz],ttdp[iy-1][iz]);
                    }
                }
                tz=iz;
                if(getbit(tz,iy))setbit(tz,iy);
                a(ttdp[iy][tz],ttdp[iy-1][iz]);
            }
        }
        res=0;
        for every(iz,0,tnz)
        {
            ttdp[0][iz]=ttdp[tny][iz];
            a(res,ttdp[tny][iz]);
            for each(iy,tny)ttdp[iy][iz]=0;
            
        }
        tdata[ix1][iy1][ix1+ix-1][iy2]=res;
    }
    //res=0;
    //for every(iz,0,tnz)a(res,ttdp[tny][iz]);
    //return res;
    return tdata[ix1][iy1][ix2][iy2];
}
inline int fct(int iz)
{
    int res;
    for(res=0;iz;++res)iz&=(iz-1);
    return res;
}
int tt[16][16];
int tf[16];
inline int dfs(int iz)
{
    int tlast=0;
    int tct=0;
    int res=1;
    memset(tt,0,sizeof tt);
    memset(tf,0,sizeof tf);
    for each(ix1,nx)
    {
        for every(ix2,ix1,nx)
        {
            tt[ix1][ix2]=1;
            tlast=1;
            for each(i,ny)
            {
                if(getbit(iz,i))
                {
                    if(tdata[1][tlast][nx][i]!=-1)
                    m(tt[ix1][ix2],tdata[ix1][tlast][ix2][i]);
                    tlast=i+1;
                }
            }
            m(tt[ix1][ix2],tdata[ix1][tlast][ix2][ny]);
        }
    }
    for each(i,nx)
    {
        tf[i]=tt[1][i];
        for each(j,i-1)
        {
            s(tf[i],((long long)tf[j]*tt[j+1][i])%mod);
        }
    }
            
    for each(i,ny)
    {
        if(getbit(iz,i))
        {
            tct++;
        }
    }
    res=tf[nx];
    //cout<<res<<endl;
    if(tdata[1][tlast][nx][ny]!=-1)
    return ((tct%2)?-res:res);
}
int main()
{
    //²Î¿¼Ìâ½â:http://www.cnblogs.com/zcwwzdjn/archive/2012/05/27/2520572.html 
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    scanf("%d%d",&nx,&ny);
    int nz=(1<<ny);
    char tc[102];
    for each(ix,nx)
    {
        scanf("%s",&tc[1]);
        for each(iy,ny)
        {
            indata[ix][iy]=(tc[iy]=='.'?1:0);
        }
    }
    memset(tdata,-1,sizeof tdata);
    
    for every(isx,1,nx)
    for every(isy,1,ny)
    for(int ix=nx;ix>=isx;ix--)
    for(int iy=ny;iy>=isy;iy--)
    dp(isx,isy,ix,iy);
    int tot=0;
    int nz2=nz/2;
    for every(iz,0,nz2-1)
    a(tot,dfs(iz));
    cout<<(tot+mod)%mod<<endl;
}
