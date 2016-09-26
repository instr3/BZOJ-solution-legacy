#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
int n;
int data[11];
int tpin,twin;
int search(int ip1,int ip2)
{
    //cout<<"S:"<<ip1<<","<<ip2<<":"<<data[1]<<data[2]<<data[3]<<endl;
    if(ip1==n)
    {
        //for each(i,n)if(data[i])return 0; 
        if(data[n])return 0;
        return 1;
    }
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
    return res;
}
int main()
{
    freopen("1306.in","r",stdin);
    freopen("1306.out","w",stdout);
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
}
