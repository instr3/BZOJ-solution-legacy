#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
#define trimax(a,b,c) max(a,max(b,c))
#define gs(a) ((a)->r-(a)->l+1)
using namespace std;
int indata[100001];
struct tnode
{
    int l,r;
    int sum1;
    int max0,l0,r0,
        max1,l1,r1;
    int mk;
    tnode *lc,*rc;
}*troot=new tnode();
void getdown(tnode *);
void dealjam(tnode *,int);
void build(tnode *it,int il,int ir)
{
    tnode *tp;
    it->mk=-1;
    if(il==ir)
    {
        if(indata[il])
        {
            it->mk=1;
            it->sum1=it->l1=it->r1=it->max1=1;
        }
        else
        {
            it->l0=it->r0=it->max0=1;
        }
        return;
    }
    tp=new tnode();
    tp->l=il;tp->r=(il+ir)/2;
    build(tp,tp->l,tp->r);
    it->lc=tp;
    tp=new tnode();
    tp->l=(il+ir)/2+1;tp->r=ir;
    build(tp,tp->l,tp->r);
    //cout<<"Building:"<<il<<"->"<<ir<<":"<<tp->sum1<<endl;
    
    it->rc=tp;
    it->sum1=it->lc->sum1+it->rc->sum1;
    it->l1=(it->lc->l1==gs(it->lc))?gs(it->lc)+it->rc->l1:it->lc->l1;
    it->r1=(it->rc->r1==gs(it->rc))?gs(it->rc)+it->lc->r1:it->rc->r1;
    it->max1=trimax(it->lc->max1,it->rc->max1,it->lc->r1+it->rc->l1);
    it->l0=(it->lc->l0==gs(it->lc))?gs(it->lc)+it->rc->l0:it->lc->l0;
    it->r0=(it->rc->r0==gs(it->rc))?gs(it->rc)+it->lc->r0:it->rc->r0;
    it->max0=trimax(it->lc->max0,it->rc->max0,it->lc->r0+it->rc->l0);

}
void mark(tnode *it,int ip,int il,int ir)
{
    if(it->r<il||it->l>ir)return;
    if(it->l>=il&&it->r<=ir)
    {
        dealjam(it,ip);
        //cout<<"Marking:"<<it->l<<"->"<<it->r<<":"<<ip<<endl;
        return;
    }
    if(it->mk!=-1)getdown(it);
    mark(it->lc,ip,il,ir);
    mark(it->rc,ip,il,ir);
    it->sum1=it->lc->sum1+it->rc->sum1;
    it->l1=(it->lc->l1==gs(it->lc))?gs(it->lc)+it->rc->l1:it->lc->l1;
    it->r1=(it->rc->r1==gs(it->rc))?gs(it->rc)+it->lc->r1:it->rc->r1;
    it->max1=trimax(it->lc->max1,it->rc->max1,it->lc->r1+it->rc->l1);
    it->l0=(it->lc->l0==gs(it->lc))?gs(it->lc)+it->rc->l0:it->lc->l0;
    it->r0=(it->rc->r0==gs(it->rc))?gs(it->rc)+it->lc->r0:it->rc->r0;
    it->max0=trimax(it->lc->max0,it->rc->max0,it->lc->r0+it->rc->l0);

}
void getdown(tnode *it)
{
    if(!(it->lc))return;
    int tmk=it->mk;
    dealjam(it->lc,tmk);
    dealjam(it->rc,tmk);
    it->mk=-1;
    it->sum1=it->lc->sum1+it->rc->sum1;
    it->l1=(it->lc->l1==gs(it->lc))?gs(it->lc)+it->rc->l1:it->lc->l1;
    it->r1=(it->rc->r1==gs(it->rc))?gs(it->rc)+it->lc->r1:it->rc->r1;
    it->max1=trimax(it->lc->max1,it->rc->max1,it->lc->r1+it->rc->l1);
    it->l0=(it->lc->l0==gs(it->lc))?gs(it->lc)+it->rc->l0:it->lc->l0;
    it->r0=(it->rc->r0==gs(it->rc))?gs(it->rc)+it->lc->r0:it->rc->r0;
    it->max0=trimax(it->lc->max0,it->rc->max0,it->lc->r0+it->rc->l0);

}
void dealjam(tnode *it,int ip)
{
    if(ip==2)
    {
        if(it->mk==0)
        {
            it->mk=1;
            it->l1=it->r1=it->max1=it->sum1=it->r-it->l+1;
            it->l0=it->r0=it->max0=0;
        }
        else if(it->mk==1)
        {
            it->mk=0;
            it->l1=it->r1=it->max1=it->sum1=0;
            it->l0=it->r0=it->max0=it->r-it->l+1;
        }
        else if(it->mk==2)
        {
            it->mk=-1;
            it->sum1=it->r-it->l+1-it->sum1;
            swap(it->max1,it->max0);
            swap(it->l1,it->l0);
            swap(it->r1,it->r0);
        }
        else
        {
            it->mk=2;
            it->sum1=it->r-it->l+1-it->sum1;
            swap(it->max1,it->max0);
            swap(it->l1,it->l0);
            swap(it->r1,it->r0);
        }
    }
    else
    {
        it->mk=ip;
        if(it->mk==1)
        {
            it->sum1=it->r-it->l+1;
            it->l1=it->r1=it->max1=it->sum1=it->r-it->l+1;
            it->l0=it->r0=it->max0=0;
        }
        else if(it->mk==0)
        {
            it->l1=it->r1=it->max1=it->sum1=0;
            it->l0=it->r0=it->max0=it->r-it->l+1;
        }
        else if(it->mk==2)
        {
            it->sum1=it->r-it->l+1-it->sum1;
            swap(it->max1,it->max0);
            swap(it->l1,it->l0);
            swap(it->r1,it->r0);
        }
    }
}

int quessum(tnode *it,int il,int ir)
{
    if(it->r<il||it->l>ir)return 0;
    if(it->l>=il&&it->r<=ir)
    {
        return it->sum1;
    }
    if(it->mk!=-1)getdown(it);
    return quessum(it->lc,il,ir)+
           quessum(it->rc,il,ir);
}

int quesmax(tnode *it,int il,int ir)
{
    
    if(it->r<il||it->l>ir)return 0;
    if(it->l>=il&&it->r<=ir)
    {
        //cout<<"Question:"<<it->l<<"->"<<it->r<<":"<<it->max1<<endl;
        return it->max1;
    }
    if(it->mk!=-1)getdown(it);
    int res=trimax(quesmax(it->lc,il,ir),
                  quesmax(it->rc,il,ir),
                  min(it->lc->r1,it->lc->r-il+1)+min(it->rc->l1,ir-it->rc->l+1));
    //cout<<"Question:"<<it->l<<"->"<<it->r<<":"<<res<<","<<min(it->lc->r1,it->lc->r-il+1)+min(it->rc->l1,ir-it->rc->l+1)<<endl;
        
    return res;
}


void printtree(tnode *it,int dw)
{
    cout<<it->l<<"->"<<it->r<<":"<<it->l1<<","<<it->r1<<endl;
    if(dw==-1)
    {
        if(it->mk==1)dw=1;
        if(it->mk==0)dw=0;
        if(it->mk==2)dw=2;
    }
    else if(dw==2)
    {
        if(it->mk==1)dw=0;
        if(it->mk==0)dw=1;
        if(it->mk==2)dw=-1;
    }
    if(it->r==it->l)
    {
        if(dw==2)dw=1;
        cout<<"Print["<<it->l<<"]:"<<(dw==-1?0:dw)<<endl;
        
        return;
    }
    printtree(it->lc,dw);
    printtree(it->rc,dw);
}
int main()
{
    freopen("1858.in","r",stdin);
    freopen("1858.out","w",stdout);
    int n,nm;
    scanf("%d%d",&n,&nm);
    
    int tip,ta,tb;
    for(int i=0;i<n;++i)
    {
        scanf("%d",&indata[i]);
    }
    troot->r=n-1;
    build(troot,0,n-1);
    for(int iq=1;iq<=nm;++iq)
    {
        scanf("%d%d%d",&tip,&ta,&tb);
        if(tip<=2)mark(troot,tip,ta,tb);
        else if(tip==3)
        {
                    //printf("Data---\n");
        //printtree(troot,-1);
            printf("%d\n",quessum(troot,ta,tb));
            //printf("Question_sum1(%d->%d):%d\n",ta,tb,quessum(troot,ta,tb));
        }
        else if(tip==4)
        {
                    //printf("Data---\n");
        //printtree(troot,-1);
            printf("%d\n",quesmax(troot,ta,tb));
            //printf("Question_max1(%d->%d):%d\n",ta,tb,quesmax(troot,ta,tb));
        }
        //printf("Data---\n");
        //printtree(troot,-1);
    }
    
}
