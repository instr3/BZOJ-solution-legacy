#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
struct enode{int to,next;}mye[1001];
struct vnode{int first;}myv[101];
int n;
bool treach[101][101];
bool tvisit[101];
void dfs(int iv,int ipar)
{
    //cout<<ipar<<" Can Get to "<<iv<<endl;
    if(ipar!=iv)
    treach[ipar][iv]=true;
    tvisit[iv]=true;
    int pt;
    for(int p=myv[iv].first;p;p=mye[p].next)
    {
        pt=mye[p].to;
        if(!tvisit[pt])
        {
            dfs(pt,ipar);
        }
    }
}
int txty[101];
int tytx[101];
bool findpath(int ix)
{
    for each(iy,n)
    {
        if(treach[ix][iy]&&!tvisit[iy])
        {
            tvisit[iy]=true;
            if(!tytx[iy])
            {
                tytx[iy]=ix;
                txty[ix]=iy;
                return true;
            }
            else if(findpath(tytx[iy]))
            {
                tytx[iy]=ix;
                txty[ix]=iy;
                return true;
            }
        }
    }
    return false;
}
int main()
{

    int nm;
    scanf("%d%d",&n,&nm);
    int pf,pt;
    for(int i=1;i<=nm;++i)
    {
        scanf("%d%d",&pf,&pt);
        mye[i].to=pt;
        mye[i].next=myv[pf].first;
        myv[pf].first=i;
    }
    for each(i,n)
    {
        memset(tvisit,0,sizeof(tvisit));
        dfs(i,i);
    }
    int tot=0;
    for each(i,n)
    {
        memset(tvisit,0,sizeof(tvisit));
        if(findpath(i))++tot;
    }
    cout<<n-tot; 
}
