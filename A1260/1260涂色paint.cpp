#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
int indata[101];
int tdp[101][101][27];
int dp(int il,int ir,int icol)
{
    if(ir<=il)return 99999999;
    if(tdp[il][ir][icol]!=-1)return tdp[il][ir][icol];
    
    if(il+1==ir)return !(icol==indata[il]);
    int res=99999999;
    for every(i,il+1,ir-1)
    {
        for each(inc,26)
        {
            //cout<<i<<","<<inc<<endl;
            res=min(res,dp(il,i,icol)+dp(i,ir,icol));
            res=min(res,dp(il,i,inc)+dp(i,ir,icol)+1);
            res=min(res,dp(il,i,icol)+dp(i,ir,inc)+1);
            //for each(inc2,26)
            //{
            //    res=min(res,dp(il,i,inc)+dp(i,ir,inc2)+2);
            //}
        }
    }
    return tdp[il][ir][icol]=res;
}
int main()
{
    freopen("1260.in","r",stdin);
    freopen("1260.out","w",stdout);
    memset(tdp,-1,sizeof tdp);
    char tc[109];
    scanf("%s",&tc[1]);
    int n=strlen(&tc[1]);
    for each(i,n)
    {
        indata[i]=tc[i]-'A'+1;
    }
    int res=99999999;
    for each(icol,26)
    {
        res=min(res,dp(1,n+1,icol));
    }
    cout<<res+1<<endl;
}
