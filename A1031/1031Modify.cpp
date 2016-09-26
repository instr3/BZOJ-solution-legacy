#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define each2(i,n) (int i=(n);i;--i)
int n,n2;
char instr[200002];
int myh[200001];
int tplace[200001],trank[400001],tsrank[400001];
int tk;
inline bool cmp(int it1,int it2)
{
    return trank[it1]==trank[it2]?trank[it1+tk]<trank[it2+tk]:trank[it1]<trank[it2];
}
inline bool cmp2(int it1,int it2)
{
    return tsrank[it1]==tsrank[it2]&&tsrank[it1+tk]==tsrank[it2+tk];
}
int main()
{
    freopen("1031.in","r",stdin);
    freopen("1031.out","w",stdout);
    int prank;
    scanf("%s",&instr[1]);
    n=strlen(&instr[1]);
    for each(i,n)instr[n+i]=instr[i];
    n2=n;n*=2;
    for each(i,n)trank[i]=instr[i];
    for each(i,n)tplace[i]=i;
    for each(i,n)tsrank[i]=trank[i];
    for(tk=1;tk<=n;tk<<=1)
    {
        sort(tplace+1,tplace+n+1,cmp);
        prank=0;
        for each(i,n)
        {
            if(cmp2(tplace[i],tplace[i-1]))
            {
                trank[tplace[i]]=prank;
            }
            else trank[tplace[i]]=++prank;
        }
        //for each(i,n)cout<<trank[i]<<" ";cout<<endl;
        for each(i,n)tsrank[i]=trank[i];
    }
    //cout<<&instr[1]<<endl;
    for each(i,n)
    {
        if(tplace[i]>n2)continue;
        printf("%c",instr[tplace[i]+n2-1]);
    }
}
