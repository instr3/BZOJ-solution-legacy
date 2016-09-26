#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=n;++i)
struct vnode{int to,w;}myv[1000];
bool dealing[1000];
int height[1000],phei;
int tcountarr[1000],tnc;
int tmpcalc[300][300];
int initcalc[300][300];
int res[300][300];
int diearr[3][4]={        1 ,3 ,10 ,11,
        2 ,7 ,8 ,9,
        4 ,5 ,6 ,12};
int tbase=0;
int tmax;

int n,nm;
void killpoint(int iv)
{
    dealing[iv]=true;
    myv[myv[iv].to].w--;
    height[iv]=++phei;
    for(int i=1;i<=nm;++i)
    res[iv][i]=tmax--;
    //cout<<"killed "<<iv<<" for "<<phei<<endl;
    if(myv[myv[iv].to].w==0)killpoint(myv[iv].to);
}
int count(int iv,int dp=1)
{
    dealing[iv]=true;
    tcountarr[dp]=iv;
    if(!dealing[myv[iv].to])return count(myv[iv].to,dp+1);
    return dp;
}
void calculate(int in,int im)
{
    if(in==3&&im==4)
    {
        for each(i,3)
        for each(j,4)
        {
            tmpcalc[i][j]=diearr[i-1][j-1];
            res[tcountarr[i]][j]=tbase+tmpcalc[i][j];
        }
        return;
    }
    //cout<<in<<","<<im<<endl;
    int tn=min(in,im);
    for(int i=1;i<=in;++i){
    for(int j=1;j<=im;++j)
    {
        if(i%tn==j%tn)
        initcalc[i][j]=1;
        //cout<<initcalc[i][j]<<" ";
    }//cout<<endl;
    }
    int tb,ts;
    for(int j=1;j<=im;++j)
    {
        tb=in*j;ts=in*(j-1)+1;
        for(int i=1;i<=in;++i)
        {
            
            if(initcalc[i][j])
            tmpcalc[i][j]=ts++;
            else
            tmpcalc[i][j]=tb--;
            res[tcountarr[i]][j]=tbase+tmpcalc[i][j];
            //cout<<tmpcalc[i][j]<<" ";
        }//cout<<endl;
    }
}
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    scanf("%d%d",&n,&nm);
    tmax=n*nm;
    int pt;
    for each(i,n)
    {
        scanf("%d",&pt);
        myv[i].to=pt;
        myv[pt].w++;
    }
    for each(i,n)
    {
        if(!dealing[i]&&myv[i].w==0)killpoint(i);
    }
    for each(i,n)
    {
        if(!dealing[i])
        {
            tnc=count(i);
            if(tnc==2)
            {
                cout<<"0";
                return 0;
            }
            //cout<<"Count:"<<tnc<<endl;
            calculate(tnc,nm);
            tbase+=tnc*nm;
        }
    }
    for each(i,n){
    for each(j,nm){
    cout<<res[i][j]<<" ";
}cout<<endl;
}
}
