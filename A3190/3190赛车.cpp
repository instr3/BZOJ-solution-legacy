#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
struct inode
{
    int k,b,n;
    bool operator <(inode ano)const
    {
        return k==ano.k?b<ano.b:k<ano.k;
    }
}indata[10001];
bool iswin[10001];
struct ck2dpoint
{
    double x,y;
    int n;
}tstk[10001];int pstk;
inline ck2dpoint intersection(inode ia,inode ib)
{
    double tx=(ib.b-ia.b)/(double)(ia.k-ib.k);
    return (ck2dpoint){tx,ia.k*tx+ia.b,-1};
}
int n;
int main()
{
    scanf("%d",&n);
    for each(i,n)
    {
        scanf("%d",&indata[i].b);
        indata[i].n=i;
    }
    for each(i,n)
    {
        scanf("%d",&indata[i].k);
    }
    sort(indata+1,indata+n+1);
    //tstk[++pstk]=(ck2dpoint){0,indata[1].b,1};
    ck2dpoint tpoint;
    for each(i,n)
    {
        //-cout<<"Checking:"<<indata[i].n<<endl;
        if(pstk)
        if(indata[i].k==indata[tstk[pstk].n].k)
        {
            if(indata[i].b==indata[tstk[pstk].n].b)
            {
                tpoint=tstk[pstk];
                tpoint.n=i;
                tstk[++pstk]=tpoint;
                continue;
            }
            --pstk;
        }
        while(pstk)
        {
            tpoint=intersection(indata[tstk[pstk].n],indata[i]);
            if(!(tpoint.x<tstk[pstk].x-1e-8))break;
            //cout<<"Pop:"<<indata[tstk[pstk].n].n<<endl;
            --pstk;
        }
        tpoint.n=i;
        if(pstk)
        {
            tstk[++pstk]=tpoint;
        }
        else
        {
            tstk[++pstk]=(ck2dpoint){0,indata[i].b,i};
        }
    }
    for each(i,pstk)
    {
        iswin[indata[tstk[i].n].n]=true;
         
    }
    printf("%d\n",pstk);
    int lastans=0;
    for each(i,n)
    {
        if(iswin[i])lastans=i;
    }
    for each(i,n)
    {
        if(iswin[i])
        {
            if(i!=lastans)
            {
                printf("%d ",i);
            }
            else
            {
                printf("%d",i);
            }
        }
    }
}
