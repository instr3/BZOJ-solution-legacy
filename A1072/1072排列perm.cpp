#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
char mys[11];
int n,nd;
//极高效率搜索 
void task()
{
    memset(mys,0,sizeof(mys));
    scanf("%s%d",&mys[1],&nd);
    n=strlen(mys+1);
    sort(mys+1,mys+n+1);
    for each(i,n)mys[i]-='0';
    long long r;int tot=0;
    do
    {
        r=0;
        for each(i,n)
        {
            r=(r*10+mys[i]);
        }
        if(r%nd==0)tot++;
    }while(next_permutation(mys+1,mys+n+1));
    printf("%d\n",tot);
}
int main()
{
    freopen("1072.in","r",stdin);
    freopen("1072.out","w",stdout);
    int nt;scanf("%d",&nt);
    for each(i,nt)
    task();
}
