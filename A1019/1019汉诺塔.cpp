#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=n;++i)
inline long long power(int a,int b)
{
    return (long long)pow((long double)a,b);
}
int varr[720]={3,3,3,3,3,3,1,2,1,1,2,2,3,3,1,1,3,1,3,3,2,2,3,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,2,1,1,2,2,1,2,1,1,2,2,1,1,1,1,1,1,2,2,2,2,2,2,3,3,1,1,3,1,3,3,3,3,3,3,1,1,1,1,1,1,3,1,3,3,1,1,3,3,2,2,3,2,3,3,3,3,3,3,2,2,2,2,2,2,3,2,3,3,2,2,3,1,3,3,1,1,3,2,3,3,2,2,3,3,3,3,3,3,1,1,2,2,1,2,3,1,3,3,1,1,3,1,3,3,1,1,3,3,3,3,3,3,1,1,1,1,1,1,3,2,3,3,2,2,3,2,3,3,2,2,3,3,3,3,3,3,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,2,2,1,2,1,1,1,1,1,1,2,2,2,2,2,2,1,2,1,1,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,1,1,3,1,3,3,1,1,3,3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,1,3,3,1,1,3,3,3,3,3,3,3,3,1,1,3,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,3,3,1,1,3,1,3,3,1,1,3,1,1,2,1,1,2,2,1,2,1,1,2,2,1,1,1,1,1,1,2,2,2,2,2,2,3,2,3,3,2,2,3,2,3,3,2,2,3,3,3,3,3,3,2,2,2,2,2,2,1,2,1,1,2,2,3,2,3,3,2,2,1,1,3,3,1,3,2,2,2,2,2,2,1,1,1,1,1,1,3,3,3,3,3,3,1,1,3,3,1,3,1,1,3,3,1,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,1,1,3,1,3,3,3,3,3,3,1,1,1,1,1,1,3,1,3,3,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,1,1,3,3,1,3,1,1,3,3,1,3,3,1,3,3,1,1,3,3,3,3,3,3,3,3,3,3,3,3,1,1,3,3,1,3,3,3,2,2,3,2,3,3,3,3,3,3,2,2,2,2,2,2,3,2,3,3,2,2,1,1,2,2,1,2,1,1,1,1,1,1,2,2,2,2,2,2,1,2,1,1,2,2,3,3,3,3,3,3,1,1,1,1,1,1,3,3,1,1,3,1,3,3,1,1,3,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,2,3,3,2,2,1,2,1,1,2,2,3,3,1,1,3,1,2,2,2,2,2,2};
//int t1[7]={0,1,1,2,2,3,3};
//int t2[7]={0,2,3,1,3,1,2};
string ts[7]={};
int trr[7]={0,1,2,3,4,5,6};
string yts[7]={"","AB","AC","BA","BC","CA","CB"};
string input[7]={};
//int yt1[7]={0,1,1,2,2,3,3};
//int yt2[7]={0,2,3,1,3,1,2};
inline bool testing()
{
    for each(i,6)
    {
        if(ts[i]!=input[i])return false;
    }
    return true;
}
int main()
{
    freopen("1019.in","r",stdin);
    freopen("1019.out","w",stdout);
    int n;cin>>n;
    int tp=0;
    long long tn[4]={0,power(2,n)-1,
    power(3,n-1),
    power(3,n-1)*2-1};
    //cout<<tn1<<","<<tn2<<","<<tn3<<endl;
    for each(i,6)cin>>input[i];
    if(testing())
    {
        cout<<tn[varr[tp]];
        return 0;
    }
    while(next_permutation(trr+1,trr+7))
    {
        tp++;
        for each(i,6)
        {
            ts[i]=yts[trr[i]];
            //t2[i]=yt2[trr[i]];
        }
        if(testing())
        {
            cout<<tn[varr[tp]];
            break;
        }
    }
}
