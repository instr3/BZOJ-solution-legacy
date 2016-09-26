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
int n;int indata[20001];
long long sum;
int minw=0;
inline int getnum()
{
    char tc=0;
    int res=0;
    while(tc<'0'||tc>'9')tc=getchar();
    while(tc>='0'&&tc<='9')
    {
        res=res*10+tc-'0';
        tc=getchar();
    }
    return res;
}
int main()
{
    freopen("4.in","r",stdin);
    freopen("4.out","w",stdout);
    indata[0]=-99999999;
    scanf("%d",&n);
    for each(i,n)
    {
        indata[i]=getnum();
        sum+=indata[i];
        minw=max(minw,indata[i]+indata[i-1]);
    }
    minw=max(minw,indata[1]+indata[n]);
    if(n%2==0)printf("%d",minw);
    else printf("%d",max(minw,(int)((2*sum-1)/(n-1)+1)));
}
