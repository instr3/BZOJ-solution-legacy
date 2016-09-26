#include <cstdio>
#include <algorithm>
#include <iostream>
#define rep(i,n) for(int i=0;i<n;i++)
const int inf=~0U>>1,maxn=10000+10;
using namespace std;
char C[maxn];
int Dp[maxn][2],now,c;//0=green 1=other
int dfs()
{
    int tmp=++now,ch,ch1,ch2;
    switch(C[tmp])
    {
        case '0':
            Dp[tmp][0]=c;Dp[tmp][1]=0;break;
        case '1':
            ch=dfs();Dp[tmp][0]=Dp[ch][1]+c;
            Dp[tmp][1]=max(Dp[ch][1],Dp[ch][0]);break;
        case '2':
            ch1=dfs();ch2=dfs();
            Dp[tmp][0]=Dp[ch1][1]+Dp[ch2][1]+c;
            Dp[tmp][1]=max(Dp[ch1][0]+Dp[ch2][1],Dp[ch1][1]+Dp[ch2][0]);break;
    }
    return tmp;
}
int Cal(int _c)
{
    c=_c;now=-1;
    int root=dfs();
    return max(Dp[root][0],Dp[root][1]);
}
int main()
{
    //freopen("in","r",stdin);
    gets(C);
    cout<<Cal(1)<<" "<<-Cal(-1)<<endl;
}



