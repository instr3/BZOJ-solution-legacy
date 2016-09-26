#include <stdio.h>
#include <iostream>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define fc(a,b) (tdp[(a)+1][(b)+1])
int tdp[103][103];
void prec()
{
    tdp[1][1]=1;
    for every(i,2,102)
    for every(j,1,i)
    {
        tdp[i][j]=(tdp[i-1][j]+tdp[i-1][j-1])%2007;
    }
}
void task()
{
    int n;scanf("%d",&n);
    int tot=0,tres;
    for each(i,n)
    {
        tres=(i*4*fc(n,i))%2007;
        for each(j,n-i)
        {
            tres=(tres*4)%2007;
        }
        tot=(tot+tres)%2007;
    }
    printf("%d\n",tot);
}
int main()
{
    prec();
    int nt;scanf("%d",&nt);
    for each(i,nt)task();
    //system("pause");
}
    
