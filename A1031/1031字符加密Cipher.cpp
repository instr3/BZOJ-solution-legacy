#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
//#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define hcae(i,n) (int i=(n);i>=1;--i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
#define rep(s) s;s;s;s;s;s;s;s;s;s;s
int n;char instr[2000015];
struct lnode{int pos,next;}myl[2000015];int pmyl;
struct hnode{int first;}myh[270];
int tlist[2000015];
inline void insert(char ic,int ipos)
{
    myl[++pmyl].pos=ipos;
    myl[pmyl].next=myh[(int)ic].first;
    myh[(int)ic].first=pmyl;
}
int main()
{
    freopen("1031.in","r",stdin);
    freopen("1031.out","w",stdout);
    scanf("%s",&instr[1]);
    n=strlen(&(instr[1]));
    if(n==1)cout<<instr[1],exit(0);
    for each(i,n)
    {
        instr[n+i]=instr[i];
    }
    for hcae(i,n)insert(instr[i],i);
    int ti,tin;
    for(int tnum=1;tnum<n;tnum<<=1)
    {
        ti=0;
        for each(i,127)
        {
            for(int p=myh[i].first;p;p=myl[p].next)
            tlist[++ti]=myl[p].pos;
        }
        for each(i,n)cout<<tlist[i]<<" ";cout<<endl;
        memset(myh,0,sizeof(myh));
        pmyl=0;
        for hcae(i,n)
        {
            tin=n+tlist[i]-1;//1 is var
            insert(instr[tin],(tin-1)%n+1);
        }
    }
    for each(i,n)
    {
        printf("%c",instr[tlist[i]+n-1]);
    }
}
    
