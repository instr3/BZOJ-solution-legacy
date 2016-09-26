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
#define	rep(i,a,b)	for(int i=a,tt=b;i<=tt;++i)
#define	drep(i,a,b)	for(int i=a,tt=b;i>=tt;--i)
#define	erep(i,e,x)	for(int i=x;i;i=e[i].next)
#define	irep(i,x)	for(__typedef(x.begin()) i=x.begin();i!=x.end();i++)
#define	read()	(strtol(ipos,&ipos,10))
#define	sqr(x)	((x)*(x))
#define	pb	push_back
#define	PS	system("pause");
typedef	long long	ll;
typedef	pair<int,int>	pii;
const int oo=~0U>>1;
const double inf=1e100;
const double eps=1e-6;
string name="", in=".in", out=".out";
//Var
int n,m,R,C,ans=oo;
int map[1008][1008];
int lmax[1008][1008],lmin[1008][1008],hmax[1008][1008],hmin[1008][1008];
deque<pii> qmax,qmin;
void Calc(int col)
{
	qmax.clear();qmin.clear();
	rep(i,1,R)
	{
		while(!qmax.empty()&&i-qmax.front().second>=n)qmax.pop_front();
		while(!qmin.empty()&&i-qmin.front().second>=n)qmin.pop_front();
		while(!qmax.empty()&&qmax.back().first<=map[i][col])qmax.pop_back();
		while(!qmin.empty()&&qmin.back().first>=map[i][col])qmin.pop_back();
		qmax.pb(pii(map[i][col],i));
		qmin.pb(pii(map[i][col],i));
		if(i>=n)
			lmax[i-n+1][col]=qmax.front().first,
			lmin[i-n+1][col]=qmin.front().first;
	}
}
void Calc2(int row)
{
	qmax.clear();qmin.clear();
	rep(i,1,C)
	{
		while(!qmax.empty()&&i-qmax.front().second>=n)qmax.pop_front();
		while(!qmin.empty()&&i-qmin.front().second>=n)qmin.pop_front();
		while(!qmax.empty()&&qmax.back().first<=lmax[row][i])qmax.pop_back();
		while(!qmin.empty()&&qmin.back().first>=lmin[row][i])qmin.pop_back();
		qmax.pb(pii(lmax[row][i],i));
		qmin.pb(pii(lmin[row][i],i));
		if(i>=n)
			hmax[row][i-n+1]=qmax.front().first,
			hmin[row][i-n+1]=qmin.front().first;
	}
}
void Init()
{
	scanf("%d%d%d",&R,&C,&n);
	rep(i,1,R)rep(j,1,C){scanf("%d",&map[i][j]);}
}
void Work()
{
	rep(i,1,C)
		Calc(i);
	rep(i,1,R)Calc2(i);
	rep(i,1,R-n+1)rep(j,1,C-n+1)ans=min(ans,hmax[i][j]-hmin[i][j]);
	cout<<ans<<endl;
}
int main()
{
    freopen("1047.in","r",stdin);
    freopen("1047.out","w",stdout);
//	freopen((name+in).c_str(),"r",stdin);
//	freopen((name+out).c_str(),"w",stdout);
	Init();
	Work();
	
	return 0;
}
