#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define each(i,n) (int i=1;i<=(n);++i)
using namespace std;
int n,nm;
struct enode{int to,fr,next;}mye[50001],mye1[50001];
struct vnode{int first,ind,res;}myv[10001],myv1[10001];
int visit[10001];
int myq[10001],pfr=1,pbk;
int dnf[10001],pdnf,inc[10001],mys[10001],pmys;
bool instk[10001];
int tnp[10001],ptnp;
int tcount;
void tarjan(int iv)
{
    int pt;
    dnf[iv]=inc[iv]=++pdnf;
    mys[++pmys]=iv;
    instk[iv]=true;
    visit[iv]=true;
    for(int p=myv[iv].first;p;p=mye[p].next)
    {
        pt=mye[p].to;
        if(!visit[pt])
        {
            tarjan(pt);
            inc[iv]=min(inc[iv],inc[pt]);
        }
        else if(instk[pt])
        {
            inc[iv]=min(inc[iv],dnf[pt]);
        }
    }
    if(dnf[iv]==inc[iv])
    {
        ptnp++;
        //cout<<"Find"<<ptnp<<":";
        tcount=0;
        while(mys[pmys]!=iv)
        {
            instk[mys[pmys]]=false;
            tnp[mys[pmys--]]=ptnp;
            tcount++;
            //cout<<mys[pmys+1]<<" ";
        }

        instk[mys[pmys]]=false;
        tnp[mys[pmys--]]=ptnp;
        myv1[ptnp].res=tcount;
        //cout<<mys[pmys+1]<<" "<<tcount;
        //cout<<endl;
    }
}
int main()
{
    freopen("1051.in","r",stdin);
    freopen("1051.out","w",stdout);
    scanf("%d%d",&n,&nm);
    int pf,pt;
    for(int i=1,j=0;i<=nm;++i)
    {
        scanf("%d%d",&pf,&pt);
        mye[++j].to=pt;
        mye[j].fr=pf;
        mye[j].next=myv[pf].first;
        myv[pf].first=j;
        myv[pt].ind++;
    }
    for each(i,n)
    {
        if(!visit[i])tarjan(i);
    }
    //return 0;
    for(int j=1;j<=nm;++j)
    {
        pf=tnp[mye[j].fr];
        pt=tnp[mye[j].to];
        if(pf==pt)continue;
        //cout<<"New Edge:"<<pf<<"->"<<pt<<endl;
        mye1[j].to=pt;
        mye1[j].next=myv1[pf].first;
        myv1[pf].first=j;
        myv1[pt].ind++;
    }
    for each(i,ptnp)
    {
        if(myv1[i].ind==0)
        {
            myq[++pbk]=i;
        }
    }

    while(pbk>=pfr)
    {
        pf=myq[pfr++];
        memset(visit,0,sizeof(visit));
        for(int p=myv1[pf].first;p;p=mye1[p].next)
        {
            pt=mye1[p].to;
            if(!visit[pt])
            {
                visit[pt]=true;
                myv1[pt].ind--;
                if(myv1[pt].ind==0)myq[++pbk]=pt;
                myv1[pt].res+=myv1[pf].res+1;
            }
        }
    }
    int maxn=n-1,tot=0;
    for each(i,n)
    {
        //cout<<myv1[tnp[i]].res<<endl;
        if(myv1[tnp[i]].res>maxn)
        {
            maxn=myv1[tnp[i]].res;tot=1;
        }
        else if(myv1[tnp[i]].res==maxn)
        {
            ++tot;
        }
    }
    printf("%d",tot);
}
