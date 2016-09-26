#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
int n;long long nt,tnt;
int tdata[100001];
int trdata[100001];
int tout[200001];
int tarr[70];int pta;
inline void gettarr()
{
    while(tnt)
    {
        tarr[pta++]=tnt%2;
        tnt/=2;
    }
    pta--;
}
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    scanf("%d",&n);
    cin>>nt;
    tnt=nt;
    gettarr();
    for each(i,n)
    {
        scanf("%d",&tdata[i]);
        --tdata[i];
    }
    long long trotate;
    for(int k=pta;k>=0;--k)
    {
        if(!tarr[k])continue; 
        trotate=((long long)1)<<k;
        rotate_copy(tdata+1,tdata+1+trotate%n,tdata+n+1,trdata+1);
        //cout<<trotate<<":";
        //for each(i,n)cout<<trdata[i]<<" ";
        //cout<<endl;
        for each(i,n)tdata[i]^=trdata[i];
    }
    for each(i,n)tout[2*i-1]=tdata[i]+1;
    int zn=2*n;
    for each(i,zn-1)printf("%d ",tout[((i-nt)%zn+zn-1)%zn+1]);
    printf("%d",tout[((zn-nt)%zn+zn-1)%zn+1]);
    //for each(i,14)cout<<i<<":"<<lowbit(i)<<endl;
    /*
    for each(i,n)
    {
        scanf("%d",&tdata[0][i]);
        cout<<(tdata[0][i]==2?'Z':'1')<<" ";
    }cout<<endl;
    for each(j,nt)
    {
        if(lowbit(j)==j){cout<<j<<":";if(j%2)cout<<" ";}
        for each(i,n)
        {
            //if(j%2)
            tdata[j][i]=(tdata[j-1][i]!=tdata[j-1][i%n+1])+1;
            //else tdata[j][i]=(tdata[j-1][(i+n-2)%n+1]!=tdata[j-1][i])+1;
            if(lowbit(j)!=j)continue;
            cout<<(tdata[j][i]==2?'Z':'1')<<" ";
            
        }
        if(lowbit(j)==j)cout<<endl;
    }*/
}
