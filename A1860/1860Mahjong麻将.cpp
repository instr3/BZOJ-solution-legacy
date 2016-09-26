#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
//#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
#define trimax(a,b,c) max((a),max((b),(c)))
//struct lnode{int next;long long w;}myl[1000000];int pmyl;
//struct hnode{int first;}myh[3000000];
bool myh[3000000];
int tdata[104];
bool succeed;
inline long long enhash(int pos,int iz)
{
    long long res=pos;
    res=res*11+tdata[pos++];
    res=res*11+tdata[pos++];
    res=res*11+tdata[pos++];
    res=res*2+iz;
    return res;
}
inline bool exist(int pos,int iz)
{
    return myh[enhash(pos,iz)];
    //int thash=enhash(pos,iz);
    //for(int p=myh[thash%2999999].first;p;p=myl[p].next)
    //{
    //    if(myl[p].w==thash)return true;
    //}
    //return false;
}
inline void insert(int pos,int iz)
{
    myh[enhash(pos,iz)]=true;
    //int thash=enhash(pos,iz);
    //int thashmd=thash%2999999;
    //myl[++pmyl].w=thash;
    //myl[pmyl].next=myh[thashmd].first;
    //myh[thashmd].first=pmyl;
}
void dfs(int pos,bool iz)
{
    
    while(pos<=100&&tdata[pos]==0)pos++;
    if((!iz)&&pos==101)
    {
        succeed=true;
        return;
    }
    if(exist(pos,iz))return;
    insert(pos,iz);
    //cout<<pos<<":"<<tdata[pos]<<tdata[pos+1]<<tdata[pos+2]<<":"<<iz<<endl;
    if(tdata[pos]>=4)
    {
        tdata[pos]-=4;
        dfs(pos,iz);
        tdata[pos]+=4;
    }
    if(tdata[pos]>=3)
    {
        tdata[pos]-=3;
        dfs(pos,iz);
        tdata[pos]+=3;
    }
    if(tdata[pos]&&tdata[pos+1]&&tdata[pos+2])
    {
        tdata[pos]--;tdata[pos+1]--;tdata[pos+2]--;
        dfs(pos,iz);
        tdata[pos]++;tdata[pos+1]++;tdata[pos+2]++;
    }
    if(iz&&tdata[pos]>=2)
    {
        tdata[pos]-=2;
        dfs(pos,0);
        tdata[pos]+=2;
    }
}
void task()
{
    for each(i,100)
    {
        scanf("%d",&tdata[i]);
        if(tdata[i]==13)tdata[i]=9;
        if(tdata[i]>=11)tdata[i]=8;
    }
    //pmyl=0;
    memset(myh,0,sizeof(myh));
    succeed=false;
    dfs(1,1);
    if(succeed)
    printf("Yes\n");else printf("No\n");
}
int main()
{
    freopen("2.in","r",stdin);
    freopen("2.out","w",stdout);
    int n;scanf("%d",&n);
    for each(i,n)task();
}
