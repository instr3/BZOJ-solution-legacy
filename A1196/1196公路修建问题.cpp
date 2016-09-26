#include <iostream>
#include <cstdlib>
//#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define enum e_num
struct enode{int fr,to,next,w1,w2;}mye[40002];
struct vnode{int first;}myv[10001];
struct es1node
{
    int enum;
    bool operator <(es1node ano)const
    {
        return mye[enum].w1<mye[ano.enum].w1;
    }
}mys1[40002];

struct es2node
{
    int enum;
    bool operator <(es2node ano)const
    {
        return mye[enum].w2<mye[ano.enum].w2;
    }
}mys2[40002];
int n,nm;
int leader[10001];
int nnum2;
bool visit[10001];
int find(int iv)
{
    if(leader[iv])return leader[iv]=find(leader[iv]);
    return iv;
}
void merge(int iv1,int iv2)
{
    int tp1=find(iv1),tp2=find(iv2);
    //if(tp1==tp2)return;
    leader[tp1]=tp2;
}
inline int task(int ik)
{
    //cout<<"Tasking:"<<ik<<endl;
    memset(visit,false,sizeof visit);
    memset(leader,0,sizeof leader);
    int ie,pf,pt;
    int tot1=0,tot2=0;
    for each(im,nm)
    {
        ie=mys2[im].enum;
        if(mye[ie].w2>ik)break;
        pf=mye[ie].fr;
        pt=mye[ie].to;
        if(find(pf)==find(pt))continue;
        tot2++;
        merge(pf,pt);
    }
    if(tot2<nnum2)
    {
        //cout<<"1st Road !Enough!"<<tot2<<endl;
        return false;
    }
    if(tot1+tot2>=n-1)goto win;
    for each(im,nm)
    {
        ie=mys1[im].enum;
        if(mye[ie].w1>ik)break;
        pf=mye[ie].fr;
        pt=mye[ie].to;
        if(find(pf)==find(pt))continue;
        tot1++;
        if(tot1+tot2>=n-1)goto win;
        merge(pf,pt);
    }
    //cout<<"Tot Road !Enough!"<<tot1<<","<<tot2<<endl;
    return false;
    win:;
    return true;
}
        
int main()
{
    freopen("1196.in","r",stdin);
    freopen("1196.out","w",stdout);
    scanf("%d%d%d",&n,&nnum2,&nm);
    --nm;
    int pf,pt,pw1,pw2;
    for(int i=1,j=1;i<=nm;++i)
    {
        scanf("%d%d%d%d",&pf,&pt,&pw1,&pw2);
        mye[++j].to=pt;
        mye[j].fr=pf;
        mye[j].w1=pw2;
        mye[j].w2=pw1;
        mye[j].next=myv[pf].first;
        myv[pf].first=j;
        mys1[i].enum=j;
        mys2[i].enum=j;
        /*mye[++j].to=pf;
        mye[j].fr=pt;
        mye[j].w1=pw1;
        mye[j].w2=pw2;
        mye[j].next=myv[pt].first;
        myv[pt].first=j;*/
    }
    sort(mys1+1,mys1+nm+1);
    sort(mys2+1,mys2+nm+1);
    int tl=0,tr=300001,tm;
    while(tl+1!=tr)
    {
        tm=(tl+tr)/2;
        if(task(tm))
        {
            tr=tm;
        }
        else
        {
            tl=tm;
        }
    }
    cout<<tr<<endl;
}
