#include <iostream>
//#include <cstdlib>
#include <cmath>
//#include <cstring>
//#include <cstdio>
//#include <algorithm>
using std::cin;
using std::cout;
using std::sqrt;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
int tdata[100001];int ptd;
int n,nm;
inline long long mypow(long long in,long long ip)
{
    long long res=1;
    while(ip)
    {
        if(ip%2)
        {
            res=res*in;
        }
        in=in*in;
        ip/=2;
    }
    return res;
}
long long dfs(long long ip,long long inum)
{
    
    if(ip>ptd)
    {
        //if(inum==1)return 0;
        //cout<<"Test:"<<nm/inum<<","<<n<<":"<<mypow(nm/inum,n)<<endl;
        return mypow(nm/inum,n);
    }
    long long res=dfs(ip+1,inum)-dfs(ip+1,inum*tdata[ip]);
    //cout<<ip<<","<<inum<<":"<<res<<endl;
    return res;
}
int main()
{
    freopen("1220.in","r",stdin);
    freopen("1220.out","w",stdout);
    cin>>n>>nm;
    //nm=4;
    long long tnm=nm;
    if(nm>100000)return 1/0;
    //n=2;
    long long tsm=((long long)sqrtl(tnm)+1);
    for every(i,2,tsm)
    {
        if(tnm%i==0)
        {
            tdata[++ptd]=i;
            while(tnm%i==0){tnm/=i;}--i;
        }
    }
    if(tnm-1)tdata[++ptd]=tnm;
    /*for each(i,ptd)
    {
        cout<<tdata[i]<<endl;
    }*/
    cout<<dfs(1,1);
}
