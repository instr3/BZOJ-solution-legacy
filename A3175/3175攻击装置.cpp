#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int nn,nx,ny;
int imap[201][201];
//int zmap[201][201];
int zx[20001],zy[20001];
struct enode{int to,next;}mye[160001];int pmye;
struct vnode{int first;}myv[20001];
int visit[20001];
int tdx[9]={0,2,2,1,-1,-2,-2,-1,1},
    tdy[9]={0,1,-1,-2,-2,-1,1,2,2};
#define inrange(x,y) ((x)>0&&(x)<=nn&&(y)>0&&(y)<=nn)
void addedge(int ix,int iy)
{
    //cout<<"Adding:"<<ix<<","<<iy<<endl;
    //zmap[ix][iy]=1;
    mye[++pmye].to=iy;
    mye[pmye].next=myv[ix].first;
    myv[ix].first=pmye;
}
bool zpath(int ix)
{
    //for each(iy,ny)
    int iy;
    for(int p=myv[ix].first;p;p=mye[p].next)
    {
        iy=mye[p].to;
        //if(!zmap[ix][iy])continue;
        if(visit[iy])continue;
        visit[iy]=true;
        if(!zy[iy])
        {
            zy[iy]=ix;zx[ix]=iy;
            return true;
        }
        else if(zpath(zy[iy]))
        {
            
            zy[iy]=ix;zx[ix]=iy;
            return true;
        }
    }
    return false;
}
int pmap[201][201];
int main()
{
    freopen("3175.in","r",stdin);
    freopen("3175.out","w",stdout);
    scanf("%d",&nn);
    for each(i,nn)
    {
        for each(j,nn)
        {
            scanf("%1d",&imap[i][j]);
            if(imap[i][j])continue;
            if((i+j)%2)
            {
                pmap[i][j]=++nx;
            }
            else
            {
                pmap[i][j]=++ny;
            }
            
        }
    }
    int tni,tnj;
    for each(i,nn)
    {
        for each(j,nn)
        {
            if(imap[i][j])continue;
            if((i+j)%2==0)continue;
            for each(idir,8)
            {
                tni=i+tdx[idir];
                tnj=j+tdy[idir];
                if(!inrange(tni,tnj))continue;
                if(imap[tni][tnj])continue;
                addedge(pmap[i][j],pmap[tni][tnj]);
            }
        }
    }
    int tot=0;
    for(int ix=nx;ix;--ix)
    {
        for each(iy,ny)visit[iy]=false;
        if(zpath(ix))++tot;
    }
    printf("%d",nx+ny-tot);
}
