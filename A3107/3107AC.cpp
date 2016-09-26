#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
using namespace std;
const int N=31;
int n,a,b,c,f[2][N][N][N][2];
inline int get(int x)
{
int s;
for(s=0;x;x>>=1)
if(x&1) s++;
return s;
}
void init()
{
int x,y,z;scanf("%d%d%d",&x,&y,&z);
    a=get(x);b=get(y);c=get(z);
    x=max(x,max(y,z));
    for(n=0;x;x>>=1) n++;
}
void work(int &a,int b)
{
    if(a==-1) a=b;
    else a=min(a,b);
}
int main()
{
    freopen("3107.in","r",stdin);
    freopen("3107.out","w",stdout);
    init();
    memset(f,-1,sizeof(f));
    f[0][0][0][0][0]=0;
    int cur=0;
    for(int t=0;t<n;t++,cur^=1)
        for(int i=0;i<=min(t,a);i++)
            for(int j=0;j<=min(t,b);j++)
                for(int k=0;k<=min(t,c);k++)
                {
                    if(f[cur][i][j][k][0]!=-1)
                    {
                        int now=f[cur][i][j][k][0];
                        work(f[cur^1][i][j][k][0],now);
                        if(i+1<=a&&k+1<=c) work(f[cur^1][i+1][j][k+1][0],now+(1<<t));
                        if(i+1<=a&&j+1<=b) work(f[cur^1][i+1][j+1][k][1],now);
                        if(j+1<=b&&k+1<=c) work(f[cur^1][i][j+1][k+1][0],now+(1<<t));
                    }
                    if(f[cur][i][j][k][1]!=-1)
                    {
                        int now=f[cur][i][j][k][1];
                        work(f[cur^1][i][j][k+1][0],now+(1<<t));
                        if(i+1<=a) work(f[cur^1][i+1][j][k][1],now);
                        if(j+1<=b) work(f[cur^1][i][j+1][k][1],now);
                        if(i+1<=a&&j+1<=b&&k+1<=c)work(f[cur^1][i+1][j+1][k+1][1],now+(1<<t));
                    }
                }               
    printf("%d\n",f[cur][a][b][c][0]);
}
