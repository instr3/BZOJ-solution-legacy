#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define mod 2147483648
int nx,ny;
int nt;
int nk;
struct snode
{
    int x,y;
    bool operator <(snode ano) const
    {
        return y==ano.y?x<ano.x:y<ano.y;
    }
}indata[100001];
bool cmpx(snode is1,snode is2)
{
    return is1.x<is2.x;
}
bool cmpy(snode is1,snode is2)
{
    return is1.y<is2.y;
}
struct megtree
{
    int n;
    int d[100001];
    int s[100001];
    #define lowbit(iv) (iv)&-(iv)
    inline void add(int iv,int iw)
    {
        s[iv]+=iw;
        while(iv<=n)
        {
            d[iv]=((long long)d[iv]+iw)%mod;
            iv+=lowbit(iv);
        }
    }
    inline void set(int iv,int iw)
    {
        add(iv,((long long)iw-s[iv])%mod);
    }
    inline int sum(int iv)
    {
        int res=0;
        while(iv)
        {
            res=((long long)res+d[iv])%mod;
            iv-=lowbit(iv);
        }
        return res;
    }
    inline void clean()
    {
        memset(d,0,sizeof d);
        memset(s,0,sizeof s);
    }
}mytx;
int inx[100001];
int tlx[100001];
int iny[100001];
int tuy[100001];
int res;
/*inline int fc(int in)
{
    int res=1;
    for every(i,in-nk+1,in)res*=i;
    for each(i,nk)res/=i;
    return res;
}*/
#define fc(in) tfc[(in)+1][nk+1]
int tfc[100002][12];
int thx[100001],thy[100001];
inline void getc(int in)
{
    tfc[1][1]=1;
    for every(i,2,in+1)
    {
        for each(k,11)
        {
            
            tfc[i][k]=((long long)tfc[i-1][k-1]+tfc[i-1][k])%mod;
            //cout<<"F"<<i<<","<<k<<":"<<tfc[i][k]<<endl;
        }
    }
}
int main()
{
    freopen("1227.in","r",stdin);
    freopen("1227.out","w",stdout);
    scanf("%d%d",&nx,&ny);++nx,++ny;
    scanf("%d",&nt);
    for each(i,nt)
    {
        scanf("%d%d",&indata[i].x,&indata[i].y);
        //indata[i].x++;indata[i].y++;
    }
    sort(indata+1,indata+nt+1,cmpx);
    int tlast=-1223;
    int tcount;
    tcount=0;

    for each(i,nt)
    {
        if(indata[i].x!=tlast)
        {
            tlast=indata[i].x;
            indata[i].x=++tcount;
        }
        else indata[i].x=tcount;
    }
    nx=tcount;
    sort(indata+1,indata+nt+1,cmpy);
    tlast=-1223;
    tcount=0;
    for each(i,nt)
    {
        if(indata[i].y!=tlast)
        {
            tlast=indata[i].y;
            indata[i].y=++tcount;
        }
        else indata[i].y=tcount;
    }
    ny=tcount;
    for each(i,nt)
    {
        
        inx[indata[i].x]++;
        iny[indata[i].y]++;
    }
    
    mytx.n=nx;
    getc(nt);
    scanf("%d",&nk);
    sort(indata+1,indata+nt+1);
    /*for each(i,nt)
    {
        cout<<indata[i].x<<","<<indata[i].y<<endl;
    }*/
    int tx,ty;
    int tlastx=nx,tlasty=0;
    for each(i,nt)
    {
        tx=indata[i].x;
        ty=indata[i].y;
        tlx[tx]++;
        mytx.set(tx,(fc(tlx[tx])*(long long)fc(inx[tx]-tlx[tx]))%mod);
        if(ty==tlasty)
        {
            //cout<<fc(tuy[ty])*fc(iny[ty]-tuy[ty])<<","<<tx-1<<":"<<tlastx<<":"<<mytx.sum(nx)<<endl;
            res=((long long)res+((fc(tuy[ty])*(long long)fc(iny[ty]-tuy[ty]))%mod*(mytx.sum(tx-1)-mytx.sum(tlastx)))%mod)%mod;
        }
        tuy[ty]++;
        tlastx=tx;
        tlasty=ty;
    }
    printf("%d",(int)(((long long)res+mod)%mod));
}
