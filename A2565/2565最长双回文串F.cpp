#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <windows.h>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define each2(i,n) (int i=n;i;--i)
#define every2(i,a,b) (int i=(b);i.=(a);--i)
int n;
char indata[10002];

/*struct lnode{int num,next;}myl[10001];int pmyl;
struct hnode{int first;}myh[128];
int trank[20001],tsrank[20001];
int tplace[10001];int pplace;
//aabaaaab
//11211112
//12411123
//46812357
inline void insert(int inum)
{
    if(inum<=0)return;
    //cout<<inum<<endl;
    char ichr=indata[inum];
    myl[++pmyl].num=inum;
    myl[pmyl].next=myh[(int)ichr].first;
    myh[(int)ichr].first=pmyl;
}
inline void analyze()
{
    for each2(i,n)
    {
        insert(i);
    }
    int prank=0,tlast=0;
    for(int k=1;k<=n;k<<=1)
    {
        prank=0;pplace=0;
        for each(ic,127)
        {
            if(!myh[ic].first)continue;
            tlast=-1;
            for(int p=myh[ic].first;p;p=myl[p].next)
            {
                if(tlast!=tsrank[myl[p].num+k/2])prank++;
                tlast=tsrank[myl[p].num+k/2];
                trank[myl[p].num]=prank;
                tplace[++pplace]=myl[p].num;
            }
        }
        for each(i,n)tsrank[i]=trank[i];
        memset(myh,0,sizeof myh);pmyl=0;
        for each(i,n)cout<<trank[i]<<" ";cout<<endl;
        for each2(i,n)
        {
            insert(tplace[i]-k);
        }
        for every(i,n-k+1,n)
        {
            insert(i);
        }
    }
    return;
    prank=0;pplace=0;
    for each(ic,127)
    {
        if(!myh[ic].first)continue;
        tlast=-1;
        for(int p=myh[ic].first;p;p=myl[p].next)
        {
            if(tlast!=trank[myl[p].num+1])prank++;
            tlast=trank[myl[p].num+1];
            trank[myl[p].num]=prank;
            tplace[++pplace]=myl[p].num;
        }
    }
    for each(i,n)cout<<trank[i]<<" ";cout<<endl;
}*/
int main()
{
    freopen("2565.in","r",stdin);
    freopen("2565.out","w",stdout);
    scanf("%s",&indata[1]);
    n=strlen(&indata[1]);
    
}
