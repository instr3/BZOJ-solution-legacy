#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
int next[21];
char cp[22];
int arrm[21][21];
int nk1,nk2,nmod,tot=0;
void getnext()
{
    unsigned int i=0;int j=-1;
    next[0]=-1;
    while(i<strlen(cp))
    if(j==-1||cp[i]==cp[j])
    {
        ++i;++j;
        next[i]=j;
    }
    else j=next[j];
}
int main()
{
    freopen("1009.in","r",stdin);
    freopen("1009.out","w",stdout);
    scanf("%d%d%d",&nk1,&nk2,&nmod);
    scanf("%s",&cp[0]);
    getnext();
    for(int i=0;i<=nk2;++i)
    {
        for(int j=next[i];j!=-1;j=next[j])
        {
            printf("%d(%c) can be turned into %d(%c)\n",i-1,cp[i-1],j,cp[j]);
            arrm[i][j+1]=1;
        }
    }
    for(int i=1;i<=nk2;++i)
    {
        for(int j=1;j<=nk2;++j)
        {
            cout<<arrm[i][j]<<" ";
        }
        cout<<endl;
    }
    for(int i=0;i<nk2;++i)
    printf("%d ",next[i]);
}
