#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
int n;//=100;
string mys;//="1abcdefabcdefabcdefabcdefabcdefabcdef";
int tdp[101][101];
int dp[101][101];
int pretask(int lt=0,int rt=n-1)
{
    //int res=1;
    if(tdp[lt][rt])return tdp[lt][rt];
    int tlen=rt-lt+1,tnlen;
    string tinit;
    for(int k=2;k<=tlen;++k)
    {
        if(tlen%k==0)
        {
            tnlen=tlen/k;
            tinit=mys.substr(lt,tnlen);
            for(int j=0;j<=tlen-1;++j)
            {
                if(tinit[j%tnlen]!=mys[lt+j])goto returnfalse;
            }
            return tdp[lt][rt]=k*pretask(lt,lt+tnlen-1);
        }
        returnfalse:;
    }
    return tdp[lt][rt]=1;
}
int task(int lt=0,int rt=n-1)
{
    if(lt==rt)return 1;
    if(dp[lt][rt])return dp[lt][rt];
    int tlen=rt-lt+1;
    int res=min(tlen,2+1+(int)log10(tdp[lt][rt])+tlen/tdp[lt][rt]);
    if(tdp[lt][rt]>1)
    res=min(res,2+1+(int)log10(tdp[lt][rt])+task(lt,lt+tlen/tdp[lt][rt]-1));
    for(int i=lt;i<rt;++i)
    {
        res=min(res,task(lt,i)+task(i+1,rt));
    }
    
    return dp[lt][rt]=res;
}
int main()
{
    freopen("1090.in","r",stdin);
    freopen("1090.out","w",stdout);
    cin>>mys;
    n=mys.size();
    for(int i=0;i<=n;++i)
    for(int j=i;j<=n;++j)
    {
        pretask(i,j);
        //if(pretask(i,j)>1)
        {
            //cout<<i<<","<<j<<":"<<pretask(i,j)<<":"<<mys.substr(i,j-i+1)<<endl;
        }
    }
    cout<<task(0,n-1);
}
