#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
int n,nmod;
int indata[200001],pin;
int myq[200001],pmyq;
int task;
int leader[200001];
int find(int it)
{
    if(leader[it])return leader[it]=find(leader[it]);
    return it;
}
char getachar()
{
    char tc=0;
    while(tc!='A'&&tc!='Q')
    {
        tc=getchar();
    }
    return tc;
}
int main()
{
    freopen("1012.in","r",stdin);
    freopen("1012.out","w",stdout);
    scanf("%d%d",&n,&nmod);
    char tc[2];int tn;
    int maxn;
    for(int i=1;i<=n;++i)
    {
        tc[0]=getachar();
        scanf("%d",&tn);
        if(tc[0]=='A')
        {
            indata[++pin]=(tn+task)%nmod;
            for(;pmyq;)
            {
                if(indata[myq[pmyq]]>=indata[pin])
                {
                    break;
                }
                else
                {
                    leader[myq[pmyq]]=pin;
                    //cout<<myq[pmyq]<<","<<pin<<endl;
                    pmyq--;
                }
            }
            myq[++pmyq]=pin;
        }
        else
        {
            //maxn=0;
            //for(int i=pin-tn+1;i<=pin;++i)
            //{
            //    maxn=max(maxn,indata[i]);
            //}
            
            maxn=indata[find(pin-tn+1)];
            task=maxn;
            //ut<<<<maxn<<endl;
            printf("%d\n",maxn);
        }
    }
}
