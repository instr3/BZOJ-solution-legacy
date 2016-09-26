#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int randint(int ia,int ib)
{
    return rand()%(ia-ib+1)+ia;
}
int n=10000;
int main()
{
    freopen("1876.in","w",stdout);
    for each(i,n)
    {
        printf("%d",randint(0,9));
    }
    cout<<endl;
    for each(i,n)
    {
        printf("%d",randint(0,9));
    }
}
