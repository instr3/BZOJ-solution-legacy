#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int inx[50001],iny[50001];
long long dp[50001];
int minat[50001];
int n;
struct segtree
{
    struct tnode
    {
        int tmax;
    }t[100001];
    int asknode(int it,int il,int ir,int pl,int pr)
    {
        if(il>=pl&&ir<=pr)return t[it].tmax;
        if(il>=pr||ir<=pl)return 0;
        return max(
         asknode(it<<1,il,((il+ir)>>1),pl,pr),
          asknode((it<<1)+1,((il+ir)>>1),ir,pl,pr));
    }
    void buildnode(int it,int il,int ir,int *idata)
    {
        //if(il>=ir)return;
        if(il+1==ir)
        {
            t[it].tmax=idata[il];
            return;
        }
        buildnode(it<<1,il,((il+ir)>>1),idata);
        buildnode((it<<1)+1,((il+ir)>>1),ir,idata);
        t[it].tmax=max(t[it<<1].tmax,t[(it<<1)+1].tmax);
    }
    inline int asktree(int pl,int pr)
    {
        return asknode(1,1,n+1,pl,pr+1);
    }
    inline void buildtree(int *idata)
    {
        buildnode(1,1,n+1,idata);
    }
}mytx,myty;
//#define getw(i,j) (mytx.asktree(i,j)*(long long)myty.asktree(i,j))
//dp[i]=min(dp[j]+w[j+1][i])
inline long long getw(int il,int ir)
{
    int maxx=0,maxy=0;
    for every(i,il,ir)
    {
        maxx=max(maxx,inx[i]);
        maxy=max(maxy,iny[i]);
    }
    return maxx*(long long)maxy;
}
    
int main()
{
    freopen("1597.in","r",stdin);
    freopen("1597.out","w",stdout);
    scanf("%d",&n);
    for each(i,n)scanf("%d%d",&inx[i],&iny[i]);
    mytx.buildtree(inx);
    myty.buildtree(iny);
    memset(dp,38,sizeof dp);
    dp[0]=0;
    for each(i,n)
    {
        for every(j,0,i-1)
        {
            if(dp[i]>=dp[j]+getw(j+1,i))
            {
                dp[i]=dp[j]+getw(j+1,i);
                minat[i]=j;
            }
            cout<<minat[i]<<" ";
        }
        cout<<endl;
    }
    for each(i,n)
    {
        cout<<minat[i]<<endl;
    }
    cout<<dp[n]<<endl;
}
