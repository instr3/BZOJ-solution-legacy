#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
//#include <cassert>
using namespace std;
#define rep(i,n) for(int i=1;i<=(n);++i)
#define rep2(i,a,b) for(int i=(a);i<=(b);++i)
int n,nm;
struct ctree
{
	int d[100001];
	void add(int in,int iw)
	{
		while(in<=n)
		{
			d[in]+=iw;
			in+=in&-in;
		}
	}
	int sum(int in)
	{
		int res=0;
		while(in)
		{
			res+=d[in];
			in-=in&-in;
		}
		return res;
	}
}myt;
int ind[100001];
int tp[100001];
bool visit[100001];
int inm[100001];int pm;
long long ans[100001];
struct snode
{
	int p,d,o;
	bool i;
	bool operator <(snode ano)const
	{
		return d>ano.d;
	}
}ts[100001];int ps;
void partition(int il,int ir)
{
	if(il+1==ir)return;
	int im=(il+ir)>>1;
	partition(il,im);
	ps=0;
	rep2(i,il,im-1)
	{
		ts[++ps].p=tp[inm[i]];
		ts[ps].d=inm[i];
		ts[ps].i=true;
	}
	rep2(i,im,ir-1)
	{
		ts[++ps].p=tp[inm[i]];
		ts[ps].d=inm[i];
		ts[ps].o=i;
		ts[ps].i=false;
	}
	sort(ts+1,ts+ps+1);
	rep(i,ps)
	{
		if(ts[i].i)
			myt.add(ts[i].p,1);
		else
			ans[ts[i].o]+=myt.sum(ts[i].p);
	}
	rep(i,ps)
	{
		if(ts[i].i)
			myt.add(ts[i].p,-1);
		else
			ans[ts[i].o]+=myt.sum(n)-myt.sum(ts[i].p);
		
	}
	partition(im,ir);
}
int main()
{
	scanf("%d%d",&n,&nm);
	rep(i,n)
	{
		scanf("%d",&ind[i]);
		tp[ind[i]]=i;
		visit[i]=1;
	}
	rep(i,nm)
	{
		scanf("%d",&inm[i]);
		visit[inm[i]]=0;
	}
	pm=nm;
	rep(i,n)
	{
		if(visit[i])inm[++pm]=i;
	}
	reverse(inm+1,inm+n+1);
	partition(1,n+1);
	rep(i,n)ans[i]+=ans[i-1];
	for(int i=n;i>n-nm;--i)
	{
		printf("%lld\n",ans[i]);
	}
	
}
