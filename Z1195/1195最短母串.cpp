#include <iostream>
#include <cstdlib>
//#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n;
int tw[16][16];
char inc[16][52];
int inl[16];
int tdp[1<<15][16];
char *tdps[1<<15][16];
#define getbit(iz,i) ((iz)&(1<<(i)))
#define setbit(iz,i) ((iz)^=(1<<(i)))
int getdp(int iz,int ilast)
{
    char tstr[2002];
    char tsnr[2002];
    int twget;
    int inz=iz;
    if(tdp[iz][ilast]!=-1)return tdp[iz][ilast];
    int res=99999999;
    if(getbit(inz,ilast-1)==0)cout<<"BBBBBBBBBBB"<<endl;
    setbit(inz,ilast-1);
    if(inz==0)
    {
        tdps[iz][ilast]=new char[inl[ilast]+2];
        strcpy(&tdps[iz][ilast][0],&inc[ilast][0]);
        //cout<<iz<<","<<ilast<<":"<<inl[ilast]<<tdps[iz][ilast]<<endl;
        
        return tdp[iz][ilast]=inl[ilast];
    }
    for each(i,n)
    {
        if(getbit(inz,i-1))
        {
            twget=getdp(inz,i)+inl[ilast]-tw[i][ilast];
            if(res>=twget)
            {
                if(res>twget)
                {
                    res=twget;
                    memset(tstr,0,sizeof tstr);
                    strcpy(tstr,tdps[inz][i]);
                    strcpy(&tstr[res-inl[ilast]],inc[ilast]);
                }
                else
                {
                    memset(tsnr,0,sizeof tdps[iz][ilast]);
                    strcpy(tsnr,tdps[inz][i]);
                    strcpy(&tsnr[res-inl[ilast]],inc[ilast]);
                    if(strcmp(tsnr,tstr)==-1)
                    {
                        strcpy(tstr,tsnr);
                    }
                }
            }
        }
    }
    //cout<<iz<<","<<ilast<<":"<<res<<":"<<tstr<<endl;
    tdps[iz][ilast]=new char[res+2];
    strcpy(tdps[iz][ilast],tstr);
    return tdp[iz][ilast]=res;
}
bool tdel[16];
int main()
{
    freopen("1195.in","r",stdin);
    freopen("1195.out","w",stdout);
    memset(tdp,-1,sizeof tdp);
    scanf("%d",&n);
    
    for each(i,n)
    {
        scanf("%s",&inc[i][0]);
        inl[i]=strlen(inc[i]);
    }
    int tlen;
    for each(i,n)
    {
        for each(j,n)
        {
            if(i!=j)
            if(strstr(inc[i],inc[j]))
            {
                //tdel[j]=true;
                //cout<<j<<"Died"<<endl;
            }
        }
    }
    for each(i,n)
    {
        if(tdel[i])
        {
            inl[i]=0;
            inc[i][0]=0;
        }
    }
    for each(i,n)
    {
        tlen=inl[i];
        for each(j,n)
        {
            if(i==j)continue;
            for every(k,0,tlen-1)
            {
                for every(p,k,tlen-1)
                {
                    if(inc[i][p]!=inc[j][p-k])goto die;
                }
                tw[i][j]=tlen-k;
                //cout<<i<<","<<j<<":"<<tw[i][j]<<endl;
                break;
                die:;
            }
        }
    }
    int tot=99999999;
    char **res=0;
    for each(i,n)
    {
        //cout<<getdp((1<<n)-1,i)<<":"<<&tdps[(1<<n)-1][i][0]<<endl;
        
        if(tot>getdp((1<<n)-1,i))
        {
            tot=getdp((1<<n)-1,i);
            res=&tdps[(1<<n)-1][i];
        }
        else if(tot==getdp((1<<n)-1,i))
        {
            if(strcmp(tdps[(1<<n)-1][i],*res)==-1)
            {
                res=&tdps[(1<<n)-1][i];
            }
        }
    }
    printf("%s",*res);
    //cout<<tot<<endl;
}
