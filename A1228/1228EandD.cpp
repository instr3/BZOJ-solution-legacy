#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n;
//int indata[10001][2];
int indata1,indata2;
int getsg(int ia,int ib)
{
    //int tmax=(int)pow(2.0,(int)log2((double)max(ia,ib)-1));
    //return tmax;
    int res=0;--ia;--ib;
    while(ia||ib)
    {
        if(ia%2||ib%2)res++;else break;
        ia/=2;ib/=2;
    }
    return res;
}
inline void task()
{
    scanf("%d",&n);
    int tcount=0;
    int nd2=n/2;
    for each(i,nd2)
    {
        scanf("%d%d",&indata1,&indata2);
        tcount^=getsg(indata1,indata2);
    }
    //cout<<tcount<<endl;
    if(tcount)
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
}
/*int tres[1001][1001];
int visit[10001];
inline int test2(int inum)
{
    int res=0;
    while(inum%2==0)inum/=2,++res;
    return res;
}

void sgtest(int n)
{
    
    for each(it,n*2)
    {
        for each(i,it-1)
        {
            int j=it-i;
            //if(i==1&&j==1)continue;
            memset(visit,0,sizeof visit);
            for each(k,i-1)
            {
                visit[tres[k][i-k]]=true;
            }
            for each(k,j-1)
            {
                visit[tres[k][j-k]]=true;
            }
            for every(k,0,n*n)
            {
                if(visit[k]==0)
                {
                    tres[i][j]=k;
                    break;
                }
            }
        }
    }
    for each(i,n)
    {
        for each(j,n)
        {
            //cout<<tres[i][j]<<" ";
            cout<<getsg(i,j)<<" ";
            //cout<<max(max(test2(i),test2(j)),test2(i+j-1))<<" ";
        }
        cout<<endl;
    }
}*/
int main()
{
    freopen("1228.in","r",stdin);
    freopen("1228.out","w",stdout);
    int nt;scanf("%d",&nt);
    for each(i,nt)task();
    
}
