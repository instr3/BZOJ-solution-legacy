#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<fstream>
#include<map>
#include<ctime>
#include<set>
#include<queue>
#include<cmath>
#include<vector>
#include<bitset>
#include<functional>
#define x first
#define y second
#define mp make_pair
#define pb push_back
using namespace std;

typedef long long LL;
typedef double ld;

const int MAX=600+10;

int n,del[MAX];
ld r[MAX],h[MAX],ALPHA,a[MAX],b[MAX],he[MAX],the[MAX];

ld work(ld x)
{
    int i;
    ld l=0,len;
    for(i=1;i<=n;++i)
        if((len=abs(x-h[i]))<=r[i])
            l=max(l,sqrt(r[i]*r[i]-len*len));
    for(i=1;i<n;++i)
    {
        if(del[i])continue;
        if(x>=a[i] && x<=b[i])
            l=max(l,he[i]+(x-a[i])*the[i]);
    }
    return l;
}

ld sps(ld L,ld R,ld FL,ld FM,ld FR)
{
    return (R-L)*(FL+FR+FM*4)/6;
}

ld calc(ld left,ld mid,ld right,ld FL,ld FM,ld FR,ld pre)
{
    ld ml=(left+mid)/2,mr=(mid+right)/2;
    ld nfl=work(ml),nfr=work(mr);
    ld s1=sps(left,mid,FL,nfl,FM);
    ld s2=sps(mid,right,FM,nfr,FR);
    if(fabs(s1+s2-pre)<1e-5)return pre;
    return calc(left,ml,mid,FL,nfl,FM,s1)+calc(mid,mr,right,FM,nfr,FR,s2);
}

int main()
{
    freopen("1502.in","r",stdin);
    freopen("1502.out","w",stdout);
    int i;
    ld left=0,right=0;
    scanf("%d%lf",&n,&ALPHA);
    ++n;
    for(i=1;i<=n;++i)
    {
        scanf("%lf",&h[i]);
        h[i]+=h[i-1];
    }
    for(i=1;i<=n;++i)
        h[i]/=tan(ALPHA);
    for(r[n]=0,i=1;i<n;++i)scanf("%lf",&r[i]);
    for(i=1;i<n;++i)
    {
        if((r[i+1]>=h[i+1]-h[i]+r[i]) || (r[i]>h[i+1]-h[i]+r[i+1]))
        {
            del[i]=1;
            continue;
        }
        ld p=acos((r[i+1]-r[i])/(h[i]-h[i+1]));
        a[i]=h[i]+r[i]*cos(p);
        b[i]=h[i+1]+r[i+1]*cos(p);
        he[i]=r[i]*sin(p);
        the[i]=1/tan(-p);
    }
    for(i=1;i<=n;++i)left=min(left,h[i]-r[i]);
    for(i=1;i<=n;++i)right=max(right,h[i]+r[i]);
    cout<<h[1]<<endl;
    printf("%.2lf\n",calc(left,(left+right)/2,right,work(left),work((left+right)/2),work(right),1e100)*2);
    return 0;
}
