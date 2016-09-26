//Warning:I64d I/O
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
//#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
#define troot (mytp.root)
#define myabs(a) ((a)<0?-(a):(a))
int n;
struct tnode
{
    int fix;
    long long w;
    tnode *c[2];
};
struct treap
{
    tnode *root;
    void rotate(tnode *&it,bool dir) //0×óº¢1ÓÒº¢ 
    {
        tnode *tc=it->c[dir];
        it->c[dir]=tc->c[!dir];
        tc->c[!dir]=it;
        it=tc;
    }
    void inserttree(tnode *&it,long long iw)
    {
        if(!it)
        {
            it=new tnode();
            it->w=iw;
            it->fix=rand()%1000;
        }
        else
        {
            if(iw<it->w)
            {
                inserttree(it->c[0],iw);
                if(it->c[0]->fix>it->fix)rotate(it,0);
            }
            else
            {
                inserttree(it->c[1],iw);
                if(it->c[1]->fix>it->fix)rotate(it,1);
            }
        }
    }
    void deletetree(tnode *&it,long long iw)
    {
        tnode *tdel;
        if(it->w==iw)
        {
            if(!(it->c[0]&&it->c[1]))
            {
                tdel=it;
                if(it->c[0])it=it->c[0];else it=it->c[1];
                delete it;
            }
            else
            {
                if(it->c[0]->fix>it->c[1]->fix)
                {
                    rotate(it,0);
                    deletetree(it,iw);
                }
                else
                {
                    rotate(it,1);
                    deletetree(it,iw);
                }
            }
        }
        else
        {
            if(iw<it->w)deletetree(it->c[0],iw);
            else deletetree(it->c[1],iw);
        }
    }
    tnode *findtree(tnode *it,long long iw)
    {
        if(!it)return it;
        if(it->w==iw)
        {
            return it;
        }
        else
        {
            if(iw<it->w)return findtree(it->c[0],iw);
            else return findtree(it->c[1],iw);
        }
    }
    long long tless,tmore;
    inline long long getless(long long iw)
    {
        tless=-999999999999LL;
        findless(root,iw);
        return tless;
    }
    inline long long getmore(long long iw)
    {
        tmore=999999999999LL;
        findmore(root,iw);
        return tmore;
    }
    void findless(tnode *it,long long iw)
    {
        if(!it)return;
        //cout<<"Finding:"<<it->w<<endl;
        if(it->w<iw)tless=max(tless,it->w);
        if(iw<=it->w)findless(it->c[0],iw);
        else findless(it->c[1],iw);
    }
    void findmore(tnode *it,long long iw)
    {
        if(!it)return;
        //cout<<"Finding:"<<it->w<<endl;
        if(it->w>iw)tmore=min(tmore,it->w);
        if(iw>=it->w)findmore(it->c[1],iw);
        else findmore(it->c[0],iw);
    }
    void print(tnode *it,int idp)
    {
        if(!it)return;
        print(it->c[0],idp+1);
        for each(i,idp)cout<<" ";
        cout<<"["<<it->w<<"]"<<it->fix<<endl;
        print(it->c[1],idp+1);
    }
}mytp;
long long indata[500001];
long long tldata[500001];
struct snode
{
    long long minw;
};
struct segtree
{
    snode s[1000001];
    void buildtree(int it,int il,int ir)
    {
        if(il+1==ir)
        {
            s[it].minw=myabs(indata[il+1]-tldata[il]);
            return;
        }
        buildtree(it<<1,il,(il+ir)>>1);
        buildtree((it<<1)+1,(il+ir)>>1,ir);
        s[it].minw=min(s[it<<1].minw,s[(it<<1)+1].minw);
    }
    void change(int it,int il,int ir,int ipos,long long iw)
    {
        if(il>ipos or ir<=ipos)return ;
        if(il+1==ir)
        {
            s[it].minw=iw;
            return;
        }
        change(it<<1,il,(il+ir)>>1,ipos,iw);
        change((it<<1)+1,(il+ir)>>1,ir,ipos,iw);
        s[it].minw=min(s[it<<1].minw,s[(it<<1)+1].minw);
    }
}mys;
long long tsdata[500001];
long long tsmg=999999999999LL,tsm=999999999999LL;
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    int nm;scanf("%d%d",&n,&nm);
    for each(i,n)
    {
        scanf("%I64d",&indata[i]);
        tsdata[i]=indata[i];
        tldata[i]=indata[i];
        mytp.inserttree(troot,indata[i]);
    }
    sort(tsdata+1,tsdata+n+1);
    for each(i,n-1)
    {
        tsmg=min(tsmg,myabs(tsdata[i]-tsdata[i+1]));
    }
    mys.buildtree(1,1,n);//1~n-1
    char tc[100];
    int tpos;long long tw;
    for each(j,nm)
    {
        scanf("%s",&tc[0]);
        if(tc[0]=='I')
        {
            scanf("%d%I64d",&tpos,&tw);
            if(mytp.findtree(troot,tw)){tsmg=0;}
            if(tsm)tsm=min(tsm,myabs(tw-tldata[tpos]));
            tldata[tpos]=tw;
            if(tpos<n)mys.change(1,1,n,tpos,myabs(indata[tpos+1]-tldata[tpos]));
            //tsm=min(tsm,mys.s[1].minw);
            mytp.inserttree(troot,tw);
            if(tsmg)tsmg=min(tsmg,min(tw-mytp.getless(tw),mytp.getmore(tw)-tw));
        }
        else if(tc[4]=='G')
        {
            printf("%I64d\n",min(tsm,mys.s[1].minw));
        }
        else
        {
            printf("%I64d\n",tsmg);
        }
    }
};

            
        
