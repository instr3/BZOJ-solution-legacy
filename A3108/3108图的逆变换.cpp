#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n,nm;
bool map[301][301];
bool tunion[301][301];
void task()
{
    scanf("%d%d",&n,&nm);
    memset(map,0,sizeof map);
    memset(tunion,0,sizeof tunion);
    int pf,pt;
    for each(i,nm)
    {
        scanf("%d%d",&pf,&pt);
        map[pf+1][pt+1]=1;
    }
    for each(i,n)
    {
        for each(j,n)
        {
            for each(k,n)
            {
                if(map[i][k]&&map[j][k])
                {
                    tunion[i][j]=tunion[j][i]=true;
                }
            }
        }
    }
    for each(i,n)
    {
        for each(j,n)
        {
            if(!tunion[i][j])continue;
            for each(k,n)
            {
                if(map[i][k]^map[j][k])
                {
                    //cout<<i<<","<<j<<","<<k<<endl;
                    printf("No\n");
                    return;
                }
            }
        }
    }
    printf("Yes\n");
}
int main()
{
    freopen("3108.in","r",stdin);
    freopen("3108.out","w",stdout);
    int nt;
    scanf("%d",&nt);
    for each(i,nt)task();
}
