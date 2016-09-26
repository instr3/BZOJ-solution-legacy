#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
struct clink
{
    int n;
    int dsize;
    struct bnode
    {
        int lt,rt;
        int s[2001];
        int msame;
        bool mrev;
        int sum,lmax,rmax;int imax;
        inline const int size(){return rt-lt+1;}
        bnode *next;
    }*first,memlist[2001];int pmlist;
    bnode *memstk[2001];int pstk;
    inline void deletebnode(bnode *ib)
    {
        //cout<<"D:"<<pstk<<endl;
        memstk[++pstk]=ib;
    }
    inline bnode *newbnode()
    {
        //cout<<"Y:"<<pmlist<<endl;
        if(pstk==0)return &memlist[++pmlist];
        bnode *tget=memstk[pstk--];
        tget->msame=tget->mrev=0;
        return tget;
    }
    inline void downdata(bnode *ib)
    {
        if(ib->mrev)
        {
            int ts=(ib->size())/2;
            for each(i,ts)swap(ib->s[i],ib->s[ib->size()+1-i]);
            ib->mrev=false;
        }
        if(ib->msame)
        {
            if(ib->msame==123456789)ib->msame=0;
            for each(i,ib->size())
            {
                ib->s[i]=ib->msame;
            }
        }
        ib->msame=0;
    }
    inline void updata(bnode *ib)
    {
        if(ib->msame)
        {
            if(ib->msame==123456789)ib->msame=0;
            ib->sum=ib->imax=ib->lmax=ib->rmax=((int)ib->msame)*ib->size();
            ib->imax=ib->lmax=ib->rmax=max((int)ib->msame,ib->lmax);
            //ib->msame
            if(ib->msame==0)ib->msame=123456789;
            return;
        }
        ib->sum=0;ib->lmax=ib->rmax=ib->imax=-999999999;
        int trsum=0;
        int iml=0;
        for each(i,ib->size())
        {
            ib->sum+=ib->s[i];
            ib->imax=max(ib->imax,iml+ib->s[i]);
            iml=max(0,max(iml+ib->s[i],(int)ib->s[i]));
            ib->lmax=max(ib->lmax,ib->sum);
        }
        for(int i=ib->size();i>=1;--i)
        {
            trsum+=ib->s[i];
            ib->rmax=max(ib->rmax,trsum);
        }
        if(ib->mrev)swap(ib->lmax,ib->rmax);
        //!
        //ib->lmax=max(0,ib->lmax);
        //ib->rmax=max(0,ib->rmax);
        //ib->imax=max(0,ib->imax);
    }

    void print()
    {
        for(bnode *p=first;p;p=p->next)
        {
            downdata(p);
            //updata(p);
            for every(i,1,p->size())
            {
                cout<<p->s[i]<<" ";
            }
            cout<<":"<<p->lt<<"-"<<p->rt<<":"<<p->imax<<","<<p->lmax<<","<<p->rmax<<endl;
        }
    }
    bnode *locate(int ik)//locate prev
    {
        for(bnode *p=first;p->next;p=p->next)
        {
            if(p->next->lt<=ik&&p->next->rt>=ik)return p;
        }
        return 0;
    }
    inline void mergenode(bnode *ib)//ib当前块
    {
        bnode *tb=ib->next;
        downdata(ib);downdata(tb);
        memcpy(&ib->s[ib->size()+1],&tb->s[1],tb->size()*sizeof(int));
        ib->rt=tb->rt;
        ib->next=tb->next;
        updata(ib);
        deletebnode(tb);
    }
    inline void splitnode(bnode *ib)
    {
        int ik=ib->size()/2+ib->lt;
        downdata(ib);
        bnode *tb=newbnode();
        tb->next=ib->next;
        tb->rt=ib->rt;
        tb->lt=ik;
        memcpy(&tb->s[1],&ib->s[ik-ib->lt+1],tb->size()*sizeof(int));
        ib->next=tb;
        ib->rt=ik-1;
        updata(ib);
        updata(tb);
    }
    inline void check()
    {
        if(!first->next)return;
        if(first->next->size()>2*dsize)splitnode(first->next);
        for(bnode *p=first->next;p->next;p=p->next)
        {
            if(p->next->size()>2*dsize)splitnode(p->next);
            if(p->size()+p->next->size()<=dsize)mergenode(p);
            if(!p->next)return;
        }
    }
    inline bnode *cutnode(bnode *ib,int ik)//ib表示切割块前面那个块 
    {
        if(ib==0)ib=locate(ik);
        if(ib->next->lt==ik)return ib;
        ib=ib->next;
        downdata(ib);
        bnode *tb=newbnode();
        tb->next=ib->next;
        tb->rt=ib->rt;
        tb->lt=ik;
        memcpy(&tb->s[1],&ib->s[ik-ib->lt+1],tb->size()*sizeof(int));
        ib->next=tb;
        ib->rt=ik-1;
        updata(ib);
        updata(tb);
        //check();
        return ib;
    }
    inline void setmark(int ik,int in,int inum)
    {
        bnode *tb=cutnode(0,ik);
        bnode *tb2=cutnode(0,ik+in);
        for(bnode *p=tb->next;p!=tb2->next;p=p->next)
        {
            //if(p->mrev)p->mrev=false;
            if(inum==0)inum=123456789;
            p->msame=inum;
            updata(p);
        }
        check();
    }
    inline void setrev(int ik,int in)
    {
        bnode *tb=cutnode(0,ik);
        bnode *tb2=cutnode(0,ik+in);
        bnode *tto,*tfr=tb2->next;
        //bnode *tfrom=tb->next;
        bnode *tnext=tb2->next;
        for(bnode *p=tb->next;p!=tnext;p=tto)
        {
            tto=p->next;
        
            p->next=tfr;
           // if(!p->msame)
            p->mrev^=1;
            tfr=p;
            swap(p->lmax,p->rmax);
        }
        tb->next=tb2;
        int tlt=tb->rt;int ts;
        for(bnode *p=tb2;p!=tnext;p=p->next)
        {
            ts=p->size();
            p->lt=tlt+1;p->rt=tlt+ts;
            tlt+=ts;
        }
        
        check();
    }
    inline void insertnode(bnode *ib,int in,int *idata)//ib指前面那个块 
    {
        int tlt=ib->rt;
        int tf=tlt;
        bnode *tnext=ib->next;
        int tblock=(in-1)/dsize+1;
        int ti=0; 
        for each(k,tblock)
        {
            ib->next=newbnode();
            ib->next->lt=tlt+1;
            ib->next->rt=min(tlt+dsize,tf+in);
            ib=ib->next;
            tlt=ib->rt;
            for each(i,ib->size())
            {
                ib->s[i]=idata[ti++];
            }
            updata(ib);
        }
        ib->next=tnext;
        for(bnode *p=tnext;p;p=p->next)
        {
            p->lt+=in;
            p->rt+=in;
        }
        check();
    }
    inline void deletenode(bnode *ib,bnode *ito)//删除的前面那个块->最后那个块 
    {
        bnode *tnext=ito->next;
        int in=0;
        bnode *td;
        for(bnode *p=ib->next;p!=tnext;p=td)
        {
            in+=p->rt-p->lt+1;
            td=p->next;
            deletebnode(p);
        }
        ib->next=tnext;
        for(bnode *p=tnext;p;p=p->next)
        {
            p->lt-=in;
            p->rt-=in;
        }
        check();
    }
    inline void insertlist(int ik,int in,int *idata)
    {
        bnode *tb=cutnode(0,ik);
        insertnode(tb,in,idata);
    }    
    inline void deletelist(int ik,int in)
    {
        bnode *tb=cutnode(0,ik);
        bnode *tb2=cutnode(0,ik+in);
        deletenode(tb,tb2);
    }   
    inline int getsum(int ik,int in)
    {
        bnode *tb=cutnode(0,ik);
        bnode *tb2=cutnode(0,ik+in);
        int res=0;
        for(bnode *p=tb->next;p!=tb2->next;p=p->next)
        {
            res+=p->sum;
        }
        return res;
    }
    inline int getgmax()
    {
        int fmax=0,res=-999999999;
        for(bnode *p=first->next;p;p=p->next)
        {
            res=max(res,p->imax);
            res=max(res,fmax+p->lmax);
            fmax=max(fmax+p->sum,p->rmax);
            res=max(res,fmax);
        }
        return res;
    }
    inline void init(int in,int *idata)
    {
        dsize=707;
        first=newbnode();first->lt=1;
        insertnode(first,in,idata);
    }
}myl;
int indata[500001];
int main()
{
    freopen("1500.in","r",stdin);
    freopen("1500.out","w",stdout);
    //int indata[13]={0,1,2,3,4,5,6,7,8,9,10,11,12};
    //myl.init(10,indata+1);
    //myl.cutnode(0,9);
    //myl.insertlist(2,5,indata+1);
    //myl.setrev(3,7);
    //myl.print();
    //myl.splitnode(myl.locate(8)->next);
    //myl.print();
    int n,nm;
    char top[100];
    scanf("%d%d",&n,&nm);
    for each(i,n){scanf("%d",&indata[i]);}//myl.print();}
    indata[n+1]=-199999999;
    myl.init(n+1,indata+1);
    int tpos,tto,tn,tw;
    for each(i,nm)
    {
        scanf("%s",&top[0]);
        //cout<<top<<endl;
        //myl.print();
        switch(top[0])
        {
            case 'I':
                scanf("%d%d",&tpos,&tn);
                for each(i,tn)scanf("%d",&indata[i]);
                myl.insertlist(tpos+1,tn,indata+1);
                break;
            case 'D':
                scanf("%d%d",&tpos,&tn);
                myl.deletelist(tpos,tn);
                break;
            case 'G':
                scanf("%d%d",&tpos,&tto);
                //printf("0\n",myl.getsum(tpos,tto));
                printf("%d\n",myl.getsum(tpos,tto));
                break;
            case 'M':
                if(top[2]=='X')
                {
                    printf("%d\n",myl.getgmax());
                }
                else
                {
                    scanf("%d%d%d",&tpos,&tn,&tw);
                    myl.setmark(tpos,tn,tw);
                }
                break;
            case 'R':
                scanf("%d%d",&tpos,&tn);
                myl.setrev(tpos,tn);
                //myl.print();
                break;
            default:;
        }
        
    }
    //myl.print();
}
