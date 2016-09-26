#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <queue>
using namespace std;
int n1,n2,n3,n,nm,nmo;
int tdata[61];
bool visit[61];
int tpitem[61],pti;
int tdp[21][21][21];
int res;
int main()
{
    freopen("1004.in","r",stdin);
    freopen("1004.out","w",stdout);
    scanf("%d%d%d%d%d",&n1,&n2,&n3,&nm,&nmo);
    n=n1+n2+n3;
    int nmod=nmo*(nm+1);
    int tcount;
    for(int i=1;i<=nm;++i)
    {
        memset(visit,0,sizeof(visit));
        pti=0;
        for(int j=1;j<=n;++j)
        {
            scanf("%d",&tdata[j]);
        }
        for(int j=1;j<=n;++j)
        {
            if(!visit[j])
            {     
                tcount=0;
                for(int k=tdata[j];!visit[k];k=tdata[k])
                {
                    visit[k]=true;
                    tcount++;
                }
                tpitem[++pti]=tcount;
            }
        }
        memset(tdp,0,sizeof(tdp));
        tdp[0][0][0]=1;
        for(int j=1;j<=pti;++j)
        {
            for(int k1=n1;k1>=0;--k1)
            for(int k2=n2;k2>=0;--k2)
            for(int k3=n3;k3>=0;--k3)
            {
                if(k1-tpitem[j]>=0)
                tdp[k1][k2][k3]=(tdp[k1][k2][k3]+tdp[k1-tpitem[j]][k2][k3])%nmod;
                if(k2-tpitem[j]>=0)
                tdp[k1][k2][k3]=(tdp[k1][k2][k3]+tdp[k1][k2-tpitem[j]][k3])%nmod;
                if(k3-tpitem[j]>=0)
                tdp[k1][k2][k3]=(tdp[k1][k2][k3]+tdp[k1][k2][k3-tpitem[j]])%nmod;
            }
        }
        res=(res+tdp[n1][n2][n3])%nmod;
    }
    memset(tdp,0,sizeof(tdp));
    tdp[0][0][0]=1;
    for(int j=1;j<=n;++j)
    {
        for(int k1=n1;k1>=0;--k1)
        for(int k2=n2;k2>=0;--k2)
        for(int k3=n3;k3>=0;--k3)
        {
            if(k1-1>=0)
            tdp[k1][k2][k3]=(tdp[k1][k2][k3]+tdp[k1-1][k2][k3])%nmod;
            if(k2-1>=0)
            tdp[k1][k2][k3]=(tdp[k1][k2][k3]+tdp[k1][k2-1][k3])%nmod;
            if(k3-1>=0)
            tdp[k1][k2][k3]=(tdp[k1][k2][k3]+tdp[k1][k2][k3-1])%nmod;
        }
    }
    res=(res+tdp[n1][n2][n3])%nmod;
    //cout<<tdp[n1][n2][n3]<<endl;
    cout<<res/(nm+1)<<endl;
}
