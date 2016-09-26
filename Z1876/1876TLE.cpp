#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define enum en__um
int na,nb;
char nsa[10001],nsb[10001];
int tmul2;
typedef int enum[20010];
void print(enum ia)
{
    for(int i=ia[0];i;--i)printf("%d",(int)ia[i]);
}
inline void dec0(enum &ia)
{
    while(ia[ia[0]]==0&&ia[0])--ia[0];
}
int tb2[20]={0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9};
void sdiv2(enum &ia)
{
    bool tr=false;
    for(int i=ia[0];i;--i)
    {
        if(tr)ia[i]+=10,tr=false;
        if(ia[i]%2)tr=true;
        ia[i]=tb2[(int)ia[i]];
        //ia[i]/=2;
    }
    dec0(ia);
}
void smul2(enum &ia)
{
    for each(i,ia[0])
    {
        ia[i]*=2;
    }
    for each(i,ia[0])
    {   
        if(ia[i]>=10)
        {
            ia[i]-=10;
            ia[i+1]+=1;
        }
    }
    ia[0]++;
    //print(ia);cout<<endl;
    dec0(ia);
}
void ssub(enum &ia,enum ib)
{
    for each(i,ia[0])
    {
        ia[i]-=ib[i];
        if(ia[i]<0)
        {
            ia[i]+=10;
            ia[i+1]-=1;
        }
    }
    dec0(ia);
}
void convert(enum &ia,char *istr)
{
    ia[0]=strlen(istr);
    int ip=0;
    for(int i=ia[0];i;--i)ia[i]=istr[ip++]-'0';
}
bool cmp(enum &ia,enum &ib)
{
    if(ia[0]!=ib[0])return ia[0]>ib[0];
    for(int i=ia[0];i;--i)
    {
        if(ia[i]!=ib[i])return ia[i]>ib[i];
    }
    //printf("Same WTF");
    for each(i,tmul2)
    {
        smul2(ia);
    }
    print(ia);exit(0);
    return true;
}
int gcd(int ia,int ib)
{
    while(ia%2==0&&ib%2==0)
    {
        ia=ia/2;
        ib=ib/2;
        tmul2++;
    }
    while(true)
    {
        if(ia==ib)
        {
            for each(i,tmul2)
            {
                ia=ia*2;
            }
            return ia;
        }
        if(ia%2==0)
        {
            ia=ia/2;
        }
        else if(ib%2==0)
        {
            ib=ib/2;
        }
        else
        {
            if(ia>ib)
            {
                ia=ia-ib;
            }
            else
            {
                ib=ib-ia;
            }
        }
    }
}
enum ia,ib;
int main()
{
    freopen("1876.in","r",stdin);
    freopen("1876.out","w",stdout);
    scanf("%s%s",&nsa[0],&nsb[0]);
    convert(ia,nsa);
    convert(ib,nsb);
    dec0(ia);dec0(ib);
    while(ia[1]%2==0&&ib[1]%2==0)
    {
        sdiv2(ia);
        sdiv2(ib);
        tmul2++;
    }
    while(true)
    {
        //print(ia);printf(";");print(ib);printf("\n");

        if(ia[1]%2==0)
        {
            sdiv2(ia);
        }
        else if(ib[1]%2==0)
        {
            sdiv2(ib);
        }
        else
        {
            if(cmp(ia,ib))
            {
                ssub(ia,ib);
            }
            else
            {
                ssub(ib,ia);
            }
        }
    }
    //scanf("%d%d",&na,&nb);
    //printf("%d",gcd(na,nb));
    
}
