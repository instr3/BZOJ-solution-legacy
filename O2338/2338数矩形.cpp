#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)

#define sqr(x) ((x)*(x))
int n;
struct zdpoint
{
    int x,y;
    zdpoint operator -(zdpoint ano)const
    {
        return (zdpoint){x-ano.x,y-ano.y};
    }
}ind[1501];
long double abs(zdpoint ia)
{
    return sqrtl((long double)(sqr(ia.x)+sqr(ia.y)));
}
struct tnode
{
    int x,y;long long len2;
    int n1,n2;
    bool operator <(tnode ano)const
    {
        return x==ano.x?(y==ano.y?len2<ano.len2:y<ano.y):x<ano.x;
    }
    bool operator ==(tnode ano)const
    {
        return x==ano.x&&y==ano.y&&len2==ano.len2;
    }
}tdata[1500*1500];int pdata;
int main()
{
    freopen("2338.in","r",stdin);
    freopen("2338.out","w",stdout);
    scanf("%d",&n);
    for each(i,n)
    {
        scanf("%d%d",&ind[i].x,&ind[i].y);
    }
    for each(i,n)
    {
        for every(j,i+1,n)
        {
            tdata[++pdata].x=ind[i].x+ind[j].x;
            tdata[pdata].y=ind[i].y+ind[j].y;
            tdata[pdata].len2=sqr((long long)(ind[i].x-ind[j].x))+sqr((long long)ind[i].y-ind[j].y);
            tdata[pdata].n1=i;
            tdata[pdata].n2=j;
        }
    }
    sort(tdata+1,tdata+pdata+1);
    long long maxres=0;
    for each(i,pdata)
    {
        if(i-1&&tdata[i]==tdata[i-1])
        {
            cout<<"Find A:"<<abs(ind[tdata[i].n1]-ind[tdata[i-1].n1])<<","<<"B"<<":"<<abs(ind[tdata[i].n2]-ind[tdata[i-1].n1])<<endl;
            maxres=max(maxres,(long long)(abs(ind[tdata[i].n1]-ind[tdata[i-1].n1])*abs(ind[tdata[i].n2]-ind[tdata[i-1].n1])));
        }
    }
    cout<<maxres<<endl;
}
