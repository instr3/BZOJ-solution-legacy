#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
//#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
int zmap[201][201];
int n;
bool visit[201];
bool zpath(int ix)
{
    for each(iy,n)
    {
        if(!zmap[ix][iy])continue;
        if(visit[iy])continue;
        visit[iy]=true;
        if(!zmap[0][iy])
        {
            zmap[ix][0]=iy;
            zmap[0][iy]=ix;
            return true;
        }
        else if(zpath(zmap[0][iy]))
        {
            zmap[ix][0]=iy;
            zmap[0][iy]=ix;
            return true;
        }
    }
    return false;
}
bool task()
{
    memset(zmap,0,sizeof zmap);
    scanf("%d",&n);
    for each(ix,n)
    for each(iy,n)
    {
        scanf("%d",&zmap[ix][iy]);
    }
    int tot=0;
    for each(ix,n)
    {
        memset(visit,0,sizeof(visit));
        if(zpath(ix))++tot;else return false;
    }
    return true;
}
int main()
{
    int tn;scanf("%d",&tn);
    for each(i,tn)
    if(task())cout<<"Yes"<<endl;else cout<<"No"<<endl;
    system("pause");
    
}
