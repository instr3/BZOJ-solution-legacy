#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
unsigned char tsave[125000001];
#define setbit(iv) tsave[(iv)/8]|=1<<((iv)%8);
#define getbit(iv) (tsave[(iv)/8]&(1<<((iv)%8)))
//inline void setbit(int iv)
//{
//    tsave[iv/8]|=1<<(iv%8);
//}
//inline bool getbit(int iv)
//{
//    return tsave[iv/8]&(1<<(iv%8));
//}
int nt;
int n;
int indata[51];
int ans[51];
struct qnode
{
    int n,dat;
    bool operator <(qnode ano)const
    {
        return dat<ano.dat;
    }
}myq[51];
int maxn=0;
int main()
{
    freopen("2440.in","r",stdin);
    freopen("2440.out","w",stdout);
    scanf("%d",&nt);
    for each(i,nt)
    {
        scanf("%d",&indata[i]);
        maxn=max(maxn,indata[i]);
        myq[i].n=i;
        myq[i].dat=indata[i];
    }
    maxn*=2;
    sort(myq+1,myq+n+1);
    int sqrtn=(int)sqrt(maxn);
    int tv;
    memset(tsave,17,sizeof tsave);
    for every(i,3,sqrtn)
    {
        tv=i*i;
        for(int j=tv;j<=maxn;j+=tv)
        {
            if(!getbit(j))
            setbit(j);
        }
    }
    int tot=0;
    int pans=1;
    for each(i,maxn)
    {
        if(!getbit(i))
        {
            tot++;
            while(myq[pans].dat==tot)ans[myq[pans++].n]=i;
        }
    }
    for each(i,nt)
    {
        printf("%d\n",ans[i]);
    }
}
