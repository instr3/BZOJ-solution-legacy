#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map> 
using namespace std;
const int u=200010;
struct rec{int x,y,z;}a[u];
struct splaytree{
	int l,r,dat,val,ad,size; long long sum;
	#define l(x) t[x].l
	#define r(x) t[x].r
	#define dat(x) t[x].dat
	#define val(x) t[x].val
	#define ad(x) t[x].ad
	#define size(x) t[x].size
	#define sum(x) t[x].sum
}t[u];
int L[u],R[u],n,p,tot,i,j,k,mod=1000000007;
long long lv[u],rv[u],ans;
map<int,long long> f;

bool cmp1(rec a,rec b)
{
	return a.x<b.x||a.x==b.x&&a.y<b.y;
}
bool cmp2(rec a,rec b)
{
	return a.x>b.x||a.x==b.x&&a.y<b.y;
}

inline void add(int x,int y)
{
	sum(x)+=(long long)size(x)*y,val(x)+=y,ad(x)+=y;
}
inline void update(int x)
{
	size(x)=size(l(x))+size(r(x))+1;
	sum(x)=sum(l(x))+sum(r(x))+val(x);
}
inline void spread(int x)
{
	if(ad(x)) add(l(x),ad(x)),add(r(x),ad(x)),ad(x)=0;
}

inline void zig(int &x)
{
	int y=l(x); l(x)=r(y); r(y)=x;
	update(x),update(y),x=y;
}
inline void zag(int &x)
{
	int y=r(x); r(x)=l(y); l(y)=x;
	update(x),update(y),x=y;
}

void splay(int &x,int y)
{
	L[0]=R[0]=0;
	while(1)
	{
		spread(x),spread(l(x)),spread(r(x));
		if(dat(x)==y||!l(x)&&y<dat(x)||!r(x)&&y>dat(x)) break;
		if(y<dat(x))
		{
			if(y<dat(l(x))) {zig(x); if(!l(x)) break;}
			R[++R[0]]=x,x=l(x);
		}
		else{
			if(y>dat(r(x))) {zag(x); if(!r(x)) break;}
			L[++L[0]]=x,x=r(x);
		}
	}
	L[L[0]+1]=l(x),R[R[0]+1]=r(x);
	for(int i=L[0];i;i--) r(L[i])=L[i+1],update(L[i]);
	for(int i=R[0];i;i--) l(R[i])=R[i+1],update(R[i]);
	l(x)=L[1],r(x)=R[1],update(x);
}

void root(int x)
{
	splay(p,x);
	while(dat(p)<=x) {splay(r(p),-1); zag(p);}
}

void insert(int x)
{
	root(x);
	tot++,dat(tot)=x,l(tot)=l(p),r(tot)=p,l(p)=0,p=tot;
	update(r(p)),update(p);
}

void solve(long long ans[u])
{
	memset(t,0,sizeof(t));
	f.clear();
	tot=p=2;
	dat(1)=0x3fffffff,dat(2)=-dat(1),r(2)=1,size(1)=1,size(2)=2;
	for(i=j=1;i<=n;i=j)
	{
		for(;j<=n&&a[i].x==a[j].x;j++)
		{
			root(a[j].y);
			ans[a[j].z]=sum(p)-sum(l(p))-(i-1+f[a[j].y]);
		} 
		for(k=i;k<j;k++)
		{
			insert(a[k].y);
			add(r(p),1);
			val(p)-=size(r(p))-1;
			f[a[k].y]+=size(r(p))-1;
			update(p);
		}
	}
}

int main()
{
    freopen("2441.in","r",stdin);
    freopen("2441.out","w",stdout);
	cin>>n;
	for(i=1;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y);
	sort(a+1,a+n+1,cmp1);
	for(i=1;i<=n;i++) a[i].z=i;
	solve(lv);
	sort(a+1,a+n+1,cmp2);
	solve(rv);
	for(i=1;i<=n;i++) {cout<<lv[i]<<","<<rv[i]<<endl;ans+=lv[i]*rv[i]%mod;}
	cout<<ans%mod<<endl;
	return 0;
}
