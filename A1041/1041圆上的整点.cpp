#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
#define each(i,n) (int i=1;i<=n;++i)
#define sqr(i) ((i)*(i))
int ir;long long isr;
long long tn;
int tot;
struct snode{long long n,m;
    bool operator <(snode ano) const{return n==ano.n?m<ano.m:n<ano.n;}
}tps;
set<snode>mys;
void print(long long num)
{
    cout<<num;
}
int gcd(int a,int b)
{
    int r=a%b;
    while(r)
    {
        a=b;b=r;r=a%b;
    }
    return b;
}    
void task(int ir,int ik)
{
    long long tm2,tm;
    if(ir<5)return;
    long long ir2=(long long)sqrt((long double)ir/2);
    for(tn=1;tn<=ir2;++tn)
    {
        tm2=ir-sqr(tn);
        if(sqr((long long)sqrt(tm2))==tm2)
        {
            tot++;
            tm=(int)sqrt(tm2);
           // if(gcd(tn,tm)==1){
                //if(sqr(tn)/2==tm)continue;
                //if(tn%2==0&&sqr(tn/2)==tm+1)continue;
            //print((sqr(tm)-sqr(tn))*ik);
            //cout<<",";
            //print(2*tm*tn);
            //cout<<",";
            //print(ir);
            //cout<<endl;//}
            tps.n=(sqr(tm)-sqr(tn))*ik;
            tps.m=(2*tm*tn*ik);
            if(tps.n<tps.m)swap(tps.n,tps.m);
            if(tps.m)
            mys.insert(tps);
        }
    }//}
    
    //cout<<tot*8+4;
}
int main()
{
    freopen("1041.in","r",stdin);
    freopen("1041.out","w",stdout);
    scanf("%d",&ir);
    isr=(int)sqrt(ir);

    int ik;
    for each(i,isr)if(ir%i==0)
    {
        ik=ir/i;
        task(i,ik);
        task(ik,i);
    }
    
    cout<<mys.size()*8+4;
}
