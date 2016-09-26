#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <queue>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
int nx,ny,nt;
int map[31][31];
int tdp[31][31];
bool visit[31][31];
struct tnode
{
    int x,y;
};
queue<tnode>myq;
int tgdp;
int tot;
void dfs(int ix,int iy)
{
    if(visit[ix][iy])return;
    visit[ix][iy]=true;
    //cout<<ix<<","<<iy<<":"<<tgdp<<endl;
    tdp[ix][iy]=tgdp;
    if(ix>1)if(!visit[ix-1][iy])
    {if(map[ix-1][iy]==0)dfs(ix-1,iy);
    else myq.push((tnode){ix-1,iy});}
    if(iy>1)if(!visit[ix][iy-1])
    {if(map[ix][iy-1]==0)dfs(ix,iy-1);
    else myq.push((tnode){ix,iy-1});}
    if(ix<nx)if(!visit[ix+1][iy])
    {if(map[ix+1][iy]==0)dfs(ix+1,iy);
    else myq.push((tnode){ix+1,iy});}
    if(iy<ny)if(!visit[ix][iy+1])
    {if(map[ix][iy+1]==0)dfs(ix,iy+1);
    else myq.push((tnode){ix,iy+1});}
}
void bfs(int ix,int iy)
{
    while(!myq.empty())myq.pop();
    myq.push((tnode){ix,iy});
    tnode tt;
    tgdp=map[ix][iy];
    memset(tdp,-1,sizeof tdp);
    memset(visit,0,sizeof visit);
    while(true)
    {
        if(tgdp>nt)break;
        if(myq.empty())break;
        myq.push((tnode){38,62});
        while(true)
        {
            tt=myq.front();
            myq.pop();
            if(tt.y==62)break;
            dfs(tt.x,tt.y);
        }
        tgdp++;
    }
    int maxdis=0;
    for each(i,nx)
    {
        for each(j,ny)
        {
            #define sqr(_) ((_)*(_))
            if(tdp[i][j]!=-1)maxdis=max(maxdis,sqr(ix-i)+sqr(iy-j));
        }
    }
    tot=max(tot,maxdis);
    //cout<<ix<<","<<iy<<":"<<maxdis<<endl;
}

int main()
{
    freopen("1295.in","r",stdin);
    freopen("1295.out","w",stdout);
    scanf("%d%d%d",&nx,&ny,&nt);
    for each(i,nx)
    {
        for each(j,ny)
        {
            scanf("%1d",&map[i][j]);
        }
    }
    
    for each(i,nx)
    {
        for each(j,ny)
        {
            bfs(i,j);
        }
    }//cout<<tot<<endl;
    printf("%.6f",(double)sqrt(tot));
}
