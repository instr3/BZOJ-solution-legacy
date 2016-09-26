#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define double long double
struct enode{int to,next;}mye[2002];
struct vnode{int first;}myv[1001];
bool map[1001][1001];
int n,nm;
bool isdp[1001][1001];
double tdp[1001][1001];
int tgoto[1001][1001];
int ist1,ist2;
inline double getdp(int it1,int it2)
{
    
    if(it1==it2)return 0;
    
    if(isdp[it1][it2])return tdp[it1][it2];
    
    int tto=tgoto[tgoto[it1][it2]][it2];
    if(tto==it2)
    {
        isdp[it1][it2]=true;
        //cout<<"Getting:"<<it1<<","<<it2<<":"<<1<<endl;
        return tdp[it1][it2]=1;
        
    }
    int pt;
    double res=0;int tcount=1;
    for(int p=myv[it2].first;p;p=mye[p].next)
    {
        
        ++tcount;
        pt=mye[p].to;
        res+=getdp(tto,pt);
    }
    res+=getdp(tto,it2);
    //if(it1==6&&it2==36)cout<<tto<<endl;
    res/=tcount;
    isdp[it1][it2]=true;
    //cout<<"Getting:"<<it1<<","<<it2<<":"<<res<<endl;
    return tdp[it1][it2]=res+1.0l;
    

}

queue<int> myq;
bool visit[1001];
int tpar[1001];
int dist[1001];
inline void bfs(int iv)
{
    //memset(tpar,0,sizeof tpar);
    memset(visit,0,sizeof visit);
    memset(dist,37,sizeof dist);
    myq.push(iv);
    tpar[iv]=-1;
    dist[iv]=0;
    tgoto[iv][iv]=iv;
    visit[iv]=true;
    int tv,pt;
    while(!myq.empty())
    {
        tv=myq.front();
        myq.pop();
        for(int p=myv[tv].first;p;p=mye[p].next)
        {
            pt=mye[p].to;
            if(!visit[pt])
            {
                myq.push(pt);
                tpar[pt]=tv;
                dist[pt]=dist[tv]+1;
                tgoto[pt][iv]=tv;
                visit[pt]=true;
            }
            else if(dist[pt]==dist[tv]+1&&tpar[pt]>tv)
            {
                tpar[pt]=tv;
                tgoto[pt][iv]=tv;
            }
        }
    }
}
        
int main()
{
    freopen("1415.in","r",stdin);
    freopen("1415.out","w",stdout);
    scanf("%d%d",&n,&nm);
    scanf("%d%d",&ist1,&ist2);
    int pf,pt;
    for(int i=1;i<=nm;++i)
    {
        scanf("%d%d",&pf,&pt);
        map[pf][pt]=map[pt][pf]=true;
    }
    
    for(int pf=1,j=1;pf<=n;++pf)
    {
        for(int pt=n;pt>=1;--pt)
        {
            if(map[pf][pt]==true)
            {
                //cout<<"ADD:"<<pf<<","<<pt<<endl;
                mye[++j].to=pt;
                mye[j].next=myv[pf].first;myv[pf].first=j;
            }
        }
    }
    for each(i,n)
    {
        bfs(i);
    }
    /*for each(i,n)
    {
        for each(j,n)
        {
            cout<<tgoto[i][j]<<" ";
        }
        cout<<endl;
    }*/
    printf("%.3f",(float)(getdp(ist1,ist2)));
}
