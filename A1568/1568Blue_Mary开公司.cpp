#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
double tib,tik;
#define double long double
struct tnode
{
    tnode *c[2];
    double k;
    int id;
    int fix;
};
struct cline
{
    int lt,rt;double k,b;
}tline[100001];int pline;
struct treap
{
    tnode *root;
    void printnode(tnode *it,int idp)
    {
        if(!it)return;
        printnode(it->c[1],idp+1);
        for each(i,idp)cout<<" ";
        cout<<"["<<it->id<<"]"<<":"<<it->k<<":"<<tline[it->id].lt<<"-"<<tline[it->id].rt<<endl;
        printnode(it->c[0],idp+1);
    }
    void printtree()
    {
        printnode(root,0);
    }
    inline void rotatenode(tnode *&it,bool idir)//0×ó×ªÓÒ1ÓÒ×ª×ó 
    {
        tnode *tt=it->c[idir];it->c[idir]=tt->c[!idir];tt->c[!idir]=it;it=tt;
    }
    void insertnode(tnode *&it,int id)
    {
        double ik=tline[id].k;
        if(!it)
        {
            it=new tnode();
            it->id=id;
            it->k=ik;
            it->fix=rand()%100;
        }
        else
        {
            if(ik<it->k)
            {
                insertnode(it->c[0],id);
                if(it->c[0]->fix>it->fix)rotatenode(it,0);
            }
            else
            {
                insertnode(it->c[1],id);
                if(it->c[1]->fix>it->fix)rotatenode(it,1);
            }
        }   
    }
    void inserttree(int id)
    {
        insertnode(root,id);
    }
    void deletenode(tnode *&it,int id)
    {
        tnode *tt;
        double ik=tline[id].k;
        if(it->id==id)
        {
            if(it->c[0]&&it->c[1])
            {
                if(it->c[0]->fix>it->c[1]->fix)
                {
                    rotatenode(it,0);
                    deletenode(it->c[1],id);
                }
                else
                {
                    rotatenode(it,1);
                    deletenode(it->c[0],id);
                }
            }
            else
            {
                if(it->c[0])
                {
                    tt=it;
                    it=it->c[0];
                    delete(tt);
                }
                else
                {
                    tt=it;
                    it=it->c[1];
                    delete(tt);
                }
            }
        }
        else
        {
            if(ik<it->k)
            {
                deletenode(it->c[0],id);
                if(it->c[0])if(it->c[0]->fix>it->fix)rotatenode(it,0);
            }
            else
            {
                deletenode(it->c[1],id);
                if(it->c[1])if(it->c[1]->fix>it->fix)rotatenode(it,1);
            }
        }
    }
    void deletetree(int id)
    {
        deletenode(root,id);
    }
    tnode *findprev(tnode *it,int id)
    {
        if(!it)return 0;
        tnode *tt;
        double ik=tline[id].k;
        if(ik>=it->k)
        {
            tt=findprev(it->c[1],id);
            if(!tt)return it;return tt;
        }
        else
        {
            return findprev(it->c[0],id);
        }
    }
    tnode *findnext(tnode *it,int id)
    {
        if(!it)return 0;
        tnode *tt;
        double ik=tline[id].k;
        if(ik>it->k)
        {
            return findnext(it->c[1],id);
        }
        else
        {
            tt=findnext(it->c[0],id);
            if(!tt)return it;return tt;
        }
    }
    tnode *findat(tnode *it,int iday)
    {
        if(!it)return 0;
        //cout<<"Finding:"<<it->id<<":"<<tline[it->id].lt<<"-"<<tline[it->id].rt<<","<<iday<<endl;
        if(tline[it->id].lt<=iday && iday<=tline[it->id].rt)return it;
        if(iday>tline[it->id].rt)
        {
            return findat(it->c[1],iday);
        }
        else
        {
            return findat(it->c[0],iday);
        }
    }
    tnode *findtree(int id,bool icmp)//0:Less 1:More
    {
        if(icmp)return findnext(root,id);
        return findprev(root,id);
    }
}myt;
int n;
double getins(cline ia,cline ib)
{
    return (ia.b-ib.b)/(ib.k-ia.k);
}
#define ole while(true)cout<<"FUCKinginginginginging";
int tsday;
int main()
{
    freopen("1568.in","r",stdin);
    freopen("1568.out","w",stdout);
    scanf("%d",&n);
    ++pline;myt.inserttree(1);
    tline[pline].lt=0;tline[pline].rt=50001;
    char tc[16];int tday;
    double tb,tk;
    double tx;
    int tid;tnode *tt;
    for each(i,n)
    {
        scanf("%s",&tc[0]);
        if(tc[0]=='P')
        {
            scanf("%lf%lf",&tib,&tik);
            tb=tib;tk=tik;
            
            ++pline;
            //if(tk<0)ole;
            tline[pline]=(cline){99999999,-99999999,tk,tb};
            while(tt=myt.findtree(pline,0))
            {
                tid=tt->id;
                
                //cout<<"ACH"<<tt->id<<endl;
                if(abs(tline[pline].k-tline[tid].k)<=1e-4)
                {
                    if(tline[pline].b>tline[tid].b)
                    {
                        tline[pline].lt=tline[tid].lt;
                        tline[pline].rt=tline[tid].rt;
                        myt.deletetree(tid);
                        continue;
                    }
                    else goto die;
                }
                tx=getins(tline[tid],tline[pline]);
                if(tline[tid].rt>tx)
                {
                    tline[pline].rt=max(tline[pline].rt,tline[tid].rt);
                    tline[tid].rt=(int)tx;
                    tline[pline].lt=(int)tx+1;
                }
                if(tline[tid].rt<tline[tid].lt)
                {
                    //tline[pline].lt=tline[tid].lt;
                    myt.deletetree(tid);
                }
                else goto redo;
            }
            tline[pline].lt=0;
            redo:;
            while(tt=myt.findtree(pline,1))
            {
                
                tid=tt->id;
                //cout<<"ACH"<<tt->id<<endl;
                if(abs(tline[pline].k-tline[tid].k)<=1e-4)
                {
                    if(tline[pline].b>tline[tid].b)
                    {
                        tline[pline].lt=tline[tid].lt;
                        tline[pline].rt=tline[tid].rt;
                        myt.deletetree(tid);
                        continue;
                    }
                    else goto die;
                }
                tx=getins(tline[tid],tline[pline]);
                if(tline[tid].lt<tx+1)
                {
                    tline[pline].lt=min(tline[pline].lt,tline[tid].lt);
                    tline[tid].lt=(int)tx+1;
                    tline[pline].rt=(int)tx;
                }
                if(tline[tid].rt<tline[tid].lt)
                {
                   //tline[pline].rt=tline[tid].rt;
                    myt.deletetree(tid);
                }
                else goto redo2;
            }
            tline[pline].rt=50001;
            redo2:;
            
            if(tline[pline].rt>=tline[pline].lt)
            {
                //cout<<tline[pline].lt<<","<<tline[pline].rt<<endl;
                myt.inserttree(pline);
            }
            die:;
            //myt.printtree();
        }
        else
        {
            scanf("%d",&tday);
            //if(tday<=0||tday>50000)ole;
            --tday;
            tt=myt.findat(myt.root,tday);
            while(!tt)
            {
                
                //ole;
                //cout<<tday<<endl;
                //myt.printtree();
                //return 1;
                
            }
            tid=tt->id;
            tx=tline[tid].k*tday+tline[tid].b;
            printf("%d\n",(int)(tx/100));
        }
    }
    //myt.printtree();
}
