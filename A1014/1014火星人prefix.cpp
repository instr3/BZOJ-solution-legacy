#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
#define mod 1000000007
#define oo 99999999
#define base 127
struct tnode
{
    tnode *p,*c[2];
    int hash;//int w;
    int ct;
    char id;
}*root;
int mbase[100001];
struct splaytree
{
    void print(tnode *it=root,int idp=0)
    {
        if(!it)return;
        print(it->c[1],idp+1);
        for each(i,idp)cout<<" ";
        cout<<"["<<it->id<<"]:"<<(it->ct)<<","<<it->hash<<endl;
        print(it->c[0],idp+1);
    }
    inline void updata(tnode *it)
    {
        #define getct(node) ((node)?(node)->ct:0)
        #define gethash(node) ((node)?(node)->hash:0)
        it->ct=getct(it->c[0])+getct(it->c[1])+1;
        it->hash=(gethash(it->c[0])+(long long)it->id*mbase[getct(it->c[0])]+
         (long long)gethash(it->c[1])*mbase[getct(it->c[0])+1])%mod;
    }
    inline void rotate(tnode *it,bool idir)//0:Lt 1:Rt
    {
        tnode *tt=it->c[idir];
        if(!tt)cout<<"[Error]In Rotate:Child Not Found"<<endl;
        it->c[idir]=tt->c[!idir];
        if(it->c[idir])it->c[idir]->p=it;
        if(it->p)
        {
            bool tvar=it->p->c[1]==it;
            it->p->c[tvar]=tt;
            tt->p=it->p;
        }
        else
        {
            root=tt;
            tt->p=0;
        }
        tt->c[!idir]=it;
        it->p=tt;
        updata(it);
        updata(tt);
    }
    inline void splay(tnode *it,tnode *ipos)
    {
        bool tv1,tv2;
        while(it->p!=ipos)
        {
            tv1=it->p->c[1]==it;
            if(it->p->p==ipos)
            {
                rotate(it->p,tv1);
                return;
            }
            tv2=it->p->p->c[1]==it->p;
            if(tv1==tv2)
            {
                rotate(it->p->p,tv2);
                rotate(it->p,tv1);
                //print();
            }
            else
            {
                rotate(it->p,tv1);
                rotate(it->p,tv2);
            }
        }
    }
    inline void newnode(tnode *&it,char id)
    {
        it=new tnode();
        //it->w=iw;
        it->id=id;
        updata(it);
    }
    inline void deletenode(tnode *&it)
    {
        delete it;
        it=0;
    }
    /*tnode *inserttree(int iw)
    {
        tnode *it=root;
        if(!it)return newnode(root,iw);
        while(true)
        {
            if(it->w>=iw)
            {
                if(!it->c[0])
                {
                    newnode(it->c[0],iw)->p=it;
                    for(tnode *tt=it;tt;tt=tt->p)updata(tt);
                    return it->c[0];
                }
                it=it->c[0];
            }
            else
            {
                if(!it->c[1])
                {
                    newnode(it->c[1],iw)->p=it;
                    for(tnode *tt=it;tt;tt=tt->p)updata(tt);
                    return it->c[1];
                }
                it=it->c[1];
            }
        }
    }*/
    inline tnode *findk(int ik)
    {
        ++ik;
        tnode *it=root;
        int tl;
        while(true)
        {
            if(!it)cout<<"[Error]In findk:it is NULL"<<endl;
            tl=it->c[0]?it->c[0]->ct:0;
            if(ik==tl+1)return it;
            if(ik>tl+1){it=it->c[1];ik-=tl+1;}
            else it=it->c[0];
        }
    }
    inline void deletek(int ik)
    {
        splay(findk(ik-1),0);
        splay(findk(ik+1),root);
        deletenode(root->c[1]->c[0]);
        updata(root->c[1]);updata(root);
    }
    inline void insertk(int ik,char id)
    {
        splay(findk(ik-1),0);
        splay(findk(ik),root);
        newnode(root->c[1]->c[0],id);
        root->c[1]->c[0]->p=root->c[1];
        //updata(root->c[1]->c[0]);
        updata(root->c[1]);updata(root);
    }
    splaytree()//Init
    {
        newnode(root,1);
        newnode(root->c[1],9);
        root->c[1]->p=root;
        updata(root);
    }
    
    inline bool testsame(int ik1,int ik2,int il)
    {
        int th1,th2;
        splay(findk(ik1-1),0);
        splay(findk(ik1+il),root);
        th1=root->c[1]->c[0]->hash;
        splay(findk(ik2-1),0);
        splay(findk(ik2+il),root);
        th2=root->c[1]->c[0]->hash;
        //cout<<il<<":"<<th1<<","<<th2<<endl;
        return th1==th2;
    }
    inline int getmax(int ik1,int ik2)
    {
        int tct=root->ct-2;
        int tl=0,tr=tct-max(ik1,ik2)+1,tm;
        while(tr!=tl)
        {
            tm=(tl+tr+1)/2;
            if(testsame(ik1,ik2,tm))tl=tm;else tr=tm-1;
        }
        return tl;
    }
    inline void changek(int ik,char id)
    {
        splay(findk(ik-1),0);
        splay(findk(ik+1),root);
        root->c[1]->c[0]->id=id;
        updata(root->c[1]->c[0]);
        updata(root->c[1]);updata(root);
    }
    char is[100001];
    tnode *buildtree(tnode *&it,int il,int ir)
    {
        if(il==ir)return 0;
        int im=(il+ir)/2;
        newnode(it,is[im-1]);
        tnode *tt;
        tt=buildtree(it->c[0],il,im);if(tt)tt->p=it;
        tt=buildtree(it->c[1],im+1,ir);if(tt)tt->p=it;
        
        updata(it);
        return it;
    }
}myt;

int main()
{
    freopen("1014.in","r",stdin);
    freopen("1014.out","w",stdout);
    mbase[0]=1;
    for each(i,100001)mbase[i]=((long long)mbase[i-1]*base)%mod;
    tnode *tt;
    /*myt.insertk(1,2);
    myt.insertk(2,3);
    myt.insertk(3,4);
    myt.insertk(4,2);
    myt.insertk(5,3);
    myt.insertk(6,2);
    myt.changek(3,4);
    cout<<myt.getmax(1,4);
    myt.print();*/
    
    int n;
    scanf("%s",&myt.is[0]);
    myt.buildtree(root->c[1]->c[0],1,strlen(myt.is)+1)->p=root->c[1];
    myt.updata(root->c[1]);myt.updata(root);
    
    //for each(i,strlen(myt.is))
    //{
        //myt.insertk(i,myt.is[i-1]);
    //}
    //myt.print();
    scanf("%d",&n);
    char tc[2];
    int tv1,tv2;
    for each(i,n)
    {
        scanf("%s",&tc[0]);
        switch(tc[0])
        {
            case 'I':
                scanf("%d%s",&tv1,&tc[0]);myt.insertk(tv1+1,tc[0]);
                break;
            case 'R':
                scanf("%d%s",&tv1,&tc[0]);myt.changek(tv1,tc[0]);
                break;
            case 'Q':
                scanf("%d%d",&tv1,&tv2);printf("%d\n",myt.getmax(tv1,tv2));
                break;
            default:;
        }
    }
}
