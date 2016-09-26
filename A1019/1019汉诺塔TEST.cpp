#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=n;++i)
#define o(p) //p
int t1[7]={0,1,1,2,2,3,3};
int t2[7]={0,2,3,1,3,1,2};
int trr[7]={0,1,2,3,4,5,6};
int yt1[7]={0,1,1,2,2,3,3};
int yt2[7]={0,2,3,1,3,1,2};
int n;
int mys[4][1001],pmys[4];
int task()
{
    int tlast=0,tc;
    for each(i,n) mys[1][i]=n+1-i;
    pmys[1]=n;    
    pmys[2]=pmys[3]=0;
    for each(i,3) mys[i][0]=99999999;
    for each(k,99999999)
    {
        for each(j,6)
        {
            if(t1[j]!=tlast&&mys[t1[j]][pmys[t1[j]]]<mys[t2[j]][pmys[t2[j]]])
            {
                mys[t2[j]][++pmys[t2[j]]]=mys[t1[j]][pmys[t1[j]]--];
o(
                for each(i,3)
                {
                    cout<<i<<":";
                    for each(u,pmys[i])
                    {
                        cout<<mys[i][u]<<" ";
                    }
                    cout<<endl;
                }
)
                tlast=t2[j];
                break;
            }
        }
        tc=0;
        if(pmys[1]==0)tc++;
        if(pmys[2]==0)tc++;
        if(pmys[3]==0)tc++;
        if(pmys[1]==0&&tc==2)
        {
            return (k==31)?1:((k==81?2:3));
            //return k;
        }
    }
    return -1;
}
int main()
{
    freopen("1019.in","r",stdin);
    freopen("1019.out","w",stdout);
    cin>>n;
    cout<<task()<<",";
    while(next_permutation(trr+1,trr+7))
    {
        for each(i,6)
        {
            t1[i]=yt1[trr[i]];
            t2[i]=yt2[trr[i]];
        }
        cout<<task()<<",";
    }
}
            
