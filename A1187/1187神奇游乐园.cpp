#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
int n,nm;
int indata[102][9];
long long tdp[102][9][16384];
#define getpos(num,pos) ((bool)((num)&(1<<(pos))))
#define addpos(num,pos,iw) (num+=(iw<<(pos)))

#define get2pos(num,pos) (getpos((num),(pos))+(getpos((num),(pos)+1)<<1))
int tzarr[201];int pzarr;
int tzto[201][9];
inline int getnextpermutation(int &inz)
{
    int tct[9]={};
    int tcheck;
    while(true)
    {
        for each(i,n+1)
        {
            
            //cout<<getpos(inz,2*i-2)<<" ";
            //cout<<getpos(inz,2*i-1)<<endl;
            if(get2pos(inz,2*i-2)<=1)
            {
                addpos(inz,2*i-2,1);
                break;
            }
            else
            {
                addpos(inz,2*i-1,-1);
            }
            //if(inz&(1<<(2*i-2)))
        }
        //
        tcheck=0;
        for each(i,n+1)
        {
            tzto[pzarr+1][i]=0;
            if(get2pos(inz,2*i-2)==1)
            {
                ++tcheck;
                tct[tcheck]=i;
            }
            if(get2pos(inz,2*i-2)==2)
            {
                tzto[pzarr+1][tct[tcheck]]=i;
                tzto[pzarr+1][i]=tct[tcheck];
                --tcheck;
            }
            if(tcheck<0)goto die;
        }
        if(tcheck!=0)goto die;
        break;
        die:;
    }
    tzarr[++pzarr]=inz;
    //cout<<inz<<endl;
    return inz;
}
void printz(int iz)
{
    for each(i,n+1)
    {
        switch(get2pos(iz,2*i-2))
        {
            case 0:cout<<"#";break;
            case 1:cout<<"(";break;
            case 2:cout<<")";break;
            default:cout<<"E";break;
        }

    }
    cout<<endl;
}
//ÒÔÉÏinit 
#define fisl(iz,ik) (tzto[(iz)][(ik)]>(ik))
#define testmin(a,b) (a)=max((a),(b))
inline int encode(int *iarr)
{
    int tz=0;
    for(int k=n+1;k>=1;--k)
    {
        tz<<=2;
        tz^=iarr[k];
    }
    return tz;
}
long long minres=-199999999;
void dp()
{
    int tz;
    int tarr[9]={};
    int tva[9]={};
    for each(im,nm)
    {
        for each(i,n)
        {
            for each(iz,pzarr)
            {
                tz=tzarr[iz];
                for each(k,n+1)
                {
                    tarr[k]=tz&3;
                    tva[k]=tarr[k];
                    //cout<<tarr[k]<<" ";
                    tz>>=2;
                }
                //if(i>1)
                {
                    if(tarr[i]&&tarr[i+1])
                    {
                        if(tarr[i]!=tarr[i+1])
                        {
                            if(tarr[i]==1)
                            {
                                tva[i]=tva[i+1]=0;
                                if(encode(tva)==0)
                                //minres=max(minres,indata[im][i]+tdp[im][i-1][encode(tarr)]);
                                if(minres<indata[im][i]+tdp[im][i-1][encode(tarr)])
                                {
                                    minres=indata[im][i]+tdp[im][i-1][encode(tarr)];
                                    //cout<<im<<","<<i<<":"<<tdp[im][i-1][encode(tarr)]<<endl;
                                    //printz(encode(tarr));
                                }
                                continue;
                            }
                            tva[i]=tva[i+1]=0;
                            testmin(tdp[im][i][encode(tva)],indata[im][i]+tdp[im][i-1][encode(tarr)]);
                            tva[i]=tarr[i];
                            tva[i+1]=tarr[i+1];
                        }
                        else
                        {
                            if(tarr[i]==1)
                            {
                                tva[tzto[iz][i+1]]=1;
                                tva[i]=tva[i+1]=0;
                            }
                            else
                            {
                                tva[tzto[iz][i]]=2;
                                tva[i]=tva[i+1]=0;
                            }
                            testmin(tdp[im][i][encode(tva)],indata[im][i]+tdp[im][i-1][encode(tarr)]);
                            tva[i]=tarr[i];
                            tva[i+1]=tarr[i+1];
                            tva[tzto[iz][i]]=tarr[tzto[iz][i]];
                            tva[tzto[iz][i+1]]=tarr[tzto[iz][i+1]];
                        }
                    }
                    else if(tarr[i] or tarr[i+1])
                    {
                        testmin(tdp[im][i][encode(tva)],indata[im][i]+tdp[im][i-1][encode(tarr)]);
                        swap(tva[i],tva[i+1]);
                        testmin(tdp[im][i][encode(tva)],indata[im][i]+tdp[im][i-1][encode(tarr)]);
                        swap(tva[i],tva[i+1]);
                    }
                    else
                    {
                        testmin(tdp[im][i][encode(tva)],tdp[im][i-1][encode(tarr)]);
                        tva[i]=1;tva[i+1]=2;
                        testmin(tdp[im][i][encode(tva)],indata[im][i]+tdp[im][i-1][encode(tarr)]);
                        tva[i]=tva[i+1]=0;
                    }
                }
            }
            //for each(iz,pzarr)
            //{
            //    tz=tzarr[iz];
            //    cout<<im<<","<<i<<":"<<tdp[im][i][tz]<<":";printz(tz);
            //}
            //cout<<endl;
        }
        //Line Transform
        for each(iz,pzarr)
        {
            tz=tzarr[iz];
            for each(k,n+1)
            {
                tarr[k]=tz&3;
                tva[k]=tarr[k];
                //cout<<tarr[k]<<" ";
                tz>>=2;
            }
            if(tarr[n+1])continue;
            tdp[im+1][0][encode(tarr-1)]=tdp[im][n][encode(tarr)];
        }
    }
}
                    
int main()
{
    freopen("1187.in","r",stdin);
    freopen("1187.out","w",stdout);
    memset(tdp,-3,sizeof tdp);
    scanf("%d%d",&nm,&n);
    int tsum=0;
    for each(i,nm)
    {
        for each(j,n)
        {
            scanf("%d",&indata[i][j]);
            tsum+=indata[i][j];
        }
    }
    int ti=0;
    while(getnextpermutation(ti));
        //printz(getnextpermutation(ti));
    tdp[1][0][0]=0;
    dp();
    cout<<minres;
}
