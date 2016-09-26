#include<cstdio>
#include<algorithm>
#include<set>
#include<map>
#include<cstdlib>
#include<cstring>

using namespace std;
const int maxn=100010,maxk=20;
int N,K,m,tot,n;
int w[maxn],b[maxn];
int fs[maxn],oth[maxn*2],next[maxn*2];
int q[maxn],fa[maxn][maxk],h[maxn];
set<int>S;
map<int,int>G;

  struct node{
    node *l,*r; int s;
    inline node(){}
    inline node(node *l,node *r,int s):l(l),r(r),s(s){}
  }a[maxn*(2+maxk)],*root[maxn];
  inline node *build(int l,int r){
    int t=++tot,mid=l+r>>1;
    a[t]=l!=r?node(build(l,mid),build(mid+1,r),0):node(NULL,NULL,0);
    return &a[t];
  }
  inline node *change(node *p,int l,int r,const int &x,const int &w){
    if(l==r)return a[++tot]=node(NULL,NULL,p->s+w),&a[tot];
    int t=++tot,mid=l+r>>1;
    a[t]=x<=mid?node(change(p->l,l,mid,x,w),p->r,p->s+w):node(p->l,change(p->r,mid+1,r,x,w),p->s+w);
    return &a[t];
  }
  void LCA_pre(){
    int k,i;
    for(K=0;(1<<K+1)<=N;++K);
    for(k=1;k<=K;++k)
      for(i=1;i<=N;++i)if(h[i]>=(1<<k))
        fa[i][k]=fa[fa[i][k-1]][k-1];
  }
  inline int LCA(int x,int y){
    if(x==y)return x;
    if(h[x]<h[y])swap(x,y);
    int k;
    for(k=K;k!=-1;--k)if(h[x]-h[y]>=(1<<k))x=fa[x][k];
    if(x==y)return x;
    for(k=K;k!=-1;--k)if(fa[x][k]!=fa[y][k])x=fa[x][k],y=fa[y][k];
    return fa[x][0];
  }

int main(){
        freopen("2588.in","r",stdin);
    freopen("2588.out","w",stdout);
  if(true){
  int M,i,x,y,t,k,u,head,tail;
  scanf("%d%d",&N,&M);
  for(i=1;i<=N;++i)scanf("%d",w+i),S.insert(w[i]);
  for(set<int>::iterator it=S.begin();it!=S.end();++it)b[G[*it]=++n]=*it;
  for(i=1;i<=N;++i)w[i]=G[w[i]];
  for(i=1;i<N;++i){
    scanf("%d%d",&x,&y);
    oth[++m]=y,next[m]=fs[x],fs[x]=m;
    oth[++m]=x,next[m]=fs[y],fs[y]=m;
  }
  root[0]=build(1,n);
  for(q[head=tail=1]=1;head<=tail;)
    for(i=fs[u=q[head++]];i;i=next[i])
      if(oth[i]!=fa[u][0])fa[q[++tail]=oth[i]][0]=u,h[oth[i]]=h[u]+1;
  for(i=1;i<=N;++i)u=q[i],root[u]=change(root[fa[u][0]],1,n,w[u],1);
  LCA_pre();
  while(M--){
    scanf("%d%d%d",&x,&y,&k);
    t=LCA(x,y);
    node *a=root[x],*b=root[y],*c=root[fa[t][0]],*d=root[t];
    int l=1,r=n,s,mid;
    while(l!=r){
      s=a->l->s+b->l->s-c->l->s-d->l->s,mid=l+r>>1;
      if(s>=k)a=a->l,b=b->l,c=c->l,d=d->l,r=mid;
      else a=a->r,b=b->r,c=c->r,d=d->r,k-=s,l=mid+1;
    }
    printf("%d\n",::b[l]);
  }
  return 0;
}
}
