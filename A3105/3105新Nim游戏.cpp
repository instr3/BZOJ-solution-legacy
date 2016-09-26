#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n,ind[101];
int tarr[101];
int tta[101];
bool solve(int in,int ires)
{
    for each(i,in)
    {
        tta[i]=tarr[i];
        //cout<<tta[i]<<" ";
    }
    //cout<<ires<<endl;
    int tmax=0,tmaxat;
    while(true)
    {
        tmax=0;tmaxat=-99999999;
        for each(i,in)
        {
            if(tta[i]>tmax)
            {
                tmax=tta[i];
                tmaxat=i;
            }
        }
        if(tmax==0)return false;
        tta[tmaxat]=-1;
        for each(i,in)
        {
            if(tta[i]!=-1)
            {
                if((tta[i]^tmax)<tta[i])tta[i]^=tmax;
            }
        }
        if((ires^tmax)<ires)ires^=tmax;
        if(ires==0)return true;
    }
}
int main()
{
    freopen("3105.in","r",stdin);
    freopen("3105.out","w",stdout);
    long long tot=0;
    scanf("%d",&n);for each(i,n)scanf("%d",&ind[i]),tot+=ind[i];
    sort(ind+1,ind+n+1,greater<int>());
    int tn=0;
    for each(i,n)
    {
        if(!solve(tn,ind[i]))
        {
            tarr[++tn]=ind[i];
        }
    }
    for each(i,tn)
    {
        tot-=tarr[i];
    }
    cout<<tot<<endl;
    
}
