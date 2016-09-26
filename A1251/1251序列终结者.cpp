#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
#define d
struct tnode
{
    tnode *c[2],*p;
    int w;
    int id;
    bool tmrev;int tmadd;
    int tmax;
    int ct;
};
int n,nm;
struct splaytree
{
    tnode tdata[50003];
    tnode *root;
    bool checkp_c(tnode *it)
    {
        if((!it->p)&&!(root==it))return true;
        if(it->c[0])if(it->c[0]->p!=it)return true;
        if(it->c[1])if(it->c[1]->p!=it)return true;
        return false;
    }
    void updata(tnode *it)
    {
        #define getmax(what) ((what)?(what->tmax):-99999999)
        #define getct(what) ((what)?(what->ct):0)
        #define trimax(a,b,c) max(a,max(b,c))
        it->ct=getct(it->c[0])+getct(it->c[1])+1;
        //it->w=getw(it->c[0])+getw(it->c[1])+it->tmadd*it->ct;
        it->tmax=trimax(getmax(it->c[0]),getmax(it->c[1]),it->w)+it->tmadd;
    }
    void downdata(tnode *it)
    {
        if(it->tmrev)
        {
            it->tmrev=false;
            swap(it->c[0],it->c[1]);
            if(it->c[0])it->c[0]->tmrev=!it->c[0]->tmrev;
            if(it->c[1])it->c[1]->tmrev=!it->c[1]->tmrev;
        }
        if(it->tmadd)
        {
            it->w+=it->tmadd;
            if(it->c[0])it->c[0]->tmadd+=it->tmadd,updata(it->c[0]);
            if(it->c[1])it->c[1]->tmadd+=it->tmadd,updata(it->c[1]);
            it->tmadd=0;
        }
    }
    void printnode(tnode *it,int idp)
    {
        if(!it)return;
        downdata(it);
        updata(it);
        printnode(it->c[1],idp+1);
        //updata(it);
        for each(i,idp)cout<<" ";
        cout<<"["<<(checkp_c(it)?"!":"")<<it->id<<"]"<<it->tmax<<":"<<it->w<<","<<it->tmadd<<endl;
        printnode(it->c[0],idp+1);
    }
    void print(){printnode(root,0);}
    void rotate(tnode *it,bool tdir)//0×ó1ÓÒ
    {
        d if(!it)
        d cout<<"Error In Rotate:Null Node"<<endl;
        tnode *tt=it->c[tdir];
        d if(!tt)
        d cout<<"Error In Rotate:Null Child"<<endl;
        //downdata(it);
        //downdata(tt);
        it->c[tdir]=tt->c[!tdir];
        if(it->c[tdir])it->c[tdir]->p=it;
        if(!it->p)
        {
            tt->p=0;
            root=tt;
        }
        else
        {
            bool tv=it->p->c[1]==it;
            tt->p=it->p;
            tt->p->c[tv]=tt;
        }
        it->p=tt;
        tt->c[!tdir]=it;
        updata(it);
        updata(tt);
    }
    void splay(tnode *it,tnode *ito)
    {
        d if(!it)
        d cout<<"Error In Splay:Null Node"<<endl;
        bool tv1,tv2;
        while(it->p!=ito)
        {
            if(it->p->p)downdata(it->p->p);
            downdata(it->p);
            downdata(it);
            if(it->p->p==ito)
            {
                rotate(it->p,it->p->c[1]==it);
                return;
            }
            else
            {
                tv1=it->p->c[1]==it;
                tv2=it->p->p->c[1]==it->p;
                if(tv1==tv2)
                {
                    rotate(it->p->p,tv2);
                    rotate(it->p,tv1);
                }
                else
                {
                    rotate(it->p,tv1);
                    rotate(it->p,tv2);
                }
            }
        }
    }
    inline tnode *findk(int ik)
    {
        ik++;
        tnode *tt=root;
        while(true)
        {
            downdata(tt);
            int tget=getct(tt->c[0]);
            if(tget>=ik)
            {
                tt=tt->c[0];
            }
            else if(ik==tget+1)
            {
                return tt;
            }
            else
            {
                ik-=tget+1;
                tt=tt->c[1];
            }
        }
    }
    inline void splayrange(int il,int ir)
    {
        splay(findk(il-1),0);
        splay(findk(ir+1),root);
    }
    inline void addrange(int il,int ir,int iw)
    {
        splayrange(il,ir);
        root->c[1]->c[0]->tmadd+=iw;
        updata(root->c[1]->c[0]);
        updata(root->c[1]);
        updata(root);
    }
    inline void revrange(int il,int ir)
    {
        splayrange(il,ir);
        root->c[1]->c[0]->tmrev=true;
    }
    inline int askrange(int il,int ir)
    {
        splayrange(il,ir);
        downdata(root->c[1]->c[0]);
        return root->c[1]->c[0]->tmax;
    }
    tnode *insertnum(tnode *&it,int id,int iw)
    {
        if(!it)
        {
            it=new tnode();
            it->id=id;
            it->w=iw;
            return it;
        }
        else
        {
            tnode *tt;
            if(id<it->id)
            {
                tt=insertnum(it->c[0],id,iw);
                it->c[0]->p=it;
                return tt;
            }
            else
            {
                tt=insertnum(it->c[1],id,iw);
                it->c[1]->p=it;return tt;
            }
        }
    }
    tnode *buildnode(tnode *&it,int il,int ir)
    {
        if(il==ir)return 0;
        if(il+1==ir)
        {
            it=&tdata[il];
            it->id=il;
            it->w=0;
            updata(it);
            return it;
        }
        else
        {
            tnode *tt;
            it=&tdata[(il+ir)>>1];
            it->id=(il+ir)>>1;
            it->w=0;
            tt=buildnode(it->c[0],il,(il+ir)>>1);
            if(tt)tt->p=it;
            tt=buildnode(it->c[1],((il+ir)>>1)+1,ir);
            if(tt)tt->p=it;
            updata(it);
            return it;
        }
    }
    void buildtree(int in)
    {
        buildnode(root,0,in+2);
    }
}myt;
int main()
{
    freopen("1251.in","r",stdin);
    freopen("1251.out","w",stdout);
    //myt.buildtree(4);
    //myt.addrange(1,1,2);
    //myt.revrange(1,3);
    //cout<<myt.askrange(1,3)<<endl;
    //myt.print();
    //return 0;
    scanf("%d%d",&n,&nm);
    myt.buildtree(n);
    int top;
    int tfr,tto,tw;
    for each(i,nm)
    {
        scanf("%d%d%d",&top,&tfr,&tto);
        switch(top)
        {
            case 1:
                scanf("%d",&tw);
                myt.addrange(tfr,tto,tw);
                break;
            case 2:
                myt.revrange(tfr,tto);
                break;
            case 3:
                printf("%d\n",myt.askrange(tfr,tto));
                break;
            default:;
        }
    }
}
