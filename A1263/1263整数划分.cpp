#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
typedef int bignum[5010];
inline void dec0(bignum &ia)
{
    while(ia[0]&&(ia[ia[0]]==0))ia[0]--;
}
void print(bignum &ia)
{
    int ii=0;
    for(int i=ia[0];i>=1;--i)
    {
        printf("%d",ia[i]);
        ii++;
        if(ii>=100)return;
    }
}
void mul(bignum &ia,int ib)
{
    for(int i=ia[0];i>=1;--i)
    {
        ia[i]*=ib;
    }
    ia[0]+=8;
    for(int i=1;i<=ia[0];++i)
    {
        ia[i+1]+=ia[i]/10;
        ia[i]%=10;
    }
    
    dec0(ia);
}
bignum ans;
int main()
{
    freopen("1263.in","r",stdin);
    freopen("1263.out","w",stdout);
    ans[0]=1;ans[1]=1;
    int n;scanf("%d",&n);
    while(n>4){mul(ans,3);n-=3;}
    mul(ans,n);
    cout<<ans[0]<<endl;
    print(ans);
    
}
