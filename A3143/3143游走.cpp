#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
struct enode{int to,next;}mye[500002];
struct vnode{int first;}myv[501];
int tdegree[501];

#define double long double
double tade[501];
double mat[501][501];
double tres[501];
double twe[500002];
int n,nm;
inline void swapline(int il1,int il2)
{
    double tv;
    for every(j,0,n)
    {
        tv=mat[il1][j];
        mat[il1][j]=mat[il2][j];
        mat[il2][j]=tv;
    }
}
#define is0(a) (abs(a)<=1e-11)
int main()
{
    freopen("3143.in","r",stdin);
    freopen("3143.out","w",stdout);
    scanf("%d%d",&n,&nm);
    int pf,pt;
    for(int i=1,j=1;i<=nm;++i)
    {
        scanf("%d%d",&pf,&pt);
        mye[++j].to=pt;
        mye[j].next=myv[pf].first;myv[pf].first=j;
        
        mye[++j].to=pf;
        mye[j].next=myv[pt].first;myv[pt].first=j;
        tdegree[pf]++;
        tdegree[pt]++;
    }
    for each(i,n)tade[i]=1/(double)tdegree[i];
    mat[1][0]=-1;
    for each(iv,n-1)
    {
        mat[iv][iv]=-1;
        for(int p=myv[iv].first;p;p=mye[p].next)
        {
            pt=mye[p].to;
            mat[iv][pt]=tade[pt];
        }
    }
    
    mat[n][n]=1;
/*Convert To:
    A:X 0 0
    B:X Y 0
    C:X Y Z
    */
    double maxnum;int maxat;
    double tmul;
    for(int k=n;k>=1;--k)
    {
        maxnum=-1;maxat=-999999;
        for each(i,k)
        {
            if(abs(mat[i][k])>maxnum)
            {
                maxnum=abs(mat[i][k]);
                maxat=i;
            }
        }
        //cout<<k<<","<<maxnum<<","<<maxat<<endl;
        swapline(maxat,k);
        for each(i,k-1)
        {
            if(is0(mat[i][k]))continue;
            tmul=mat[i][k]/mat[k][k];
            for every(j,0,k)
            {
                mat[i][j]=mat[i][j]-mat[k][j]*tmul;
            }
        }
    }

    for each(k,n)
    {
        tmul=mat[k][0];
        for each(j,k-1)
        {
            tmul-=mat[k][j]*tres[j];
        }
        tres[k]=tmul/mat[k][k];
        //cout<<"Ans["<<k<<"]="<<tres[k]<<endl;
    }
    double tot=0;
    for each(im,nm)
    {
        pf=mye[im*2+1].to;
        pt=mye[im*2].to;
        twe[im]=tres[pf]*tade[pf]+tres[pt]*tade[pt];
        //cout<<"E["<<im<<"]="<<twe[im]<<endl;
    }
    sort(twe+1,twe+nm+1);
    for each(im,nm)tot+=(nm-im+1)*twe[im];
    
    /*for each(i,n)
    {
        cout<<mat[i][0]<<":";
        for each(j,n)
        {
            cout<<mat[i][j]<<" ";
        }
        printf("\n");
    }*/
    #undef double 
    printf("%.3f",(double)tot);
}
