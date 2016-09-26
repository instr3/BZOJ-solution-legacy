#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
int nx,ny;
int nc;
int pts[10]; 
char map[12][12];
int tmk[12][12][10];
bool ismk[12][12];
int tdp[12][12][2][2][2][2][2][2][2][2][2];
bool texist[12][12][2][2][2][2][2][2][2][2][2];
bool tout[12][12][2][2][2][2][2][2][2][2][2];
int tdec;
#define such(p) (p).ix][(p).iy][(p).iget[1]][(p).iget[2]][(p).iget[3]][(p).iget[4]][(p).iget[5]][(p).iget[6]][(p).iget[7]][(p).iget[8]][(p).iget[9]
#define pos(p) (p).ix][(p).iy
struct tnode
{
    int ix,iy;
    bool iget[10];
    bool operator ==(tnode ano) const 
    {
        if(ix!=ano.ix)return false;
        if(iy!=ano.iy)return false;
        for each(i,nc)if(iget[i]!=ano.iget[i])return false;
        return true;
    }
}tnow;
/*struct queue
{
    tnode d[1000001];
    int fr,bk;
    queue(){fr=1;}
    inline bool empty(){return fr==bk+1;};
    inline void push(tnode &it){if(bk==1000000)bk=0;d[++bk]=it;};
    inline tnode pop(){if(fr==1000000)fr=0;return d[fr++];};
}myq;*/
queue<tnode>myq;
/*
    dp(x,y,beans)=max(dp(x',y',beans')-1+points)
*/
int tres=0;
void print(tnode it)
{
    cout<<it.ix<<","<<it.iy<<"/";
    for each(i,9)cout<<it.iget[i];
    cout<<":"<<tdp[such(it)]<<endl;
} 
inline void relax(tnode &it,int ifrom)
{
    if(it==tnow)return;
    int tsave=tdp[such(it)];
    tdp[such(it)]=-987654321;
    /*for each(k,9)
    {
        if(it.iget[k])goto brk;
    }
    tdp[such(it)]=0;
    brk:;*/
    tnode ipt[5];
    for each(i,4)ipt[i]=it;
    ipt[1].ix--;ipt[2].ix++;
    ipt[3].iy--;ipt[4].iy++;
    int tget[5]={};
    if(ismk[pos(ipt[4])])
    for each(k,9)
    {
        if(tmk[pos(ipt[4])][k])
        {
            ipt[4].iget[k]=!ipt[4].iget[k];
            if(it.iget[k])tget[4]+=pts[k];
            else tget[4]-=pts[k];
        }
    }
    if(ismk[pos(it)])
    for each(k,9)
    {
        if(tmk[pos(it)][k])
        {
            ipt[3].iget[k]=!ipt[3].iget[k];
            if(it.iget[k])tget[3]+=pts[k];
            else tget[3]-=pts[k];
        }
    }
    for every(i,ifrom,ifrom)
    {
        if(!(ipt[i].ix&&ipt[i].iy&&ipt[i].ix-nx-1&&ipt[i].iy-ny-1))continue;
        if(map[pos(ipt[i])]!='0')continue;
        if(tout[such(ipt[i])]){tdp[such(ipt[i])]-=tdec;tout[such(ipt[i])]=false;}
        tdp[such(it)]=max(tdp[such(it)],tget[i]+tdp[such(ipt[i])]-1);
    }
    if(tdp[such(it)]>tsave)return;
    for each(i,4)
    {
        if(i==ifrom)continue;
        if(!(ipt[i].ix&&ipt[i].iy&&ipt[i].ix-nx-1&&ipt[i].iy-ny-1))continue;
        if(map[pos(ipt[i])]!='0')continue;
        if(tout[such(ipt[i])]){tdp[such(ipt[i])]-=tdec;tout[such(ipt[i])]=false;}
        tdp[such(it)]=max(tdp[such(it)],tget[i]+tdp[such(ipt[i])]-1);
    }
}
inline void getdp()
{
    tnode it;
    tnode ipt[5];
    int trem;
    while(!myq.empty())
    {
        it=myq.front();
        //it=myq.pop();
        myq.pop();
        //print(it);
        texist[such(it)]=false;
        for each(i,4)ipt[i]=it;
        ipt[1].ix--;ipt[2].ix++;
        ipt[3].iy--;ipt[4].iy++;
        if(ismk[pos(ipt[4])])
        for each(k,nc)
        {
            if(tmk[pos(ipt[4])][k])
            {
                ipt[4].iget[k]=!ipt[4].iget[k];
            }
        }
        if(ismk[pos(it)])
        for each(k,nc)
        {
            if(tmk[pos(it)][k])
            {
                ipt[3].iget[k]=!ipt[3].iget[k];
            }
        }
        for each(i,4)
        {
            if(!(ipt[i].ix&&ipt[i].iy&&ipt[i].ix-nx-1&&ipt[i].iy-ny-1))continue;
            if(map[pos(ipt[i])]!='0')continue;
            if(tout[such(ipt[i])]){tdp[such(ipt[i])]-=tdec;tout[such(ipt[i])]=false;}
            trem=tdp[such(ipt[i])];
            relax(ipt[i],((i-1)^1)+1);
            if(tdp[such(ipt[i])]>trem)
            {
                if(ipt[i].ix==tnow.ix&&ipt[i].iy==tnow.iy)tres=max(tres,tdp[such(ipt[i])]);
                if(!texist[such(ipt[i])])
                {
                    myq.push(ipt[i]);
                    texist[such(ipt[i])]=true;
                }
            }
        }
    }
}

int main()
{
    freopen("1294.in","r",stdin);
    freopen("1294.out","w",stdout);
    memset(tdp,-38,sizeof tdp);
    scanf("%d%d",&nx,&ny);
    scanf("%d",&nc);for each(i,nc)scanf("%d",&pts[i]);
    char tc[1000];
    tnode it={};
    for each(i,nx)
    {
        scanf("%s",&tc[1]);
        for each(j,ny)
        {
            map[i][j]=tc[j];
            if(tc[j]>'0'&&tc[j]<='9')
            {
                for each(ix,i-1)
                {
                    tmk[ix][j][tc[j]-'0']=true;
                    ismk[ix][j]=true;
                }
            }
        }
    }
    int tot=0;
    for each(i,nx)
    {
        for each(j,ny)
        {
            if(tc[j]=='0')
            {
                if(tc[j-1]=='0'&&ismk[i][j])tdec=1;else tdec=99999;
                memset(tout,1,sizeof tout);
                //memset(tdp,-38,sizeof tdp);
                it.ix=i;
                it.iy=j;
                myq.push(it);
                tdp[such(it)]=0;
                texist[such(it)]=true;
                tout[such(it)]=false;
                tnow=it;
                getdp();
                tot=max(tot,tres);
            }
        }
    }
    cout<<tot;
    //getdp();
}
