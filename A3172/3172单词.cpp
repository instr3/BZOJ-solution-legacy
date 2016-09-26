#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n;
char ind[1001002];int np;
int thash[1001002];
int tlen[201];
int tinh[201];
int tmul26[1001002];
char *inp[201];
void enhash()
{
    tmul26[0]=1;
    for each(i,np)
    {
        tmul26[i]=tmul26[i-1]*27;
        //if(ind[i]==0)thash[i]=thash[i-1]*10;else
        thash[i]=thash[i-1]*27+ind[i]-'a'+1;
        //cout<<thash[i]<<endl;
    }
    //cout<<thash[5]-thash[3]*tmul26[5-3]<<endl;
}
#define gethash(l,r) (thash[r]-thash[(l)-1]*tmul26[(r)-(l)+1])
inline void readstr(char *istr)
{
    char tc=0;
    while(tc<'a'||tc>'z')tc=getchar();
    while(tc>='a'&&tc<='z')
    {
        *istr++=tc;
        tc=getchar();
    }
}
int main()
{
    freopen("3172.in","r",stdin);
    freopen("3172.out","w",stdout);
    scanf("%d",&n);
    np=1;
    for each(i,n)
    {
        inp[i]=&ind[np];
        //scanf("%s",&ind[np]);
        readstr(&ind[np]);
        tlen[i]=strlen(&ind[np]);
        np=np+tlen[i]+1;
    }
    --np;
    /*for every(i,1,n)
    {
        printf("%s ",inp[i]);
    }*/
    enhash();
    //cout<<gethash(4,7);
    int tot;
    for each(i,n)
    {
        tinh[i]=gethash(inp[i]-&ind[0],inp[i]-&ind[0]+tlen[i]-1);
        //cout<<tinh[i]<<endl;
        tot=0;
        for every(j,tlen[i]-1,np)
        {
            if(gethash(j-tlen[i]+1,j)==tinh[i])
            {
                ++tot;
            }
        }
        printf("%d\n",tot);
    }
}
