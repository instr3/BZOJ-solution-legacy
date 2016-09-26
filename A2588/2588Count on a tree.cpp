#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <set> 
#include <map>
using namespace std;
struct tnode
{
    int l,r;
    int sum;
    tnode *lc,*rc;//*par;
    //tnode *bk;
};
int n,nm;
struct enode{int to,next;}mye[200001];

struct vnode{int first,w;tnode *rt;int dp;}myv[100001];

int inw[100001];

int fa[100001][20];
set<int> myset;
map<int,int> mymap;
int redc[100001];

//tnode *tleaf[100001];
//tnode *tsleaf[100001];
//tnode *tsp,*tnp;
/*int mempool[300000000];
void testpool()
{
    cout<<"Memory Test:"<<endl;
    for(int i=0;i<300000000;++i)
    {
        if(mempool[i]!=0&&mempool[i]!=19960322)
        {
            cout<<"Memory Not Allowed @ "<<mempool+i<<endl;
            return;
        }
        mempool[i]=19960322;
    }
    cout<<"Memory Ok"<<endl;
    return;
}*/
void buildtree(tnode *&it,int il,int ir)
{
    it=new tnode();
    it->l=il,it->r=ir;
    if(il+1==ir)
    {
        if(myv[1].w==il)it->sum++;
        //tleaf[il]=it;
        return;
    }
    buildtree(it->lc,il,(il+ir)/2);
    buildtree(it->rc,(il+ir)/2,ir);
    it->sum=it->lc->sum+it->rc->sum;
    //printf("Tnode[%d,%d]:%d\n",il,ir,it->sum);
}
bool visit[100001];
tnode *modifytree(tnode *&it,tnode *tst,int il,int ir,int iw)
{
    tnode *tt;
    if(il>iw||ir<=iw)return 0;
    it=new tnode(*tst);
    if(il+1==ir)
    {
        if(iw==il)it->sum++;
        //printf("%d's new point:[%d,%d),",0,it->l,it->r);
        //printf("which sum is %d\n",it->sum);
        return it;
    }
    if(tt=modifytree(it->lc,tst->lc,il,(il+ir)/2,iw))
    {
        it->lc=tt;
    }
    if(tt=modifytree(it->rc,tst->rc,(il+ir)/2,ir,iw))
    {
        it->rc=tt;
    }
    it->sum=it->lc->sum+it->rc->sum;
    //printf("%d's new point:[%d,%d),",0,it->l,it->r);
    //printf("which sum is %d\n",it->sum);
    return it;
}
void dfs(int iv,int dp)
{
    visit[iv]=true;
    int tv;//tnode *tsl;bool ttvar=false;
    for(int p=myv[iv].first;p;p=mye[p].next)
    {
        tv=mye[p].to;
        if(!visit[tv])
        {
            //myv[tv].par=iv;
            fa[tv][0]=iv;
            myv[tv].dp=dp+1;
            //printf("new v(%d):%d\n",tv,myv[tv].w);
            //tsl=tleaf[myv[tv].w];
            myv[tv].rt=modifytree(myv[tv].rt,myv[iv].rt,1,n+1,myv[tv].w);
            /*for(tnode *tp=tleaf[myv[tv].w];tp->par;tp=tp->par)
            {
                tnp=new tnode(*tp);
                if(!ttvar)tleaf[myv[tv].w]=tnp;
                if(tp->lc!=tsp)tnp->lc=tp->lc;else tnp->lc=tsp;
                if(tp->rc!=tsp)tnp->rc=tp->rc;else tnp->rc=tsp;
                tsp=tp;
                printf("%d's new point:[%d,%d]\n",tv,tnp->l,tnp->r);
            }*/
            dfs(tv,dp+1);
            /*for(tnode *tp=tleaf[myv[tv].w];tp->par;tp=tp->par)
            {
                
            tleaf[myv[tv].w]=tsl;*/
        }
    }
}

void getup(int &iv,int dp)
{
    int tli=(int)log2(dp)+1;
    for(int i=0;i<=tli;++i)
    {
        if(dp&(1<<i))iv=fa[iv][i];
    }
}
#define gs(it) (it?(it->lc?it->lc->sum:0):0)
int findans(tnode *t1,tnode *t2,tnode *t3,tnode *t4,int k)
{
    if(!t1)return 0;
    if((!(t1->lc)))return redc[t1->l];
    int tfs=gs(t1)+gs(t2)-gs(t3)-gs(t4);
    if(tfs>=k)return findans(t1->lc,t2->lc,t3?(t3->lc):0,t4?(t4->lc):0,k);
    return(findans(t1->rc,t2->rc,t3?(t3->rc):0,t4?(t4->rc):0,k-tfs));
}
int main()
{
    freopen("2588.in","r",stdin);
    freopen("2588.out","w",stdout);
    
    int pf,pt;
    scanf("%d%d",&n,&nm);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&inw[i]);
        myset.insert(inw[i]);
    }
    int tn=0;
    for(set<int>::iterator p=myset.begin();p!=myset.end();p++)
    {
        tn++;
        mymap[*p]=tn;
        redc[tn]=*p;
        
    }
    --tn;
    for(int i=1;i<=n;++i)
    {
        myv[i].w=mymap[inw[i]];
        //cout<<myv[i].w<<endl;
    }
    for(int i=1,j=0;i<n;++i)
    {
        scanf("%d%d",&pf,&pt);
        mye[++j].to=pt;
        mye[j].next=myv[pf].first;
        myv[pf].first=j;
        mye[++j].to=pf;
        mye[j].next=myv[pt].first;
        myv[pt].first=j;
    }
    buildtree(myv[1].rt,1,n+1);
    
    dfs(1,0);
    for(int k=1;k<=19;++k)
    {
        for(int i=1;i<=n;++i)
        {
            fa[i][k]=fa[fa[i][k-1]][k-1];
        }
    }
    int pk,sbpf,lastans=0;
    int ptf,ptt,pz;
    for(int i=1;i<nm;++i)
    {
        scanf("%d%d%d",&sbpf,&pt,&pk);
        pf=lastans^sbpf;
        //pf=sbpf;
        ptf=pf;ptt=pt;
        
        if(myv[ptf].dp<myv[ptt].dp)swap(ptf,ptt);
        getup(ptf,myv[ptf].dp-myv[ptt].dp);
        for(int k=(int)log2(myv[ptf].dp)+1;k>=0;k--)
        {
            if(fa[ptf][k]!=fa[ptt][k])
            {
                //getup(ptf,k);getup(ptt,k);
                ptf=fa[ptf][k];
                ptt=fa[ptt][k];
            }
        }
        pz=ptf==ptt?ptf:fa[ptf][0];
        //printf("LCA of %d,%d is %d\n",pf,pt,pz);
        if(fa[pz][0])
        printf("%d\n",lastans=findans(myv[pf].rt,myv[pt].rt,myv[fa[pz][0]].rt,myv[pz].rt,pk));
        else
        printf("%d\n",lastans=findans(myv[pf].rt,myv[pt].rt,0,myv[pz].rt,pk));
    }
    scanf("%d%d%d",&sbpf,&pt,&pk);
    pf=lastans^sbpf;
    //pf=sbpf;
    ptf=pf;ptt=pt;
    
    if(myv[ptf].dp<myv[ptt].dp)swap(ptf,ptt);
    getup(ptf,myv[ptf].dp-myv[ptt].dp);
    for(int k=(int)log2(myv[ptf].dp)+1;k>=0;k--)
    {
        if(fa[ptf][k]!=fa[ptt][k])
        {
            //getup(ptf,k);getup(ptt,k);
            ptf=fa[ptf][k];
            ptt=fa[ptt][k];
        }
    }
    pz=ptf==ptt?ptf:fa[ptf][0];
    //printf("LCA of %d,%d is %d\n",pf,pt,pz);
    if(fa[pz][0])
    printf("%d",lastans=findans(myv[pf].rt,myv[pt].rt,myv[fa[pz][0]].rt,myv[pz].rt,pk));
    else
    printf("%d",lastans=findans(myv[pf].rt,myv[pt].rt,0,myv[pz].rt,pk));
    //此处防止PE将最后一次循环单独输出 
    return 0;
    //testpool();
}
