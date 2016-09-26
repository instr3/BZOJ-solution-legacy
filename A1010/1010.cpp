#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define os(x) ((x)*(x))
int n,nl;
int nc[50001];
long long dp[50001];
long long sum[50001];
long long tfj[50001];
struct tnode
{
    long long x,y;int num;
}deq[50001];int pdq1=1,pdq2=0;
inline long double getk(int fr,int to)
{
    return ((long double)(deq[to].y-deq[fr].y))/(deq[to].x-deq[fr].x);
}
int main()
{

    scanf("%d%d",&n,&nl);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&nc[i]);
    }
    for(int i=1;i<=n;++i)
    {
        sum[i]=sum[i-1]+nc[i];
        tfj[i]=i+sum[i];
    }
    //Insert dp[0];
    long long tmemi,tmin,tr;
    tnode tp={};
    deq[++pdq2]=tp;
    for(int i=1;i<=n;++i)
    {
        tmemi=-(sum[i]+i-nl-1);
        tmin=9999999999999999LL;
        for(;pdq1<=pdq2;++pdq1)
        {
            tr=2*tmemi*tfj[deq[pdq1].num]+
             (os(tfj[deq[pdq1].num])+dp[deq[pdq1].num]);
            if(tmin>=tr)
            {
                tmin=tr;
                //cout<<"AC  "<<tr<<endl;
            }
            else
            {
                //cout<<"Meet "<<tr<<endl;
                break;
            }
        }
        --pdq1;
        dp[i]=tmin+os(tmemi);
        //cout<<"Ans: "<<dp[i]<<endl;
        tp.x=tfj[i];
        tp.y=os(tfj[i])+dp[i];
        tp.num=i;
        //printf("Debug:%d:AddPoint2D(%I64d,%I64d)\n",i,tp.x,tp.y);
        deq[++pdq2]=tp;
        while(pdq2-pdq1>=2&&getk(pdq2-1,pdq2)<getk(pdq2-2,pdq2-1))
        {
            //cout<<getk(pdq2-1,pdq2)<<","<<getk(pdq2-2,pdq2-1)<<endl;
            //printf("Debug:%d:DelPoint2D(%I64d,%I64d)\n",deq[pdq2-1].num,deq[pdq2-1].x,deq[pdq2-1].y);
            deq[pdq2-1]=deq[pdq2];
            pdq2--;
        }
    }
    //for(int i=1;i<=n;++i)
    //cout<<dp[i]<<endl;
    cout<<dp[n];
}
    
