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
int randint(int imin,int imax)
{
    int res=(int)(rand()%(imax-imin+1)+imin);
    return res;
}
int main()
{
    freopen("1562.in","w",stdout);
    int n=10000;
    cout<<n<<endl;
    for each(i,n)
    {
        cout<<randint(1,3)<<" ";
    }
}
