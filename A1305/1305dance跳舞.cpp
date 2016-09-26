#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
int tarr1[100],tarr2[100];
int main()
{
    
    int n,nk;scanf("%d%d",&n,&nk);
    char tc[100];
    for each(i,n)
    {
        scanf("%s",&tc[1]);
        for each(j,n)
        {
            if(tc[j]=='Y')
            tarr1[i]++,++tarr2[j];
        }
    }
    int res=999999;
    for each(i,n)
    {
        res=min(res,min(tarr1[i],tarr2[i]));
    }
    cout<<min(n,res+nk);
    system("pause");
}
