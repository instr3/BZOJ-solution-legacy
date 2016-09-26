#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
struct enode{int to,next;}mye[20001];
struct vnode{int first;}myv[10001];
int n,nf;
int icolor[10001];
int streedp[10001][3];
/*2:上面是空的 
  1:上面搞了白的
  0:上面搞了黑的 */
int treedp(int iv,int ic,int ipar)
{
    if(streedp[iv][ic]!=-1)return streedp[iv][ic];
    if(iv<=nf)
    {
        if(ic==icolor[iv])return streedp[iv][ic]=0;else return streedp[iv][ic]=1;
    }
    int pt;
    int res1=0,res2=1,res3=1;
    for(int p=myv[iv].first;p;p=mye[p].next)
    {
        pt=mye[p].to;
        if(pt==ipar)continue;
        res1+=treedp(pt,ic,iv);
        res2+=treedp(pt,1,iv);
        res3+=treedp(pt,0,iv);
    }
    int res=min(min(res1,res2),res3);
    //cout<<"Dp:"<<iv<<","<<ic<<","<<ipar<<":"<<res1<<res2<<res3<<endl;
    return streedp[iv][ic]=res;
}
int main()
{
    memset(streedp,-1,sizeof(streedp));
    scanf("%d%d",&n,&nf);
    for each(i,nf)scanf("%d",&icolor[i]);
    int pf,pt;
    for(int i=1,j=1;i<=n-1;++i)
    {
        scanf("%d%d",&pf,&pt);
        mye[++j].to=pt;
        mye[j].next=myv[pf].first;
        myv[pf].first=j;
        mye[++j].to=pf;
        mye[j].next=myv[pt].first;
        myv[pt].first=j;
    }
    cout<<treedp(n,2,-1);
    system("pause");
}
