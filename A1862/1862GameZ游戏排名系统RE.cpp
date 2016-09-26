#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
//#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
struct lnode{char word[12];int mk,w;int next;}myl[300001];int pmyl=0;
struct hnode{int first;}myh[3000001];
char antihash[300001][12];int pnum;
inline int enhash(char *tc)
{
    int res=strlen(tc)*29;
    for every(i,0,strlen(tc)-1)
    {
        res=((long long)res*(tc[i]+37)*tc[i]+tc[i]*11)%2999999+1;
    }
    return res;
}
inline bool exist(char *ic)
{
    int tic=enhash(ic);
    for(int p=myh[tic].first;p;p=myl[p].next)
    {
        for(int i=0;ic[i]!=0||myl[p].word[i]!=0;++i)
        {
            if(ic[i]!=myl[p].word[i])goto M_con;
        }
        return true;
        M_con:;
    }
    return false;
}
inline lnode *ask(char *ic)
{
    int tic=enhash(ic);
    for(int p=myh[tic].first;p;p=myl[p].next)
    {
        if(myl[p].next==0)return &myl[p];
        for(int i=0;(ic[i]!=0)||(myl[p].word[i]!=0);++i)
        {
            if(ic[i]!=myl[p].word[i])goto M_con;
        }
        return &myl[p];
        M_con:;
    }
    exit(0);
}
inline void insert(char *ic,int imk,int iw)
{
    int tic=enhash(ic);
    myl[++pmyl].mk=imk;
    for every(i,0,strlen(ic)-1)
    myl[pmyl].word[i]=ic[i];
    myl[pmyl].w=iw;
    myl[pmyl].next=myh[tic].first;
    myh[tic].first=pmyl;
}
//------------------------------------------------------------------------------
struct tnode
{
    //int mk;
    int index;
    int w;
    int fix;
    int size;
    tnode *p,*c[2];
    bool operator <(tnode ano)const
    {
        return (w==ano.w)?index<ano.index:w>ano.w;
    }
    bool operator ==(tnode ano)const
    {
        return index==ano.index;
    }
}*root;
void print(tnode *it,int dp);
inline void update(tnode *tp)
{
    if(!tp)return;
    tp->size=(tp->c[0]?tp->c[0]->size:0)+(tp->c[1]?tp->c[1]->size:0)+1;
}
inline void rotateup(tnode*it)
{
    tnode *tp=it->p;
    bool tl=(it==tp->c[0]);
    if(tp->p)
    {
        bool tl2=(tp->p->c[0]==tp);
        it->p=tp->p;
        it->p->c[!tl2]=it;
    }
    else 
    {
        root=it;
        it->p=0;
    }
    tp->c[!tl]=it->c[tl];
    if(tp->c[!tl])tp->c[!tl]->p=tp;
    it->c[tl]=tp;
    tp->p=it;
    update(tp);
    update(it);
}
void inserttree(tnode*&it,tnode in)
{
    if(!it)
    {
        it=new tnode();
        it->index=in.index;
        it->w=in.w;
        it->size=1;
        it->fix=rand()%1000;
    }
    else
    {
        if(in<(*it))
        {
            inserttree(it->c[0],in);it->c[0]->p=it;
            if(it->fix<it->c[0]->fix)rotateup(it->c[0]);
        }
        else
        {
            inserttree(it->c[1],in);it->c[1]->p=it;
            if(it->fix<it->c[1]->fix)rotateup(it->c[1]);
        }
    }
    update(it);
}
void deletetree(tnode*&it,tnode in)
{
    if(in==(*it))
    {
        if(it->c[0]&&it->c[1])
        {
            if(it->c[0]->fix>it->c[1]->fix)
            {
                rotateup(it->c[0]);
                deletetree(it->c[1],in);
            }
            else
            {
                rotateup(it->c[1]);
                deletetree(it->c[0],in);
            }
        }
        else
        {
            tnode *pt=it;
            if(it->c[0])it=it->c[0];
            else it=it->c[1];
            if(it)it->p=it->p->p;
            delete pt;
        }
    }
    else
    {
        if(in<(*it))
        {
            deletetree(it->c[0],in);
        }
        else
        {
            deletetree(it->c[1],in);
        }
    }
    update(it);
}
int locate(tnode*&it,tnode in,int ibase)
{
    int tvar=(it->c[0]?it->c[0]->size+1:1);
    if(in==(*it))return ibase+tvar;
    else
    if(in<(*it))
    {
        return locate(it->c[0],in,ibase);
    }
    else
    {
        return locate(it->c[1],in,ibase+tvar);
    }
}
tnode *find(tnode *it,int isize)
{
    int ts=(it->c[0]?it->c[0]->size:0);
    if(ts>=isize)return find(it->c[0],isize);
    if(ts+1==isize)return it;
    return find(it->c[1],isize-ts-1);
}/*
inline tnode tt(int iw)
{
    tnode test={};
    test.w=iw;
    return test;
}*/
void print(tnode *it,int dp)
{
    if(!it)return;
    print(it->c[0],dp+1);
    for each(i,dp)cout<<" ";
    cout<<it->w<<":"<<it->fix<<":"<<it->p<<endl;
    print(it->c[1],dp+1);
}
    int tcount=0;
    char tc[100];
    char tname[100];
    tnode pt;
    lnode *tm;
    int tvar;
    int pindex=0;
    int tpts;
    tnode *tget;
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    int n;scanf("%d",&n);
    lnode *tm=0;
    for each(i,n)
    {
        scanf("%s",&tc[0]);
        //for every(j,0,strlen(tc-2))tname[j]=tc[j+1];
        switch(tc[0])
        {
            case '+':
                if(exist(&tc[1]))
                {
                    tm=ask(&tc[1]);
                    pt.index=tm->mk;
                    pt.w=tm->w;
                    //cout<<"delete:"<<tm->mk<<","<<tm->w<<"::";
                    deletetree(root,pt);
                    scanf("%d",&pt.w);
                    tm->mk=++pindex;
                    tm->w=pt.w;
                    pt.index=pindex;
                    memset(antihash[pindex],0,sizeof(antihash[pindex]));
                    strcpy(&antihash[pindex][0],&tc[1]);
                    //cout<<"insert:"<<pt.index<<":"<<pt.w<<endl;
                    inserttree(root,pt);
                }
                else
                {
                    scanf("%d",&pt.w);
                    pt.index=++pindex;
                    insert(&tc[1],pindex,pt.w);
                    memset(antihash[pindex],0,sizeof(antihash[pindex]));
                    strcpy(&antihash[pindex][0],&tc[1]);
                    //cout<<"insert:"<<pt.index<<":"<<pt.w<<endl;
                    inserttree(root,pt);
                    tcount++;
                }
                break;
            case '?':
                tvar=strtol(&tc[1],0,10);
                if(tvar)
                {
                    for every(i,tvar,min(tvar+9,tcount))
                    {
                        //cout<<i<<":"<<find(root,i)->index<<":";
                        cout<<antihash[find(root,i)->index]<<" ";
                    }
                    cout<<endl;
                }
                else
                {
                    tm=ask(&tc[1]);
                    pt.index=tm->mk;
                    pt.w=tm->w;
                    ///tget=locate(root,pt,0);
                    //cout<<pt.index<<","<<pt.w<<","<<",";
                    cout<<locate(root,pt,0)<<endl;
                }
                break;
            default:;
        }
    }
    cout<<pmyl<<endl;
    print(root,0),exit(0);
}
