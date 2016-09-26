#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
//#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
int main()
{
    int n,nk;
    scanf("%d%d",&n,&nk);
    if(n==1){printf("1");return 0;}
    if(nk>(n+1)/2)nk=n+1-nk;
    printf("%d",2*nk);
    system("pause");
}
