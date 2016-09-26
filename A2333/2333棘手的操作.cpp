#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n;
struct tnode
{
    //int w;
    int add;
    int max;
};
int indata[300001];//={0,1,2,3,4,5,6,7,8,9};
struct segtree
{
    private:
    tnode d[1200002];
    int n;
    void printnode(int it,int il,int ir,int idp)
    {
        //tagdown(it,il,ir);
        if(il+1!=ir)printnode((it<<1)+1,(il+ir)>>1,ir,idp+1);
        for each(i,idp)cout<<" ";
        printf("[%d-%d]:%d->%d\n",il,ir,d[it].add,d[it].max);
        if(il+1!=ir)printnode(it<<1,il,(il+ir)>>1,idp+1);
    }
    inline void updatenode(int it,int il,int ir)
    {
        if(il+1==ir)
        {
            d[it].max=d[it].add;return;
            
        }
        d[it].max=max(d[it<<1].max,d[(it<<1)+1].max)+d[it].add;
    }
    inline void tagdown(int it,int il,int ir)
    {
        if(il+1==ir)
        {//return;
            cout<<"Error!"<<endl;
            return;
        }
        d[it<<1].add+=d[it].add;
        d[(it<<1)+1].add+=d[it].add;
        d[it].add=0;
        updatenode(it<<1,il,(il+ir)>>1);
        updatenode((it<<1)+1,(il+ir)>>1,ir);
        updatenode(it,il,ir);
    }
    void changenode(int it,int il,int ir,int ipl,int ipr,int iw)
    {
        if(il>=ipl&&ir<=ipr)
        {
            d[it].add+=iw;
            updatenode(it,il,ir);
            return;
        }
        if(il>=ipr||ir<=ipl)return;
        if(d[it].add)tagdown(it,il,ir);
        changenode(it<<1,il,(il+ir)>>1,ipl,ipr,iw);
        changenode((it<<1)+1,(il+ir)>>1,ir,ipl,ipr,iw);
        updatenode(it,il,ir);
    }
    int asknode(int it,int il,int ir,int ipl,int ipr)
    {
        if(il>=ipl&&ir<=ipr)
        {
            return d[it].max;
        }
        if(il>=ipr||ir<=ipl)return -199999999;
        if(d[it].add)tagdown(it,il,ir);
        return max(asknode(it<<1,il,(il+ir)>>1,ipl,ipr),
         asknode((it<<1)+1,(il+ir)>>1,ir,ipl,ipr));
    }
    void buildnode(int it,int il,int ir)
    {
        if(il+1==ir)
        {
            d[it].add=indata[il];
            updatenode(it,il,ir);
            return;
        }
        buildnode(it<<1,il,(il+ir)>>1);
        buildnode((it<<1)+1,(il+ir)>>1,ir);
        updatenode(it,il,ir);
    }
    public:
    void printtree()
    {
        printnode(1,1,n+1,0);
    }
    void changetree(int ipl,int ipr,int iw)
    {
        changenode(1,1,n+1,ipl,ipr+1,iw);
    }
    int asktree(int ipl,int ipr)
    {
        //cout<<"Asking:"<<ipl<<","<<ipr<<endl;
        return asknode(1,1,n+1,ipl,ipr+1);
    }
    void buildtree(int in)
    {
        n=in;
        buildnode(1,1,n+1);
    }
}myt;
int iop[300001][3];int nop;
int leader1[300001],leader2[300001],tnext[300001],tprev[300001];
int findfather1(int iv)
{
    if(leader1[iv])return leader1[iv]=findfather1(leader1[iv]);
    return iv;
}
void merge1(int iva,int ivb)
{
    int tfa=findfather1(iva),tfb=findfather1(ivb);
    if(tfa==tfb)return;
    leader1[tfa]=tfb;
}
int findfather2(int iv)
{
    if(leader2[iv])return leader2[iv]=findfather2(leader2[iv]);
    return iv;
}
void merge2(int iva,int ivb)
{
    int tfa=findfather2(iva),tfb=findfather2(ivb);
    if(tfa==tfb)return;
    leader2[tfa]=tfb;
}
int tdata[300001];

int tlist[300001];int plist;
int tplace[300001];
void dfs(int iv)
{
    tlist[++plist]=iv;
    tplace[iv]=plist;
    if(tnext[iv])dfs(tnext[iv]);
}
int main()
{
    freopen("2333.in","r",stdin);
    freopen("2333.out","w",stdout);
    scanf("%d",&n);
    /*
    myt.buildtree(9);
    myt.changetree(1,5,10000);
    myt.changetree(3,6,100);
    myt.printtree();
    cout<<myt.asktree(1,9);
    */
    for each(i,n)scanf("%d",&tdata[i]);
    
    char tc[3];
    scanf("%d",&nop);
    int pf,pt;
    for each(i,nop)
    {
        scanf("%s",&tc[0]);
        if(tc[0]=='A')
        {
            iop[i][0]=tc[1]-'0';
            //cout<<"OP:A"<<iop[i][1]<<endl;
            if(tc[1]=='3')
            {
                scanf("%d",&iop[i][1]);
            }
            else
            {
                scanf("%d%d",&iop[i][1],&iop[i][2]);
            }
        }
        else if(tc[0]=='F')
        {
            iop[i][0]=tc[1]-'0'+3;
            if(tc[1]=='3');
            else
            {
                scanf("%d",&iop[i][1]);
            }
        }
        else
        {
            iop[i][0]=0;
            scanf("%d%d",&iop[i][1],&iop[i][2]);
            pf=iop[i][1];pt=iop[i][2];
            if(findfather1(pf)==findfather1(pt))continue;
            //cout<<"U"<<pf<<","<<pt<<endl;
            tnext[findfather1(pf)]=findfather2(pt);
            tprev[findfather2(pt)]=findfather1(pf);
            merge1(pf,pt);
            merge2(pt,pf);
        }
    }
    for each(i,n)
    {
        if(tprev[i]==0)dfs(i);
    }
    for each(i,n)indata[tplace[i]]=tdata[i];
    myt.buildtree(n);
    /*for each(i,n)
    {
        printf("%d ",tlist[i]);
    }*/
    
    memset(leader1,0,sizeof leader1);
    memset(leader2,0,sizeof leader2);
    for each(i,nop)
    {
        //cout<<iop[i][0]<<endl;
        switch(iop[i][0])
        {
            case 0:
                pf=iop[i][1];pt=iop[i][2];
                if(findfather1(pf)==findfather1(pt))continue;
                merge1(pf,pt);
                merge2(pt,pf);
                break;
            case 1:
                myt.changetree(tplace[iop[i][1]],tplace[iop[i][1]],iop[i][2]);
                break;
            case 2:
                myt.changetree(tplace[findfather2(iop[i][1])],tplace[findfather1(iop[i][1])],iop[i][2]);
                break;
            case 3:
                myt.changetree(1,n,iop[i][1]);
                break;
            case 4:
                printf("%d\n",myt.asktree(tplace[iop[i][1]],tplace[iop[i][1]]));
                break;
            case 5:
                printf("%d\n",myt.asktree(tplace[findfather2(iop[i][1])],tplace[findfather1(iop[i][1])]));
                break;
            case 6:
                printf("%d\n",myt.asktree(1,n));
                break;
            default:;
        }
    }     
}
