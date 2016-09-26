#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
long long nlim,nd,nup,nmod;
long long fastmul(long long ib,long long in)
{
    long long res=1;
    while(in)
    {
        if(in%2)
        res=(res*ib)%nmod;
        ib=(ib*ib)%nmod;
        in/=2;
    }
    return res;
}

int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    //scanf("%d%d%d%d",&nlim,&nd,&nup,&nmod);
    cin>>nlim>>nd>>nup>>nmod;
    nmod*=2;
    cout<<((((nup+1)*(nd-1)+(nlim-(nup+1)*(nd-1))*2))%nmod*fastmul(nup,nd-1))%nmod/2<<endl;
}
