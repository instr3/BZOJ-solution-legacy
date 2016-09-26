//Lib
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<ctime>

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
using namespace std;
//Macro
#define rep(i,a,b) for(int i=a,tt=b;i<=tt;++i)
#define drep(i,a,b) for(int i=a,tt=b;i>=tt;--i)
#define erep(i,e,x) for(int i=x;i;i=e[i].next)
#define irep(i,x) for(__typedef(x.begin()) i=x.begin();i!=x.end();i++)
#define read() (strtol(ipos,&ipos,10))
#define sqr(x) ((x)*(x))
#define pb push_back
#define PS system("pause");
typedef long long ll;
typedef pair<int,int> pii;
const int oo=~0U>>1;
const double inf=1e100;
const double eps=1e-6;
string name="",in=".in",out=".out";
//Var
const int mod=10007;
int n,m,ans,maxx;
int s[50008],a[50008];
int f[2000][50008],g[50008],p[50008];
inline void inc(int &x,int y){x+=y;x%=mod;}
bool Check(int limit)
{
	int sum=0,cnt=0,i=1;
	rep(i,1,n)
	{
		sum+=a[i];
		if(sum>limit)cnt++,sum=a[i];
	}
	return cnt+1<=m;
}
int Calc()
{
	int l=maxx,r=s[n],mid;
	while(l<=r)
	{
		mid=l+r>>1;
		if(Check(mid))r=mid-1;
		else l=mid+1;
	}
	return l;
}
//f[i][j]??i?j?
int Calc(int limit)
{
	int ret=0,now=0,pre,pos=0;
	f[0][0]=1;g[0]=1;
	rep(i,1,n){while(s[i]-s[pos]>limit)pos++;p[i]=pos;g[i]=1;}
	rep(i,1,m)
	{
		pre=now;now^=1;
		memset(f[now],0,sizeof f[now]);
		rep(j,1,n)
			inc(f[now][j],g[j-1]-g[p[j]]+f[pre][p[j]]);
		inc(ret,f[now][n]);g[0]=0;
		rep(j,1,n){g[j]=g[j-1]+f[now][j];}
	}
	return ret;
}
void Work()
{
	scanf("%d%d",&n,&m);m++;
	rep(i,1,n)scanf("%d",a+i),s[i]=s[i-1]+a[i],maxx=max(maxx,a[i]);
	ans=Calc();
	printf("%d %d\n",ans,Calc(ans));
}
int main()
{
    freopen("1044.in","r",stdin);
    freopen("1044.out","w",stdout);
	Work();
	return 0;
}
