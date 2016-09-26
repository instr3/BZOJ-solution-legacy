#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
int n,nmod;
int indata[200001],pin;
int task;

int main()
{
    freopen("1012.in","r",stdin);
    freopen("1012.out","w",stdout);
    scanf("%d%d",&n,&nmod);
    char tc[2];int tn;
    int maxn;
    for(int i=1;i<=n;++i)
    {
        scanf("%s%d",&tc[0],&tn);
        if(tc[0]=='A')
        {
            indata[++pin]=(tn+task)%nmod;
        }
        else
        {
            maxn=0;
            for(int i=pin-tn+1;i<=pin;++i)
            {
                maxn=max(maxn,indata[i]);
            }
            task=maxn;
            cout<<maxn<<endl;
        }
    }
}
