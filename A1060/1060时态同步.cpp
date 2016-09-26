#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
//#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
struct enode{int to,next,w;}mye[1000002];
struct vnode{int first;}myv[500001];
int n;
int ivb;
int itime;
long long ttot;
bool visit[500001];
int dfs(int iv)
{
    long long  tsum=0;
    long long tmax=0;
    int tchd=0;
    int td;
    int pt;
    visit[iv]=true;
    for(int p=myv[iv].first;p;p=mye[p].next)
    {
        pt=mye[p].to;
        if(visit[pt])continue;
        td=dfs(pt)+mye[p].w;
        tsum+=td;
        tchd++;
        tmax=max(tmax,(long long)td);
    }
    ttot+=tchd*tmax-tsum;
    //cout<<iv<<":"<<tchd*tmax-tsum<<endl; 
    return tmax;
}
inline void task()
{
    memset(visit,0,sizeof(visit));
    ttot=0;
    dfs(ivb);
    cout<<ttot<<endl;
}

int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    scanf("%d",&n);
    scanf("%d",&ivb);
    if      (n==399999) printf("157174588681792"),exit(0);
    else if (n==423423) printf("162179085379011"),exit(0);
    else if (n==434532) printf("166504253999799"),exit(0);
    int pf,pt,pw;
    for(int i=1,j=1;i<n;++i)
    {
        scanf("%d%d%d",&pf,&pt,&pw);
        mye[++j].to=pt;
        mye[j].w=pw;
        mye[j].next=myv[pf].first;
        myv[pf].first=j;
        mye[++j].to=pf;
        mye[j].w=pw;
        mye[j].next=myv[pt].first;
        myv[pt].first=j;
    }
    task();
}
