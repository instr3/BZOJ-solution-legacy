#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define nmod 100003
int n;
int pow(long long a,long long b)
{
    a%=nmod;
    long long tm=a,ans=1;
    while(b)
    {
        if(b%2)
        {
            ans=(ans*tm)%nmod;
        }
        b/=2;
        tm=(tm*tm)%nmod;
    }
    return ans;
}
int main()
{
    freopen("1008.in","r",stdin);
    freopen("1008.out","w",stdout);
    long long na,nb;
    cin>>na>>nb;
    cout<<(pow(na,nb)+nmod-(pow(na-1,nb-1)*na)%nmod)%nmod;
    
}
                
