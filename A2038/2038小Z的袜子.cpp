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
//TJ:http://hi.baidu.com/wjbzbmr/item/7ad9d409663db62fa0312dd0
int sqrtn;
struct qnode
{
    int lt,rt;
    int num;
    inline bool operator < (qnode ano) const
    {
        return lt/sqrtn==ano.lt/sqrtn?rt<ano.rt:lt<ano.lt;
    }
}myq[50001];
int indata[50001];
long long tres[50001];
long long tbd[50001];
int n,nm;
long long tcw;
int tct[50001],tlt=1,trt;
inline int gcd(int ia,int ib)
{
    int ir=ia%ib;
    while(ir)
    {
        ia=ib;ib=ir;ir=ia%ib;
    }
    return ib;
}
int main()
{
    scanf("%d%d",&n,&nm);
    for each(i,n)scanf("%d",&indata[i]);
    for each(i,nm)scanf("%d%d",&myq[i].lt,&myq[i].rt),myq[i].num=i;
    sqrtn=(int)sqrt((double)n);
    
    sort(myq+1,myq+nm+1);
    
    int tnl,tnr;
    for each(i,nm)
    {
        tnl=myq[i].lt;
        tnr=myq[i].rt;
        while(tnl>tlt)
        {
            tcw-=tct[indata[tlt]]-1;
            tct[indata[tlt]]--;
            tlt++;
        }
        while(tnl<tlt)
        {
            tlt--;
            tcw+=tct[indata[tlt]];
            tct[indata[tlt]]++;
        }
        while(tnr<trt)
        {
            tcw-=tct[indata[trt]]-1;
            tct[indata[trt]]--;
            trt--;
        }
        while(tnr>trt)
        {
            trt++;
            tcw+=tct[indata[trt]];
            tct[indata[trt]]++;
        }
        tres[myq[i].num]=tcw;
        tbd[myq[i].num]=((long long)myq[i].rt-myq[i].lt+1)*(myq[i].rt-myq[i].lt)/2;
        //cout<<i<<":"<<tcw<<endl;
    }
    int tg;
    for each(i,nm)
    {
        tg=gcd(tres[i],tbd[i]);
        printf("%d/%d\n",(int)(tres[i]/tg),(int)(tbd[i]/tg));
    }
    system("pause");
}
    
