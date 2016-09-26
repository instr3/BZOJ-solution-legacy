#include <iostream>
#include <cstdlib>
//#include <cstring>
#include <cstdio>
//#include <cmath>
#include <algorithm>
#include <map>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
int n,nt;
struct mnode
{
    int num;int exist;
};
map<int,mnode>mym;
map<int,mnode>myanti;
map<int,int>myf;
struct indnode
{
    int yr;int w;int tf;
    bool operator <(indnode ano)const
    {
        return w<ano.w;
    }
}indata[50001],tdata[50001];
bool tnop(indnode t1,indnode t2)
{
    return t1.yr<t2.yr;
}
inline void predcrete()
{
    scanf("%d",&n);
    for each(i,n)
    {
        scanf("%d%d",&indata[i].yr,&indata[i].w);
        //tdata[i].yr=indata[i].yr;
        //tdata[i].w=indata[i].w;
    }
    sort(indata+1,indata+n+1);
    int tlast=0, tlabel=0;
    for each(i,n)
    {
        //cout<<indata[i].yr<<","<<indata[i].w<<":";
        if(indata[i].w==tlast)tlast=indata[i].w,indata[i].w=tlabel;
        else tlast=indata[i].w,indata[i].w=++tlabel;
        //cout<<indata[i].w<<endl;
    }
    sort(indata+1,indata+n+1,tnop);
    int ttf=0;
    for each(i,n)
    {
        indata[i].tf=++ttf;
        myf[indata[i].yr]=i;
        //cout<<indata[i].yr<<":";
        //cout<<indata[i].w<<endl;
    }
}
struct dnode
{
    int yr,w;
    int fd;
};
struct queue
{
    dnode d[50001];
    int lt,rt;
    queue(){lt=1;}
    inline bool empty(){return lt==rt+1;}
    inline void push(int iyr,int iw)
    {
        int tfd=1;
        int tlast=-1999999999;
        int tlastyr=-1999999999;
        while(lt!=rt+1&&d[rt].w<iw)
        {
            //myanti.insert(map<int,int>::value_type(d[rt].yr,iyr));
            if(tlast==d[rt].w)myanti[d[rt].yr].num=tlastyr;else
            myanti[d[rt].yr].num=iyr;
            myanti[d[rt].yr].exist=true;
            tlastyr=d[rt].yr;
            tlast=d[rt].w;
            tfd+=d[rt].fd;
            rt--;
        }
        //cout<<d[rt].yr<<" ";
        //cout<<tfd<<endl;
        mnode tnode={};
        mym.insert(map<int,mnode>::value_type(iyr,tnode));
        
        mym[iyr].exist=true;
        if(lt==rt+1)mym[iyr].num=-1999999999;else
        mym[iyr].num=d[rt].yr;
        d[++rt].yr=iyr;
        d[rt].w=iw;
        d[rt].fd=tfd;
    }
}myq;
int main()
{
    freopen("1067.in","r",stdin);
    freopen("1067.out","w",stdout);

    predcrete();
    for each(i,n)
    {
        myq.push(indata[i].yr,indata[i].w);
    }
    myq.push(999999999,999999999);
    int nm;scanf("%d",&nm);
    int p1,p2;
    for each(i,nm)
    {
        scanf("%d%d",&p1,&p2);
        
        if((mym[p2].exist==false&&mym[p1].exist&&(myanti[p1].num<p2&&myanti[p1].exist))||(mym[p2].exist&&(mym[p2].num>p1||(mym[p1].exist&&indata[myf[p2]].w>=indata[myf[p1]].w))))printf("false\n");
        else if(mym[p2].exist&&mym[p1].exist&&indata[myf[p2]].tf-indata[myf[p1]].tf==p2-p1)
        printf("true\n");
        else printf("maybe\n");
        //if(i==3484){cout<<p1<<","<<p2<<endl;continue;}
    }
}

