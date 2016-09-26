#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <queue>

using namespace std;
int nday,n,nk,ne,nt;
struct enode{int to,w,next;}mye[500];
struct vnode{int first,mw,fd;}myv[21];
struct dnode{int fr,to,num,next;}dinfo[10000];
//bool isab[21][500][500];
bool isab[21];
long long dp[101];
int isinq[21];
int getroad(int idayf,int idayt)
{
    queue<int> myq;
    memset(isinq,0,sizeof(isinq));
    memset(isab,1,sizeof(isab));
    for(int p=1;p<=nt;++p)
    {
        if(dinfo[p].fr<=idayt&&dinfo[p].to>=idayf)
        {
            isab[dinfo[p].num]=false;
        }
    }
    for(int i=1;i<=n;++i)
     myv[i].mw=99999999;
    myv[1].mw=0;
    myq.push(1);
    isinq[1]=true;
    int tv,tpt;
    while(myq.empty()==false)
    {
        tv=myq.front();myq.pop();
        isinq[tv]=false;
        for(int p=myv[tv].first;p;p=mye[p].next)
        {
            tpt=mye[p].to;
            if(isab[tpt]==false)continue;
            if(myv[tpt].mw>myv[tv].mw+mye[p].w)
            {
                
                myv[tpt].mw=myv[tv].mw+mye[p].w;
                myq.push(tpt);
                isinq[tpt]=true;
            }
        }
    }
    return myv[n].mw;
}
int main()
{
    freopen("1003.in","r",stdin);
    freopen("1003.out","w",stdout);
    memset(isab,1,sizeof(isab));
    scanf("%d%d%d%d",&nday,&n,&nk,&ne);
    int pf,pt,pw;
    for(int i=1,j=0;i<=ne;++i)
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
    int ta,tb;
    scanf("%d",&nt);
    for(int i=1,j=0;i<=nt;++i)
    {
        scanf("%d%d%d",&pf,&ta,&tb);
        dinfo[++j].fr=ta;
        dinfo[j].to=tb;
        dinfo[j].num=pf;
        dinfo[j].next=myv[pf].fd;
        myv[pf].fd=j;
    }
    for(int i=1;i<=nday;++i)
    {
        dp[i]=(long long)getroad(1,i)*i;
        cout<<dp[i]<<endl;
        for(int j=1;j<i;++j)
        {
            dp[i]=min(dp[i],dp[j]+(long long)getroad(j+1,i)*(i-j)+nk);
        }
        //cout<<dp[i]<<endl;
    }
    cout<<dp[nday]<<endl;
}
