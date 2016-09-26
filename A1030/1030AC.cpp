#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<cmath>
const int maxn=7000,MC=10007;
int N,M,tot,nil,root;
int c[maxn][26],cnt[maxn],fail[maxn];
int q[maxn],head,tail;
int trans[maxn][26];
char s[200];
int f[101][maxn];

  inline void ref(int &x,const int &y){
    x+=y;
    while(x>=MC)x-=MC;
  }

  void BuildTrie(){
    int i,j,n,now,d;
    nil=1; root=tot=2;
    for(j=1;j<=N;++j){
      scanf("%s",s);
      n=strlen(s); now=root;
      for(i=0;i<n;++i){
        d=s[i]-65;
        if(!c[now][d])c[now][d]=++tot;
        now=c[now][d];
      }
      cnt[now]=1;
    }
  }
  
  void BuildAC(){
    int u,i,t,p;
    fail[root]=nil;
    q[head=tail=1]=root;
    while(head<=tail){
      u=q[head++];
      for(i=0;i<26;++i)
        if((t=c[u][i])!=0){
          if(u==root)fail[t]=root;
          else{
            for(p=fail[u];p!=root;p=fail[p])
              if(c[p][i])break;
            fail[t]=(c[p][i])?c[p][i]:root;
          }
          for(p=fail[t];p!=root;p=fail[p])
            if(cnt[p])break;
          if(cnt[p])cnt[t]=1;
          q[++tail]=t;
        }
    }
  }
  
  inline int GetTrans(int x,int w){
    if(c[x][w])return c[x][w];
    int p;
    for(p=fail[x];p!=nil;p=fail[p])if(c[p][w])return c[p][w];
    return root;
  }

int main(){
    freopen("1030.in","r",stdin);
    freopen("1030.out","w",stdout);
  int i,j,ans,tans,k,p;
  scanf("%d%d",&N,&M);
  BuildTrie();
  BuildAC();
  for(i=2;i<=tot;++i)
    for(j=0;j<26;++j)
      trans[i][j]=GetTrans(i,j);
  f[0][root]=1;
  for(k=0;k<M;++k)
    for(i=root;i<=tot;++i)
      for(j=0;j<26;++j)
        if(!cnt[p=trans[i][j]])
          ref(f[k+1][p],f[k][i]);
  ans=1;
  for(i=1;i<=M;++i)ans=(ans*26)%MC;
  tans=0;
  for(i=root;i<=tot;++i)ref(tans,f[M][i]);
  ans-=tans;
  while(ans<0)ans+=MC;
  printf("%d\n",ans);
  return 0;
}
