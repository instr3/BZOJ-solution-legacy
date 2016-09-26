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
//#define rstr(i) ((int*)(indata+tboard[i]-1))
int n,nk;
int indata[400001];
int trank[400001];
struct lnode{int pos,td2,next;}myl[200001];int pmyl;
struct hnode{int first;}myh[200001];
inline void insert(int id,int id2,int ipos)
{
    myl[++pmyl].pos=ipos;
    myl[pmyl].td2=id2;
    myl[pmyl].next=myh[id].first;
    myh[id].first=pmyl;
}
int tboard[200001];int ptb;
int height[200001];
inline int maxpre(int ia,int ib,int istart)//必须确保istart位相同 
{
    if(ib==0)return 0;
    istart++;
    for(;;istart++)
    {
        if((indata+ia-1)[istart]!=(indata+ib-1)[istart])break;
    }
    return istart-1;
}
int task(int in)
{
    int tcounter=0;
    for each(i,n)
    {
        if(height[i]<in)tcounter=1;
        else tcounter++;
        if(tcounter>=nk)return true;
    }
    return false;
}
int thash[10000001];
int main()
{
    freopen("1717.in","r",stdin);
    freopen("1717.out","w",stdout);
    scanf("%d%d",&n,&nk);
    int tin;
    int tnrank;int tlast;
    for each(i,n)
    {
        scanf("%d",&indata[i]);
        thash[indata[i]]=1;
    }
    int tcount=0;
    for every(i,0,1000000)
    {
        if(thash[i])thash[i]=++tcount;
    }
    for each(i,n)
    {
        indata[i]=thash[indata[i]];
        //cout<<indata[i]<<" ";
    }
    for hcae(i,n)
    {
        insert(indata[i],0,i);
    }
    for(int iz=1;iz<=2*n;iz<<=1)
    {
        tnrank=0;
        for each(i,n)
        {
            tlast=-99999999;
            for(int p=myh[i].first;p;p=myl[p].next)
            {
                if(myl[p].td2!=tlast)
                {
                    tnrank++;
                    tlast=myl[p].td2;
                }
                tboard[++ptb]=myl[p].pos;
                trank[myl[p].pos]=tnrank;
                //cout<<tboard[ptb]<<" "<<trank<<endl;
            }
        }
        /*for each(i,n)
        {
            cout<<trank[i]<<" ";
        }
        cout<<endl;*/
        memset(myh,0,sizeof myh);pmyl=0;ptb=0;
        for hcae(i,n)
        {
            if(tboard[i]<=iz)continue;
            tin=tboard[i]-iz;
            insert(trank[tin],trank[tin+iz],tin);
        }
        for(int i=n;i>n-iz;--i)
        {
            insert(trank[i],0,i);
            //cout<<"-"<<trank[i]<<"-"<<endl;
        }
    }
    tlast=0;
    /*for each(i,n)
    {
        cout<<tboard[i]<<":";
        for every(j,tboard[i],n)
        {
            cout<<indata[j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;*/
    for each(i,n)
    {
        height[trank[i]]=maxpre(i,tboard[trank[i]-1],max(tlast-1,0));
        tlast=height[trank[i]];
        //cout<<height[trank[i]]<<" ";
    }
    /*for each(i,n)
    {
        cout<<setw(2)<<tboard[i]<<","<<setw(2)<<height[i]<<":";
        for every(j,tboard[i],n)
        {
            cout<<indata[j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;*/
    int tl=0,tr=10001,tm;
    while(tl+1!=tr)
    {
        tm=(tl+tr)/2;
        if(task(tm))
        {
            tl=tm;
        }
        else
        {
            tr=tm;
        }
    }
    cout<<tl<<endl;
}
