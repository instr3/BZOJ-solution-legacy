#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
//#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
char tc[1000003];
int dp[2][1000003][2];
int dend[1000003];
int getend(int ib)
{
    if(dend[ib])return dend[ib];
    if(tc[ib]=='1')return dend[ib]=getend(ib+1);
    if(tc[ib]=='0')return dend[ib]=ib;
    int res=getend(ib+1);
    return dend[ib]=getend(res+1);
}

int deal(int imax,int ib,int ie,int igreen)
{
    //cout<<imax<<","<<ib<<","<<ie<<","<<igreen<<endl;
    if(dp[imax][ib][igreen]!=-1)return dp[imax][ib][igreen];
    int tie=dend[ib+1];
    //cout<<tc[ib]<<":"<<tie<<endl;
    switch(tc[ib])
    {
        case '0':
            return dp[imax][ib][igreen]=igreen;
            break;
        case '1':
            if(imax)
            {
                if(igreen)return dp[1][ib][1]=deal(1,ib+1,ie,0)+1;
                else return dp[1][ib][0]=max(deal(1,ib+1,ie,1),deal(1,ib+1,ie,0));
            }
            else
            {
                if(igreen)return dp[0][ib][1]=deal(0,ib+1,ie,0)+1;
                else return dp[1][ib][0]=min(deal(0,ib+1,ie,0),deal(0,ib+1,ie,1));
            }
            break;
        case '2':
            if(imax)
            {
                if(igreen)return dp[1][ib][1]=deal(1,ib+1,tie,0)+deal(1,tie+1,ie,0)+1;
                else return dp[1][ib][0]=
                 max(deal(1,ib+1,tie,0)+deal(1,tie+1,ie,1),
                  deal(1,ib+1,tie,1)+deal(1,tie+1,ie,0));
            }
            else
            {
                if(igreen)return dp[0][ib][1]=deal(0,ib+1,tie,0)+deal(0,tie+1,ie,0)+1;
                else return dp[0][ib][0]=
                 min(deal(0,ib+1,tie,0)+deal(0,tie+1,ie,1),
                  deal(0,ib+1,tie,1)+deal(0,tie+1,ie,0));
            }
            break;
        default:;
    }
    cout<<"How do you get there?!"<<endl;
    return -123;
}
int main()
{
    freopen("4.in","r",stdin);
    freopen("4.out","w",stdout);
    memset(dp,-1,sizeof(dp));
    /*int n=0;
    while(!feof(stdin))
    {
        ttc=getchar();
        cout<<ttc<<endl;
        if(ttc<'0'||ttc>'2')break;
        tc[++n]=ttc;
    }
    return 0;*/
    //scanf("%s",&tc[1]);
    gets(&tc[1]);
    int n=strlen(&tc[1]);
    getend(1);
    //for each(i,n)cout<<getend(i)<<" ";
    //cout<<endl;
    cout<<max(deal(1,1,n,0),deal(1,1,n,1))<<endl<<
     min(deal(0,1,n,0),deal(0,1,n,1));
}
