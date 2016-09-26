#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
#define size(p) ((p)->rt-(p)->lt+1)
#define local(p,in) (in-(p)->lt+1)
#define root(p,in) (in+(p)->lt-1)
#define hmod 999997
//#define inline
inline int enhash(char *iname)
{
    int tlen=strlen(iname);
    int res=tlen*37;
    for each(i,tlen)
    {
        res=(3*res*(long long)(iname[i-1]+7*i))%hmod;
    }
    return res;
}
struct hashtable
{
    int antihash[1000001];int pin;
    struct lnode{char name[11];int num;int next;}myl[1000001];int pmyl;
    struct hnode{int first;}myh[1000001];
    inline int add(char *iname)
    {
        int thash=enhash(iname);
        strcpy(myl[++pmyl].name,iname);
        myl[pmyl].num=++pin;
        myl[pmyl].next=myh[thash].first;myh[thash].first=pmyl;
        antihash[pin]=pmyl;
        return pin;
    }
    inline int ask(char *iname)
    {
        int thash=enhash(iname);
        for(int p=myh[thash].first;p;p=myl[p].next)
        {
            if(myl[p].name[0]==iname[0])
            {
                if(strcmp(myl[p].name,iname)==0)
                {
                    return myl[p].num;
                }
            }
        }
        return 0;
    }
    inline char *askanti(int inum)
    {
        return myl[antihash[inum]].name;
    }
}myhash;
struct pnode
{
    int num;
    int score;
};
struct mnode
{
    mnode *next;
    int lt,rt;
    pnode w[4002];
    //inline int size(){return rt-lt+1;};
    
};
int n;
int nbsize=2;
struct cblock
{
    mnode *posarr[1000001];
    mnode *first;
    int nsize;
    inline void print()
    {
        for(mnode *p=first->next;p;p=p->next)
        {
            cout<<"["<<p->lt<<"-"<<p->rt<<"]"; 
            for each(i,size(p))
            {
                cout<<p->w[i].num<<":"<<p->w[i].score<<" ";
            }
            cout<<endl;
        }
    }
    inline void splitnode(mnode *ip)
    {
        mnode *tnext=ip->next;
        ip->next=new mnode();
        ip->next->lt=size(ip)/2+ip->lt;
        ip->next->rt=ip->rt;
        ip->next->next=tnext;
        for every(i,ip->next->lt,ip->next->rt)
        {
            posarr[ip->w[local(ip,i)].num]=ip->next;
            ip->next->w[local(ip->next,i)]=ip->w[local(ip,i)];
        }
        ip->rt=ip->next->lt-1;
    }
    inline void mergenode(mnode *ip)
    {
        mnode *tnext=ip->next;
        ip->next=ip->next->next;
        ip->rt=tnext->rt;
        for every(i,tnext->lt,tnext->rt)
        {
            posarr[tnext->w[local(tnext,i)].num]=ip;
            ip->w[local(ip,i)]=tnext->w[local(tnext,i)];
        }
        delete tnext;
    }
    inline void check()
    {
        for(mnode *p=first->next;p;p=p->next)
        {
            if(size(p)>=nbsize)
            {
                splitnode(p);
            }
            if(p->next)
            {
                if(size(p)+size(p->next)<nbsize)
                {
                    mergenode(p);
                }
            }
        }
    }
    inline void check_this(mnode *ip)
    {
        //for(mnode *p=first->next;p;p=p->next)
        //{
            if(size(ip)>=nbsize)
            {
                splitnode(ip);
            }
            if(ip->next)
            {
                if(size(ip)+size(ip->next)<nbsize)
                {
                    mergenode(ip);
                }
            }
        //}
    }
    inline int askrank(int irank)
    {
        int tcount=0;
        for(mnode *p=first->next;p;p=p->next)
        {
            tcount=tcount+size(p);
            if(tcount>=irank)
            {
                tcount-=size(p);
                return p->w[local(p,irank)].num;
            }
        }
        return -1;
    }
    inline void insert(int inum,int iscore)
    {
        for(mnode *p=first->next;p;p=p->next)
        {
            if(p->w[local(p,p->rt)].score<iscore)
            {
                for every(i,1,size(p))
                {
                    if(p->w[i].score<iscore)
                    {
                        posarr[inum]=p;
                        for(int j=size(p);j>=i;--j)
                        {
                            p->w[j+1]=p->w[j];
                        }
                        p->rt++;
                        p->w[i]=(pnode){inum,iscore};
                        for (mnode *ip=p->next;ip;ip=ip->next)
                        {
                            ip->lt++;ip->rt++;
                        }
                        nsize++; 
                        check_this(p); 
                        break;
                    }
                }
                break;
            }
        }
        
    }
    inline int asknum(int inum)
    {
        mnode *ip=posarr[inum];
        for every(i,ip->lt,ip->rt)
        {
            if(ip->w[local(ip,i)].num==inum)
            {
                return i;
            }
        }
    }
    inline void remove(int inum)
    {
        mnode *ip=posarr[inum];
        for every(i,ip->lt,ip->rt)
        {
            if(ip->w[local(ip,i)].num==inum)
            {
                for every(j,local(ip,i)+1,size(ip))
                {
                    ip->w[j-1]=ip->w[j];
                }
                ip->rt--;
                for (mnode *p=ip->next;p;p=p->next)
                {
                    p->lt--;p->rt--;
                }
                nsize--;
                check_this(ip); 
                break;
            }
        }
        /*
        int tcount=0,ti;
        for(mnode *p=first->next;p;p=p->next)
        {
            tcount=tcount+size(p);
            if(tcount>=irank)
            {
                tcount-=size(p);
                ti=local(p,irank);
                for every(j,ti+1,size(p))
                {
                    p->w[j-1]=p->w[j];
                }
                p->rt--;
                for (mnode *ip=p->next;ip;ip=ip->next)
                {
                    ip->lt--;ip->rt--;
                }
                break;
            }
        }*/
        
    }
    inline void init()
    {
        mnode *tp=(first=new mnode());
        tp->lt=1;tp->rt=0;
        tp->next=new mnode();
        tp=tp->next;
        tp->lt=1;tp->rt=1;tp->w[1].score=-1999999999;
    }
}myb;
inline char getlet()
{
    char tc=0;
    while(tc!='+'&&tc!='?')
    {
        tc=getchar();
    }
    return tc;
}
bool ttype;
inline int getwhat()
{
    char tc=getchar();
    int res=0;
    if(tc>='0'&&tc<='9')
    {
        ttype=0;
        while(tc>='0'&&tc<='9')
        {
            res=res*10+tc-'0';
            tc=getchar();
        }
        return res;
    }
    else
    {
        char tget[11]={};int ptget=0;
        ttype=1;
        while(tc>='A'&&tc<='Z')
        {
            tget[ptget++]=tc;
            tc=getchar();
        }
        //cout<<"AskP:"<<tget<<endl;
        return myhash.ask(tget);
    }
}
int main()
{
    freopen("1862.in","r",stdin);
    freopen("1862.out","w",stdout);
    /*myhash.add("hello");
    cout<<myhash.ask("hellos");
    myhash.add("hi");
    cout<<myhash.ask("hi");
    myhash.add("you");
    cout<<myhash.askanti(3);
    myb.init();
    myb.insert(1,239);
    myb.insert(2,333);
    myb.insert(3,9);
    //myb.splitnode(myb.first->next);
    //myb.splitnode(myb.first->next->next);
    myb.insert(35,17);
    myb.insert(55,200);
    myb.insert(123,123);
    myb.insert(234,234);
    myb.insert(38,200);
    myb.remove(3);
    myb.remove(3);
    myb.remove(3);
    myb.mergenode(myb.first->next->next);
    myb.print();
    cout<<myb.askrank(4);*/
    myb.init();
    scanf("%d",&n);
    nbsize=(int)sqrt(n)*2;
    char tget[11];
    int tnum;
    int tv;//GET Hash
    int tscore;
    for each(i,n)
    {
        if(getlet()=='+')
        {
            scanf("%s%d",&tget[0],&tscore);
            //cout<<"ADD:"<<tget<<endl;
            tv=myhash.ask(tget);
            if(tv)
            {
                //cout<<"Remove:"<<tget<<endl;
                //myb.print();
                myb.remove(tv);
                //myb.print();
                myb.insert(tv,tscore);
            }
            else
            {
                tv=myhash.add(tget);
                myb.insert(tv,tscore);
            }
        }
        else
        {
            tnum=getwhat();
            if(ttype==0)
            {
                //cout<<"Asknum"<<tnum<<endl;
                for each(i,10)
                {
                    tv=myb.askrank(tnum+i-1);
                    if(tv<=0)break;
                    //cout<<i<<":";
                    if(i!=1)
                    printf(" ");
                    printf("%s",myhash.askanti(tv));
                }
                printf("\n");
            }
            else
            {
                printf("%d\n",myb.asknum(tnum));
            }
        }
    }
} 
