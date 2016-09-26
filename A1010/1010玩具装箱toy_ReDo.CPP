#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define os(x) ((x)*(x))
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n,nl;
int nc[50001];
long long sum[50001];
long long dp[50001];
int minat[50001];
struct tnode
{
    int lt;
    int num;
}tstk[50001];int pstk;int plt=1;
#define test(i,j) os(sum[(i)]-sum[(j)]+(i)-(j)-1-nl)
int main()
{
    freopen("1010.in","r",stdin);
    freopen("1010.out","w",stdout);
    scanf("%d%d",&n,&nl);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&nc[i]);
    }
    for(int i=1;i<=n;++i)
    {
        sum[i]=sum[i-1]+nc[i];
    }
    tstk[++pstk]=(tnode){1,0};
    int tk;
    int tml,tmr,tm;
    int tnum;
    for each(i,n)
    {
        while(tstk[plt+1].lt<=i&&plt+1<=pstk)plt++;
        tk=tstk[plt].num;
        dp[i]=dp[tk]+test(i,tk);
        tm=i;
        for(;pstk>=plt;--pstk)
        {
        
            tnum=tstk[pstk].num;
            //È«ÌåÕóÍö 
            #define temptest(pos,old,new) \
            (dp[old]+test(pos,old)>=dp[new]+test(pos,new))
            if(temptest(tstk[pstk].lt,tnum,i))
            {
                //cout<<"Delete:"<<tstk[pstk].lt<<" "<<tstk[pstk].num<<endl;
                continue;
            }
            tml=max(tstk[pstk].lt,i);tmr=n+1;
            while(tml+1!=tmr)
            {
                tm=(tml+tmr)/2;
                if(!temptest(tm,tnum,i))
                {
                    tml=tm;
                }
                else
                {
                    tmr=tm;
                }
            }
            break;
        }
        if(tml<n)
        tstk[++pstk]=(tnode){tml+1,i};
        //cout<<"New Item:"<<tml+1<<"#"<<i<<endl;
    }
    /*for(int i=1;i<=n;++i)
    {
        dp[i]=9999999999999999LL;
        for(int j=0;j<i;++j)
        {
            if(dp[i]>=dp[j]+test(i,j))
            {
                dp[i]=dp[j]+test(i,j);
                minat[i]=j;
            }
        }
    }*/
    //for(int j=1;j<=n;++j)
    //{
        
        //for(int i=j+1;i<=n;++i)
        //cout<<os(sum[i]-sum[j]+i-j-1-nl)<<" ";
        //cout<<dp[j]<<endl;
    //}
    cout<<dp[n]<<endl;
}

