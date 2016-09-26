#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
int main()
{
    freopen("1009.in","r",stdin);
    freopen("1009.out","w",stdout);
    int nk1,nk2,nmod,tot=0;
    scanf("%d%d%d",&nk1,&nk2,&nmod);
    int n2;
    scanf("%d",&n2);
    int n1max=1;
    for(int i=1;i<=nk1;++i)n1max*=10;
    int n2max=1;
    for(int i=1;i<=nk2;++i)n2max*=10;
    for(int i=0,j;i<=n1max;++i)
    {
        //Do not input 0!
        j=i;
        while(j)
        {
            if(j%n2max==n2)
            {
                tot++;
                break;
            }
            j/=10;
        }
    }
    cout<<n1max-tot<<endl;
}
