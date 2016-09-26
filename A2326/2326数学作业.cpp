#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
long long n;int nmod;
struct mat3x3
{
    int d[4][4];
    void print()
    {
        for each(i,3)
        {
            for each(j,3)
            {
                cout<<d[i][j]<<",";
            }
            cout<<endl;
        }
    }
};
struct mat1x3
{
    int d[4];
};
inline mat3x3 operator *(mat3x3 ia,mat3x3 ib)
{
    mat3x3 ir={};
    for each(i,3)
    {
        for each(j,3)
        {
            for each(k,3)
            {
                ir.d[i][j]=(ir.d[i][j]+ia.d[i][k]*(long long)ib.d[k][j])%nmod;
            }
        }
    }
    return ir;
}
inline mat1x3 operator *(mat1x3 ia,mat3x3 ib)
{
    mat1x3 ir={};
    for each(j,3)
    {
        for each(k,3)
        {
            ir.d[j]=(ir.d[j]+ia.d[k]*(long long)ib.d[k][j])%nmod;
        }
    }
    return ir;
}
inline mat3x3 matpow(mat3x3 ia,long long ip)
{
    mat3x3 ir={};
    ir.d[1][1]=ir.d[2][2]=ir.d[3][3]=1;
    while(ip)
    {
        if(ip%2)
        {
            ir=ir*ia;
        }
        ia=ia*ia;
        ip/=2;
    }
    return ir;
}
mat1x3 res={0,0,1,1};
mat3x3 tmat;
int nlog;
long long tm10[19];
long long tm9[19];
int main()
{
    freopen("2326.in","r",stdin);
    freopen("2326.out","w",stdout);
    cin>>n>>nmod;
    nlog=1;
    long long tn=n;
    while(tn/=10)nlog++;
    tm10[0]=1;
    //cout<<nlog<<endl;
    for each(i,nlog)
    {
        tm10[i]=tm10[i-1]*10LL;
        //cout<<(tm10[i])<<" ";
    }
    tm9[1]=9;
    for every(i,2,nlog)
    {
        tm9[i]=tm9[i-1]*10;
    }
    tmat.d[2][1]=1;
    tmat.d[2][2]=1;
    tmat.d[3][2]=1;
    tmat.d[3][3]=1;
    for each(k,nlog-1)
    {
        tmat.d[1][1]=tm10[k]%nmod;
        //tmat.print();
        res=res*matpow(tmat,tm9[k]);
        
        //cout<<res.d[1]<<","<<res.d[2]<<","<<res.d[3]<<endl;
    }
    tmat.d[1][1]=tm10[nlog]%nmod;
    //cout<<n-tm10[nlog-1]+1<<endl;
    res=res*matpow(tmat,n-tm10[nlog-1]+1);
    printf("%d",res.d[1]);
}
