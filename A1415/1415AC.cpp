#include <string.h>
#include <iostream>
 #include <stdio.h>
 using namespace std;
 #define MAXN 1005
 struct edge{
     int v,n;
 }e[MAXN*2];
 int first[MAXN],es;
 int n,m,c1,c2,tu,tv;
 int p[MAXN][MAXN],deg[MAXN];
 double d[MAXN][MAXN];
 void addedge(int u,int v){
     deg[u]++,e[es].v=v,e[es].n=first[u],first[u]=es++;
 }
 int vis[MAXN],q[MAXN],front,rear;
 void bfs(int s){
     memset(vis,-1,sizeof vis);vis[s]=0;
     q[front=rear=0]=s,rear++;
     while(front<rear){
         int u=q[front++];
         for(int i=first[u];i!=-1;i=e[i].n){
             int v=e[i].v;
             if(vis[v]==-1)vis[v]=vis[u]+1,q[rear++]=v,p[v][s]=u;
             else if(vis[v]==vis[u]+1&&p[v][s]>u)p[v][s]=u;
         }
     }
 }
 double dp(int c1,int c2){
     if(d[c1][c2])return d[c1][c2];
     if(c1==c2)return 0.0;
     if(p[p[c1][c2]][c2]==c2||p[c1][c2]==c2)return 1.0;
     double tmp=dp(p[p[c1][c2]][c2],c2);
     for(int i=first[c2];i!=-1;i=e[i].n)
         tmp+=dp(p[p[c1][c2]][c2],e[i].v);
     return d[c1][c2]=tmp/(deg[c2]+1)+1;
 }
 int main(){
            freopen("1415.in","r",stdin);
    freopen("1415.out","w",stdout);
     while(scanf("%d%d",&n,&m)!=EOF){
         scanf("%d%d",&c1,&c2);
         memset(deg,0,sizeof deg);
         memset(first,-1,sizeof first);es=0;
         for(int i=0;i<m;i++){
             scanf("%d%d",&tu,&tv);
             addedge(tu,tv);
             addedge(tv,tu);
         }
         for(int i=1;i<=n;i++)
             for(int j=1;j<=n;j++)p[i][j]=d[i][j]=0;
         for(int i=1;i<=n;i++)bfs(i);
          for(int i=1;i<=n;i++)
          {
                for(int j=1;j<=n;j++)cout<<p[i][j]<<" ";
                cout<<endl;
            }
         printf("%.3f\n",dp(c1,c2));
     }
     return 0;
 }
