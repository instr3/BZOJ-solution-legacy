#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#define rep(i,n) for(int i=0;i<n;i++)
#define pb push_back
const int inf=~0U>>1,maxn=100000;
using namespace std;
#define Tree int t,int l,int r
#define Left t*2,l,l+r>>1
#define Right t*2+1,l+r>>1,r
int n,m;
struct sinfo
{
    int sum,maxl,maxr,maxs,size;
    void set(bool x){sum=maxl=maxr=maxs=x?size:0;}
    sinfo():size(1){}
    bool full()const{return sum==size;}
};
sinfo operator+(const sinfo&L,const sinfo&R)
{
    sinfo F;
    F.size=L.size+R.size;
    F.sum=L.sum+R.sum;
    F.maxl=L.full()?L.sum+R.maxl:L.maxl;
    F.maxr=R.full()?R.sum+L.maxr:R.maxr;
    F.maxs=max(L.maxr+R.maxl,max(L.maxs,R.maxs));
    return F;
}
struct info
{
    sinfo I[2];
    bool e;
    info(bool _e=true):e(_e){}
    void set(bool c){rep(i,2)I[i].set(i==c);}
}T[maxn*4];
info operator+(const info&L,const info&R)
{
    if(!L.e)return R;if(!R.e)return L;
    info F;rep(i,2)F.I[i]=L.I[i]+R.I[i];
    return F;
}
int A[maxn],M[maxn*4]={};
void Mark(int t,int m)
{
    if(m==3){swap(T[t].I[0],T[t].I[1]);M[t]=3-M[t];}
    else{T[t].set(m-1);M[t]=m;}
}
void PushDown(int t)
{
    if(M[t])Mark(t*2,M[t]),Mark(t*2+1,M[t]),M[t]=0;
}
void Build(Tree)
{
    if(l+1==r){T[t].set(A[l]);return;}
    Build(Left);Build(Right);
    T[t]=T[t*2]+T[t*2+1];
}
info Ask(Tree,int a,int b)
{
    if(a>=r||b<=l)return info(false);
    if(l>=a&&r<=b)return T[t];
    PushDown(t);
    return Ask(Left,a,b)+Ask(Right,a,b);
}
void Change(Tree,int a,int b,int m)
{
    if(a>=r||b<=l)return;
    if(l>=a&&r<=b){Mark(t,m);return;}
    PushDown(t);
    Change(Left,a,b,m);Change(Right,a,b,m);
    T[t]=T[t*2]+T[t*2+1];
}
#define root 1,0,n
int main()
{
    scanf("%d%d",&n,&m);rep(i,n)scanf("%d",A+i);
    Build(root);int k,l,r;
    while(m--)
    {
        scanf("%d%d%d",&k,&l,&r);r++;
        switch(k)
        {
            case 0:Change(root,l,r,1);break;
            case 1:Change(root,l,r,2);break;
            case 2:Change(root,l,r,3);break;
            case 3:printf("%d\n",Ask(root,l,r).I[1].sum);break;
            case 4:printf("%d\n",Ask(root,l,r).I[1].maxs);break;
        }
    }
}



