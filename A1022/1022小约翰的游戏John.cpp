#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
inline void say(int done)
{
    if(done)printf("John\n");else printf("Brother\n");
}
void task()
{
    int n;
    bool all1=true;
    int data[1000];
    int res=0;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&data[i]);
        if(data[i]!=1)all1=false;
        res^=data[i];
    }
    if(all1)
    {
        say((n+1)%2);
    }
    else
    {
        say(res);
    }
}
int main()
{
    freopen("1022.in","r",stdin);
    freopen("1022.out","w",stdout);
    int N;scanf("%d",&N);
    for(int i=1;i<=N;++i)task();
}
