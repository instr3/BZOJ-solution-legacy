#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[55],b[2010],s[2010],f[55],sum,n,m,rest,l,r,mid,i;
bool dfs(int x,int last)
{
 if(!x) return 1;
 //if(rest<s[x]) return 0;
 int i,pos;
 for(i=last;i<=m;i++)
  if(f[i]>=b[x])
  {
   f[i]-=b[x]; rest-=b[x];
   //if(f[i]<b[1]) rest-=f[i];
   if(b[x]==b[x-1]) pos=last; else pos=1;
   if(dfs(x-1,pos)) return 1;
   //if(f[i]<b[1]) rest+=f[i];
   f[i]+=b[x]; rest+=b[x];
  }
 return 0;
}
int main()
{
        freopen("1082.in","r",stdin);
    freopen("1082.out","w",stdout);
 cin>>m;
 for(i=1;i<=m;i++) scanf("%d",&a[i]),sum+=a[i];
 sort(a+1,a+m+1);
 cin>>n;
 for(i=1;i<=n;i++) scanf("%d",&b[i]);
 sort(b+1,b+n+1);
 for(i=1;i<=n;i++) s[i]=s[i-1]+b[i];
 while(s[n]>sum) n--;
 l=0,r=n;
 //for(i=1;i<=m;i++) f[i]=a[i];
 //dfs(1000,1);
 //return 0;
 while(l<r)
 {
  mid=(l+r+1)>>1;
  for(i=1;i<=m;i++) f[i]=a[i];
  rest=sum;
  cout<<l<<","<<r<<","<<mid<<endl;
  if(dfs(mid,1)) l=mid; else r=mid-1;
 }
 cout<<l<<endl;
 return 0;
}
