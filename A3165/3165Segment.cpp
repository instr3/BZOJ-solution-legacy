#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int pmyl;
int n;
int tgres;char tgc;
double tans[39990];
int tansat[39990];
inline int readint()
{
    tgres=0;
    while(tgc<'0'||tgc>'9')tgc=getchar();
    while(tgc>='0'&&tgc<='9')tgres=tgres*10+tgc-'0',tgc=getchar();
    return tgres;
}
int main()
{
    freopen("3165.in","r",stdin);
    freopen("3165.out","w",stdout);
    
    scanf("%d",&n);
    int top;
    int lastans=0,tx1,ty1,tx2,ty2,tv;   
    double tmax;int tmaxat;
    double res,tk,tb,tget;
    for each(i,n)
    {
        //scanf("%d",&top);
        top=readint();
        if(top==0)
        {
            //scanf("%d",&tx1);
            tx1=readint();
            tx1=(tx1+ lastans-1)%39989+1;
            /*tmax=-9e99;
            tmaxat=0;
            for each(j,pmyl)
            {
                if(tx1<myl[j].x1||tx1>myl[j].x2)continue;
                res=myl[j].k*tx1+myl[j].b;
                if(res>tmax)
                {
                    tmax=res;
                    tmaxat=j;
                }
            }
            lastans=tmaxat;
            printf("%d\n",tmaxat);*/
            lastans=tansat[tx1];
            printf("%d\n",tansat[tx1]);
        }
        else
        {
            //scanf("%d%d%d%d",&tx1,&ty1,&tx2,&ty2);
            tx1=readint();
            ty1=readint();
            tx2=readint();
            ty2=readint();
            tx1=(tx1+lastans-1)%39989+1;
            tx2=(tx2+lastans-1)%39989+1;
            ty1=(ty1+lastans-1)%1000000000+1;
            ty2=(ty2+lastans-1)%1000000000+1;
            if(tx1>tx2)
            {
                tv=tx1;tx1=tx2;tx2=tv;
                tv=ty1;ty1=ty2;ty2=tv;
            }
            tk=(ty2-ty1)/(double)(tx2-tx1);
            //tb=ty1-tx1*tk;
            ++pmyl;
            tget=ty1;
            for every(i,tx1,tx2)
            {
                if(tans[i]<=tget)
                {
                    tans[i]=tget;
                    tansat[i]=pmyl;
                }
                tget+=tk;
            }
            
            //myl[++pmyl].k=(ty2-ty1)/(double)(tx2-tx1);
            //myl[pmyl].b=ty1-tx1*myl[pmyl].k;
            //myl[pmyl].x1=tx1;
            //myl[pmyl].x2=tx2;
        }
    }
}
