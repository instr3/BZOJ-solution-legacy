#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define lowbit(iv) ((iv)&-(iv))
#define sqr(x) ((x)*(x))
inline int randint(int il,int ir)
{
    return rand()%(ir-il+1)+il;
}
int nx=3,ny=4,nz=5;
int main()
{
    freopen("in","w",stdout);
    cout<<nx<<" "<<ny<<" "<<nz<<endl;
    for each(ix,nx)
    {
        for each(iy,ny)
        {
            for each(iz,nz)
            {
                if(randint(0,1)!=0)cout<<0<<" ";
                else cout<<1<<" ";
            }
            cout<<endl;
        }
    }
}
                
