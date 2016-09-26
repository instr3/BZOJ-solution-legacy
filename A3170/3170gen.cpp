#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(a) ((a)<0?-(a):(a))
inline int randint(int tl,int tr)
{
    return (rand()+rand()*65536LL)%(tr-tl+1)+tl;
}
int n=10000;
int main()
{
    freopen("3170.in","w",stdout);
    cout<<n<<endl;
    for each(i,n)
    {
        cout<<randint(-1000000000,1000000000)<<" "<<randint(-1000000000,1000000000)<<endl;
    }

}
