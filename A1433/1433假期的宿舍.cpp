#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
//#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
int zmap[1001][1001];
int zx[1001],zy[1001];
bool visit[1001];
int nx,ny;
bool zpath(int ix)
{
    for each(iy,ny)
    {
        if(zmap[ix][iy])
        {
            if(visit[iy])continue;
            visit[iy]=true;
            if(!zy[iy])
            {
                zx[ix]=iy;zy[iy]=ix;return true;
            }
            else if(zpath(zy[iy]))
            {
                zx[ix]=iy;zy[iy]=ix;return true;
            }
        }
    }
    return false;
}
int pkid[1001];
int pbed[1001];
bool ishere[1001];
bool ishome[1001];
void task()
{
    memset(zx,0,sizeof zx);
    memset(zy,0,sizeof zy);
    memset(zmap,0,sizeof zmap);
    nx=ny=0;
    memset(pbed,0,sizeof pbed);
    memset(pkid,0,sizeof pkid);
    int n;scanf("%d",&n);
    for each(i,n)
    {
        scanf("%d",&ishere[i]);
        if(ishere[i])pbed[i]=++ny;
    }
    for each(i,n)
    {
        scanf("%d",&ishome[i]);
        if(ishere[i])
        {
            if(!ishome[i])pkid[i]=++nx;
        }
        else pkid[i]=++nx;
    }
    int tij;
    for each(i,n)
    {
        for each(j,n)
        {
            scanf("%d",&tij);
            if(tij)
            {
                if(pkid[i]&&pbed[j]){zmap[pkid[i]][pbed[j]]=1;/*cout<<i<<" can sleep in "<<j<<endl;*/}
                if(pkid[j]&&pbed[i]){zmap[pkid[j]][pbed[i]]=1;/*cout<<j<<" can sleep in "<<i<<endl;*/}
            }
            if(i==j)zmap[pkid[i]][pbed[i]]=1;
        }
    }
    int tot=0;

    for each(ix,nx)
    {
        memset(visit,0,sizeof(visit));
        if(zpath(ix))++tot;
    }
    if(tot<nx)
    {
        cout<<"T_T"<<endl;
    }
    else 
    {
        cout<<"^_^"<<endl;
    }
}
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    int n;scanf("%d",&n);
    for each(i,n)
    task();
    
}
