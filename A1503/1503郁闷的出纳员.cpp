#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
struct tnode
{
    tnode /**par,*/*lc,*rc;
    int pos,w,ran,ct;
} *troot=new tnode();
void treeinsert(tnode *&ip,int pos,int w);
//int indata[100];
//int inran[100];
int wbase;
int n,nmin;
int tot;
inline void getw(tnode *&tn)
{
    if(tn) 
    tn->ct=(tn->lc?tn->lc->ct:0)+(tn->rc?tn->rc->ct:0)+1;
}
inline void leftrotate(tnode *&tn)
{
    tnode *tt=tn->rc;
    tn->rc=tt->lc;
    //tn->par=tt;
    getw(tn);
    tt->lc=tn;
    //tt->par=tn->par;
    tn=tt;
    getw(tt);
}
inline void rightrotate(tnode *&tn)
{
    tnode *tt=tn->lc;
    tn->lc=tt->rc;
    //tn->par=tt;
    getw(tn);
    tt->rc=tn;
    //tt->par=tn->par;
    tn=tt;
    getw(tn);
    
}
/*
void treebuild(int ls)
{
    troot->pos=1;
    troot->w=indata[1];
    troot->ran=inran[troot->pos];
    for(int i=2;i<=ls;++i)
    {
        treeinsert(troot,i,indata[i]);
    }
}*/
void treeinsert(tnode *&ip,int pos,int w)
{
    if((!ip)||(ip==troot&&troot->ct==0))
    {
        ip=new tnode();
        ip->pos=pos;
        ip->w=w;
        //ip->par=__NEED_INPUT__;
        ip->ran=rand();
        //ip->ran=inran[ip->pos];
        ip->ct=1;
        return;
    }
    if(w>ip->w)
    {
        treeinsert(ip->rc,pos,w);
        if(ip->ran > ip->rc->ran)
        {
            leftrotate(ip);
        }
    }
    else
    {
        treeinsert(ip->lc,pos,w);
        if(ip->ran > ip->lc->ran)
        {
            rightrotate(ip);
        }
    }
    getw(ip);
}
void print(tnode *ip,int dp)
{
    if(!ip)return;
    if(ip->lc)print(ip->lc,dp+1);
    //for(int i=1;i<=dp;++i)cout<<" ";
    //printf("[%d]:%d\n",ip->pos,ip->w);
    tot--;
    //printf("[%d]:%d(%d)\n",ip->ran,ip->w+wbase,ip->ct);
    if(ip->rc)print(ip->rc,dp+1);
}
int treeask(tnode *ip,int tct)
{
    if(!ip)return -1;
    int tcr=ip->rc?ip->rc->ct:0;
    if(tcr>=tct)return treeask(ip->rc,tct);
    else if(tcr+1==tct)return ip->w+wbase;
    else return treeask(ip->lc,tct-tcr-1);
}
void treedel(tnode *&ip,int tw)
{
    
    if(ip->w+wbase>=tw)
    {
        if(ip->lc)
        treedel(ip->lc,tw);
        getw(ip);
    }
    else
    {
        ip=ip->rc;
        if(ip)
        {
            treedel(ip,tw);
            getw(ip);
        }
    }
}

int main()
{
    freopen("1503.in","r",stdin);
    freopen("1503.out","w",stdout);
    //int myarr[11]={0,5,31,111,456,34,61,2,9999,711,15};
    //int n=10;
    scanf("%d%d",&n,&nmin);
    int tw;
    char tc[2];
    for(int i=1;i<=n;++i)
    {
        scanf("%s%d",&tc[0],&tw);
        switch(tc[0])
        {
            case 'I':
                
                if(tw>=nmin)
                {
                tot++;
                treeinsert(troot,0,tw-wbase);}break;
            case 'A':wbase+=tw;break;
            case 'S':
                wbase-=tw;
                treedel(troot,nmin);
                break;
            case 'F':
                
                //print(troot,0);
                //cout<<"Find Biggest "<<tw<<":"<<treeask(troot,tw)<<endl;
                printf("%d\n",treeask(troot,tw));
                break;
        }
        
        //scanf("%d%d",&indata[i],&inran[i]);
        //indata[i]=myarr[i];
    }
    print(troot,0);
    cout<<tot<<endl;
    //treebuild(n);
    //print(troot,0);
    //leftrotate(troot);
    //print(troot,0);
}
