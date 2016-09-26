#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int inx[50001],iny[50001];
long long dp[50001];
int n;
struct segtree
{
    private:
    struct tnode
    {
        int tmax;
    }t[100001];
    int n;
    //segtree(int in){n=in;}
    int asknode(int it,int il,int ir,int pl,int pr)
    {
        if(il>=pl&&ir<=pr)return t[it].tmax;
        if(il>=pr||ir<=pl)return 0;
        return max(
         asknode(it<<1,il,((il+ir)>>1),pl,pr),
          asknode((it<<1)+1,((il+ir)>>1),ir,pl,pr));
    }
    void buildnode(int it,int il,int ir,int *idata)
    {
        //if(il>=ir)return;
        if(il+1==ir)
        {
            t[it].tmax=idata[il];
            return;
        }
        buildnode(it<<1,il,((il+ir)>>1),idata);
        buildnode((it<<1)+1,((il+ir)>>1),ir,idata);
        t[it].tmax=max(t[it<<1].tmax,t[(it<<1)+1].tmax);
    }
    public:
    inline int asktree(int pl,int pr)
    {
        return asknode(1,1,n+1,pl,pr+1);
    }
    inline void buildtree(int *idata)
    {
        buildnode(1,1,n+1,idata);
    }
}mytx,myty;
#define getw(i,j) (mytx.asktree(i,j)*(long long)myty.asktree(i,j))
struct queue
{
    struct qnode
    {
        int lt,n;
    }d[50001];
    int front,back;
    inline void push(qnode in){d[++back]=in;}
    inline qnode top(){return d[front];}
    inline qnode pop(){return d[front++];}
    inline bool empty(){return front==back+1;}
    inline int count(){return back-front+1;}
    queue(){front=1;back=0;};
}myq;
int main()
{
    freopen("1597.in","r",stdin);
    freopen("1597.out","w",stdout);
    scanf("%d",&n);
    for each(i,n)scanf("%d%d",&inx[i],&iny[i]);
    mytx.buildtree(inx);
    myty.buildtree(iny);
    myq.push((queue::qnode){1,0});
    dp[0]=0;
    int tk;
    int tml,tmr,tm;
    int tl;
    for each(i,n)
    {
        while(myq.d[myq.front+1].lt<=i&&myq.front+1<=myq.back)myq.pop();
        tk=myq.top().n;
        dp[i]=dp[tk]+getw(tk+1,i);
        #define supertest(pos,old,new)\
        (dp[old]+getw((old)+1,pos)>=dp[new]+getw((new)+1,pos))
        tm=i;
        for(;!myq.empty();--myq.back)
        {
            tl=max(myq.d[myq.back].lt,i+1);
            if(supertest(tl,myq.d[myq.back].n,i))
            {
                //cout<<"Die:"<<myq.d[myq.back].n<<"("<<myq.d[myq.back].lt<<")"<<endl;
                continue;
            }
            tml=tl;tmr=n+1;
            while(tml+1!=tmr)
            {
                tm=(tml+tmr)/2;
                if(supertest(tm,myq.d[myq.back].n,i))
                {
                    tmr=tm;
                }
                else
                {
                    tml=tm;
                }
            }
            break;
        }
        if(tm<n)
        myq.push((queue::qnode){tm+1,i});
        cout<<tm+1<<endl;
    }
    cout<<dp[n]<<endl;
}
