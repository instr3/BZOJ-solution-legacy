#include <iostream>
#include <cstring>
#include <cstdlib>
//#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
int n;
int indata[10001];
int tmin[10001];
int tres[10001];
int tminat[10001],tpre[10001];
int nm;
int main()
{
    freopen("1046.in","r",stdin);
    freopen("1046.out","w",stdout);
    scanf("%d",&n);for each(i,n)scanf("%d",&indata[n+1-i]);
    int tl,tr,tm;
    for each(i,n)
    {
        tl=0,tr=n+1;
        while(tl+1!=tr)
        {
            tm=(tl+tr)>>1;
            if(tmin[tm]<=indata[i])
            {
                tr=tm;
            }
            else
            {
                tl=tm;
            }
        }
        tres[i]=tl+1;
        tpre[i]=tminat[tl];
        //tmin[tres[i]]=max(indata[i],tmin[tres[i]]);
        if(tmin[tres[i]]<=indata[i])
        {
            tmin[tres[i]]=indata[i];
            tminat[tres[i]]=i;
        }
        //cout<<tmin[i]<<" ";
    }
    //for each(i,n)cout<<tres[i]<<" ";
    scanf("%d",&nm);
    int tk;
    int tlast;
    for each(i,nm)
    {
        scanf("%d",&tk);
        tlast=-99999999;
        for(int j=n;j>=1;--j)
        {
            if(tres[j]>=tk&&tlast<indata[j])
            {
                /*for(int ip=j,ik=1;ik<=tk;ik++,ip=tpre[ip])
                {
                    printf("%d ",indata[ip]);
                }
                printf("\n");
                goto die;*/

                if(tk==1)
                {
                    printf("%d\n",indata[j]);
                    goto die;
                }
                printf("%d ",indata[j]);--tk;
                tlast=indata[j];
            }
        }
        printf("Impossible\n");
        die:;
    }
}
