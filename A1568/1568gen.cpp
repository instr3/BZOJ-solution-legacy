#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iomanip>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
inline int randint(int il,int ir)
{
    return (rand()+65535*rand())%(ir-il+1)+il;
}
inline double randdb(int il,int ir)
{
    return (rand()/65535.0l)*(ir-il+1)+il;
}
int n=100000;
int main()
{
    freopen("1568.in","w",stdout);
    srand(11);
    printf("%d\n",n);
    int top;
    for each(i,n)
    {
        top=randint(1,2);
        if(top==1)
        {
            cout<<"P "<<setprecision(10)<<randdb(-1000000,1000000)<<" "<<randdb(0,100)<<endl;
        }
        else
        {
            cout<<"Q "<<randint(1,50000)<<endl;
        }
    }
}
