#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define mod 999997
int n;
int data[11];
int tdata[11];
int tpin,twin;
long long enhash(int tmod)
{
    //memcpy(tdata,data,sizeof data);
    for each(i,n)tdata[i]=data[i];
    sort(tdata+1,tdata+n+1);
    long long res=0;
    for each(i,n)
    {
        res=res*27+tdata[i];
    }
    /*if(res<0)
    {
        for each(i,n)cout<<data[i]<<" ";
    }cout<<endl;*/
    if(tmod)
    return res%tmod;
    else return res;
}
struct hashtable
{
    struct lnode{long long to;int res,next;}myl[100000001];
    int pmyl;
    struct hnode{int first;}myh[1000001];
    
    void add(int tres)
    {
        for each(i,n)cout<<data[i]<<" ";cout<<":"<<tres<<endl;
        //cout<<"Add:"<<tres<<endl;
        int thash=(int)enhash(mod);
        myl[++pmyl].res=tres;
        myl[++pmyl].to=enhash(0);
        myl[++pmyl].next=myh[thash].first;
        myh[thash].first=pmyl;
        //cout<<thash<<"Added:"<<tres<<endl;
    }
    int ask()
    {
        for each(i,n)cout<<data[i]<<" ";cout<<endl;
        int thash=(int)enhash(mod);
        long long tsource=enhash(0);
        for(int p=myh[thash].first;p;p=myl[p].next)
        {
            if(myl[p].to==tsource)
            {
                return myl[p].res;
            }
        }
        return -1;
    }
}myh;
int search(int ip1,int ip2)
{
    //cout<<"S:"<<ip1<<","<<ip2<<":"<<data[1]<<data[2]<<data[3]<<endl;
    if(ip1==n)
    {
        //for each(i,n)if(data[i])return 0; 
        if(data[n])return 0;
        return 1;
    }
    int tget;
    if(data[n]==-1)return 0;
    int res=0;
    int nip1,nip2;
    if(ip2==n)
    {
        nip1=ip1+1;
        nip2=nip1+1;
        if(data[ip1]==3)goto there2;
        if(data[ip1]>=2)return 0;
        if(data[ip1]==1)goto there1;
    }else{nip1=ip1;nip2=ip2+1;};
    if(data[ip1]>3*(n-ip2+1))return 0;
    if(data[ip2]>3*(n-ip1+1))return 0;
    
    tget=myh.ask();
    if(tget!=-1)
    {
        cout<<tget<<endl;
        return tget;
    }
    if(data[ip2]>=3&&twin)
    {
        data[ip2]-=3;--twin;
        res+=search(nip1,nip2);
        data[ip2]+=3;++twin;
    }
    if(data[ip2]>=1&&data[ip1]>=1&&tpin)
    {
        there1:;
        --data[ip2];--data[ip1];--tpin;
        res+=search(nip1,nip2);
        ++data[ip2];++data[ip1];++tpin;
    }
    if(data[ip1]>=3&&twin)
    {
        there2:;
        data[ip1]-=3;--twin;
        res+=search(nip1,nip2);
        data[ip1]+=3;++twin;
    }
    if(res)myh.add(res);
    return res;
}
int dfs(int ip1)
{
    int res=0;
    while(data[ip1]==0)
    {
        if(ip1==n)return 1;
        ip1++;
    }
    for every(ip2,ip1+1,n)
    {
        if(data[ip2]>=3)
        {
            data[ip2]-=3;
            res+=dfs(ip1);
            data[ip2]+=3;
        }
        if(data[ip2]>=1&&data[ip1]>=1)
        {
            --data[ip2];--data[ip1];
            res+=dfs(ip1);
            ++data[ip2];++data[ip1];
        }
        if(data[ip1]>=3)
        {
            data[ip1]-=3;--twin;
            res+=dfs(ip1);
            data[ip1]+=3;++twin;
        }
    }
    return res;
}
int main()
{
    freopen("3139.in","r",stdin);
    freopen("3139.out","w",stdout);
    scanf("%d",&n);
    int allsum=0;
    int allwin=n*(n-1)/2*3;
    for each(i,n)
    {
        scanf("%d",&data[i]);
        allsum+=data[i];
    }
    tpin=allwin-allsum;
    twin=n*(n-1)-tpin;
    //cout<<tpin<<","<<twin<<endl;
    printf("%d",search(1,2));
    //printf("%d",dfs(1));
}
