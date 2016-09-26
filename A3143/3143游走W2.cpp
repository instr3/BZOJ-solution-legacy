#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define double long double
struct enode{int to,next;}mye[50002];
struct vnode{int first;}myv[501];
int n,nm,nm2;

double seq[501][501];
inline void solver(int in)
{
    double tr1,tr2;
    for(int k=in;k>=1;--k)
    {
        for each(i,k-1)
        {
            tr2=seq[i][k];
            tr1=seq[i+1][k];
            if(tr1==0)continue;
            for every(j,0,k)
            {
                seq[i][j]*=tr1;
                seq[i+1][j]*=tr2;
                seq[i][j]-=seq[i+1][j];
            }
        }
    }
}

            
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    scanf("%d%d",&n,&nm);
    int pf,pt;
    for(int i=1,j=1;i<=nm;++i)
    {
        scanf("%d%d",&pf,&pt);
        mye[++j].to=pt;
        mye[j].next=myv[pf].first;
        myv[pf].first=j;
        mye[++j].to=pf;
        mye[j].next=myv[pt].first;
        myv[pt].first=j;
    }
    seq[1][0]=12;
    seq[1][1]=1;
    seq[1][2]=2;
    seq[2][0]=3;
    seq[2][1]=1;
    seq[2][2]=-1;
    seq[3][3]=1;
    seq[3][2]=-99;
    seq[3][0]=111;
    for each(i,3)
    {
        cout<<seq[i][0]<<":";
        for each(j,3)
        {
            cout<<seq[i][j]<<" ";
        }
        cout<<endl;
    }
    solver(3);
    for each(i,3)
    {
        cout<<seq[i][0]<<":";
        for each(j,3)
        {
            cout<<seq[i][j]<<" ";
        }
        cout<<endl;
    }
}
        
