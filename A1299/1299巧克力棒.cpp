#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <set>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)

int data[20];
void task()
{
    set<int> mys,mys2;
    bool iswin=false;
    int allxor=0;
    int n;scanf("%d",&n);
    mys.insert(0);
    for each(i,n)
    {
        scanf("%d",&data[i]);
        allxor^=data[i];
        for(set<int>::iterator p=mys.begin();
         p!=mys.end();p++)
        {
            if(data[i]==(*p))iswin=true;
            mys2.insert(data[i]^(*p));
        }
        for(set<int>::iterator p=mys2.begin();
         p!=mys2.end();p++)
        {
            mys.insert(*p);
        }
        for each(j,i-1)
        {
            if(data[i]==data[j])iswin=true;
        }
    }
    //if(allxor==0)iswin=true;
    if(!iswin)printf("YES\n");else printf("NO\n");
}
int main()
{
    freopen("1299.in","r",stdin);
    freopen("1299.out","w",stdout);
    for each(i,10)task();

}
