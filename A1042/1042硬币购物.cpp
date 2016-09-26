#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
%:define every_wi(i,a,b) (i=(a);i<=(b);++i)
//ÈÝ³âÔ­Àí  
int nt;
int nc[5];
int tc[5];
int tb[5];
long long tdp[200001];
long long res;
int main()
{
    freopen("1042.in","r",stdin);
    freopen("1042.out","w",stdout);
    for each(i,4)scanf("%d",&nc[i]);
    tdp[0]=1;
    for each(i,4)
    {
        for every(j,0,100000)
        {
            tdp[j+nc[i]]+=tdp[j];
        }
    }
    //cout<<tdp[900]<<endl;
    scanf("%d",&nt);
    int n;
    int tmak;
    int tn;
    for each(i,nt)
    {
        scanf("%d%d%d%d%d",&tc[1],&tc[2],&tc[3],&tc[4],&n);
        res=0;
        for every_wi(tb[1],0,1)
        for every_wi(tb[2],0,1)
        for every_wi(tb[3],0,1)
        for every_wi(tb[4],0,1)
        {
            tmak=0;
            tn=n;
            for each(i,4)
            {
                if(tb[i])
                {
                    tmak++;
                    tn-=(tc[i]+1)*nc[i];
                }
            }
            //cout<<tb[1]<<","<<tb[2]<<","<<tb[3]<<","<<tb[4]<<":"<<tn<<endl;
            if(tn<0)continue;
            res+=(tmak%2?-1:1)*tdp[tn];
        }
        printf("%lld\n",res);
    }
    
}
