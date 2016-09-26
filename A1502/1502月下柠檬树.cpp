#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
long double inh[501];
long double ix[501],ir[501];
int n;
struct lnode
{
    long double k;
    long double b;
    long double lt,rt;
}myl[501];
inline const long double tf(long double tx)
{
    long double res=0;
    for each(i,n)
    {
        #define sqr(x) ((x)*(x))
        if(ix[i]+ir[i]<tx or ix[i]-ir[i]>tx)continue;
        res=max(res,sqrtl(sqr(ir[i])-sqr(ix[i]-tx)));
    }
    for each(i,n)
    {
        if(myl[i].lt<=tx&&tx<=myl[i].rt)
        {
            res=max(res,myl[i].k*tx+myl[i].b);
        }
    }
    //cout<<tx<<"::"<<res<<endl;
    return res;
}
inline const long double simpson(long double ta,long double tb){return (tb-ta)*(tf(ta)+4*tf((ta+tb)/2)+tf(tb))/6;}
long double getres(long double ta,long double tb)
{
    #define zero (1e-5L)
    #define myabs(x) ((x)>=0?(x):-(x))
    long double tm=(ta+tb)/2;
    long double res=simpson(ta,tb);

    long double tcom=simpson(ta,tm)+simpson(tm,tb)-res;
    //cout<<ta<<","<<tb<<":"<<res<<","<<tcom<<endl;
    if(myabs(tcom)<=zero)return res;
    return getres(ta,tm)+getres(tm,tb);
}
int main()
{
    freopen("1502.in","r",stdin);
    freopen("1502.out","w",stdout);
    double talpha;
    scanf("%d",&n);cin>>talpha;
    long double cota=1/(tanl((long double)talpha));
    for each(i,n+1)cin>>inh[i];
    long double ths=0;
    long double tl=9e99L,tr=-9e99L;
    for each(i,n)
    {
        cin>>ir[i];
        ths+=inh[i];
        ix[i]=ths*cota;
        //cout<<ix[i]<<","<<ir[i]<<endl;
        tl=min(tl,ix[i]-ir[i]);
        tr=max(tr,ix[i]+ir[i]);
    }
    ix[n+1]=(ths+inh[n+1])*cota;
    tr=max(tr,ix[n+1]);
    tl=min(tl,ix[n+1]);
    long double tx1,tx2,ty1,ty2;
    for each(i,n)
    {
        tx1=ix[i]-ir[i]*(ir[i+1]-ir[i])/(ix[i+1]-ix[i]);
        ty1=sqrt(sqr(ir[i])-sqr(ix[i]-tx1));
        tx2=ix[i+1]-ir[i+1]*(ir[i]-ir[i+1])/(ix[i]-ix[i+1]);
        ty2=sqrt(sqr(ir[i+1])-sqr(ix[i+1]-tx2));
        //cout<<tx1<<","<<ty1<<";"<<tx2<<","<<ty2<<endl;
        myl[i].k=(ty2-ty1)/(tx2-tx1);
        myl[i].b=ty1-myl[i].k*tx1;
        myl[i].lt=tx1;
        myl[i].rt=tx2;
    }
    //cout<<tf(tl+0.5)<<","<<tf(2.22250)<<","<<tf(tr-0.5)<<endl;
    printf("%.2f",(double)getres(tl-1,tr+1)*2);
}
    
