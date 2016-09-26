#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
int nx,ny;
int indata[1002][2];
struct enode{int to,next;}myex[2005],myey[2005];int pmyex,pmyey;
struct vnode{int first,cn;}myvx[1002],myvy[1002];
inline void addedge(int ix,int iy)
{
    //cout<<ix<<":"<<iy<<endl;
    myex[++pmyex].to=iy;
    myex[pmyex].next=myvx[ix].first;
    myvx[ix].first=pmyex;
    
    myey[++pmyey].to=ix;
    myey[pmyey].next=myvy[iy].first;
    myvy[iy].first=pmyey;
}
bool visity[1002];
bool zpath(int ix)
{
    int iy;
    for(int p=myvx[ix].first;p;p=myex[p].next)
    {
        iy=myex[p].to;
        //cout<<ix<<":"<<iy<<endl;
        if(visity[iy])continue;
        visity[iy]=true;
        
        if(!myvy[iy].cn)
        {
            //cout<<ix<<"->"<<iy<<endl;
            myvx[ix].cn=iy;
            myvy[iy].cn=ix;
            return true;
        }
        else if(zpath(myvy[iy].cn))
        {
            //cout<<ix<<"->"<<iy<<endl;
            myvx[ix].cn=iy;
            myvy[iy].cn=ix;
            return true;
        }
    }
    return false;
}
            
int main()
{
    scanf("%d%d",&ny,&nx);
    for each(i,nx)
    {
        scanf("%d%d",&indata[i][0],&indata[i][1]);
        addedge(i,indata[i][0]+1);
        addedge(i,indata[i][1]+1);
    }
    int tot=0;
    for each(i,nx)
    {
        memset(visity,0,sizeof(visity));
        if(zpath(i))++tot;
        else break;
    }
    cout<<tot<<endl;
    system("pause");
}
        
