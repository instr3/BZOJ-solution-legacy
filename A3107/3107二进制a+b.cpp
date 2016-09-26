#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int na,nb,nc;
int tca,tcb,tcc,tcm;
int n;
int tn;
unsigned tmax;
int tup;
int tna[32],tnb[32];
inline int fcount1(int in)
{
    int res=0;
    while(in)
    {
        if(in%2)res++;
        in/=2;
    }
    return res;
}
unsigned tdp[33][33][33][33][2];
int main()
{
    freopen("3107.in","r",stdin);
    freopen("3107.out","w",stdout);
    scanf("%d%d%d",&na,&nb,&nc);
    tn=0;
    while(na)
    {
        if(na%2)
        {
            tca++;
        }
        tn++;
        na/=2;
    }
    n=max(n,tn);
    tn=0;
    while(nb)
    {
        if(nb%2)
        {
            tcb++;
        }
        tn++;
        nb/=2;
    }
    n=max(n,tn);
    tn=0;
    while(nc)
    {
        if(nc%2)tcc++;
        tn++;
        nc/=2;
    }
    n=max(n,tn);
    tup=tca+tcb-tcc;
    tmax=1;
    for each(i,n)tmax=tmax*2;--tmax;
    tcm=max(tca,tcb);
    memset(tdp,127,sizeof tdp);
    tdp[0][1][1][1][0]=0;
    int tadd=1;
    for each(i,n)
    {
        for each(ica,tca+1)
        {
            for each(icb,tcb+1)
            {
                for each(icc,tcc+1)
                {
                    #define gmin(a,b) a=min(a,b)
                    gmin(tdp[i][ica][icb][icc][0],tdp[i-1][ica][icb][icc][0]);
                    gmin(tdp[i][ica][icb][icc][0],tdp[i-1][ica-1][icb][icc-1][0]+tadd);
                    gmin(tdp[i][ica][icb][icc][0],tdp[i-1][ica][icb-1][icc-1][0]+tadd);
                    gmin(tdp[i][ica][icb][icc][1],tdp[i-1][ica-1][icb-1][icc][0]);
                    
                    gmin(tdp[i][ica][icb][icc][0],tdp[i-1][ica][icb][icc-1][1]+tadd);
                    gmin(tdp[i][ica][icb][icc][1],tdp[i-1][ica-1][icb][icc][1]);
                    gmin(tdp[i][ica][icb][icc][1],tdp[i-1][ica][icb-1][icc][1]);
                    gmin(tdp[i][ica][icb][icc][1],tdp[i-1][ica-1][icb-1][icc-1][1]+tadd);
                    //cout<<i<<","<<ica-1<<","<<icb-1<<","<<icc-1<<":"<<tdp[i][ica][icb][icc][1]<<endl;
                }
            }
        }
        tadd<<=1;
    }
    if(tdp[n][tca+1][tcb+1][tcc+1][0]>tmax)printf("-1");
    else
    printf("%d",tdp[n][tca+1][tcb+1][tcc+1][0]);
                    
                    
                
    /*
    int res=0;
    if(tup<0)
    {
        printf("-1");return 0;
    }
    if(tup==0)
    {
        res=(1<<(tca+tcb))-1;
        if(res>tmax)printf("-1");else
        printf("%d",res);
        return 0;
    }
    int res2=1999999999;
    int tnva=(1<<(tca))-1,tnvb=(1<<(tcb))-1;
    int tget;
    for(int ia=tnva;ia<=tmax;ia<<=1)
    {
        for(int ib=tnvb;ib<=tmax;ib<<=1)
        {
            tget=ia+ib;
            
            if(tget>tmax)continue;
            //cout<<ia<<","<<ib<<","<<fcount1(tget)<<","<<tcc<<endl;
            if(fcount1(tget)==tcc)
            {
                res2=min(res2,tget);
            }
        }
    }
    if(tcm>=tup)
    {
        for each(i,tup)
        {
            if(tca&&tcb)
            {
                tna[i]=1;tnb[i]=1;tca--;tcb--;
            }
            else if(tca)
            {
                tna[i]=1;
                tca--;
            }
            else
            {
                tnb[i]=1;
                tcb--;
            }
        }
        for every(i,tup+2,n)
        {
            if(tca==0&&tcb==0)break;
            if(tca)
            {
                tna[i]=1;--tca;
            }
            else
            {
                tnb[i]=1;--tcb;
            }
        }
        if(tca||tcb){printf("-1");return 0;}
    }
    else
    {
        int tvar=tca+tcb-tup;
        if(tvar<=1)
        {
            printf("-1");return 0;
        }
        for each(i,tvar)
        {
            tna[i]=tnb[i]=1;
        }
        for every(i,tvar+1,tup)tna[i]=1;
    }
    for each(i,n)
    {
        //cout<<tnb[i]<<" ";
        res=res+(tna[i]+tnb[i])*(1<<(i-1));
    }
    if(res>tmax)printf("-1");else printf("%d",min(res,res2));
    */
}
