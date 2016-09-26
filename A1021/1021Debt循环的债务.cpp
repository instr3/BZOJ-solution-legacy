#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
//#include <cmath>
#include <algorithm>
using namespace std;
#define using us__ing
#define dp(x,y) odp[0][(x)+1200][(y)+1200] //A have,B have
#define dp2(x,y) odp[1][(x)+1200][(y)+1200]
#define dpx(n,x,y) odp[n][(x)+1200][(y)+1200]
#define oo (99999999)
#define using us__ing
#define cdecl cd__ecl

int marr[301];int nms[301];
int mwho[301];
//int odp[2401][2401];
int odp[2][2401][2401];
int nmon[4][7];
//{0,1,5,10,20,50,100};
int na,nb,nc;
/*
inline void testif(int ia,int ib,int ica,int icb,int ik)
{
    if(dp(ia,ib)>dp(ica,icb))
    {
        dp2(ia,ib)=ik;
        dp(ia,ib)=dp(ica,icb)+1;
    }
}*/

int main()
{
    memset(odp,38,sizeof(odp));
    //memset(odp2,38,sizeof(odp2));
    freopen("1021.in","r",stdin);
    freopen("1021.out","w",stdout);
    int nsa,nsb,nsc;
    scanf("%d%d%d",&nsa,&nsb,&nsc);
    na+=nsa;nb-=nsa;nb+=nsb;nc-=nsb;nc+=nsc;na-=nsc;
    dp(na,nb)=0;
    dp2(na,nb)=0;
    for(int i=1;i<=3;++i)
    {
        for(int j=6;j>=1;--j)
        {
            scanf("%d",&nmon[i][j]);
        }
    }
    int using;
    int ik=1;
    int dlimit[7]={0,30,150,300,2000,2000,2000};
    int kgcd[7]={0,1,5,10,10,50,100};
    int kmon[7]={0,1,5,10,20,50,100};
    int tna1,tna2,tnb1,tnb2;
    int in=0;
    for(int tm=1;tm<=6;++tm)
    {
        using=kmon[tm];
        tna1=max(-1000,(na/dlimit[tm]-1)*dlimit[tm]-dlimit[tm]);
        tna2=min( 1000,(na/dlimit[tm]+1)*dlimit[tm]+dlimit[tm]);
        tnb1=max(-1000,(nb/dlimit[tm]-1)*dlimit[tm]-dlimit[tm]);
        tnb2=min( 1000,(nb/dlimit[tm]+1)*dlimit[tm]+dlimit[tm]);
        for(int ts=1;ts<=3;++ts)
        for(int k=1;k<=nmon[ts][tm];++k,++ik,in=!in)
        {
            //memcpy(odp2,odp,sizeof(odp));
            for(int ia=tna1;ia<=tna2;ia+=kgcd[tm])
            for(int ib=tnb1;ib<=tnb2;ib+=kgcd[tm])
            {
                
                if(dpx(in,ia,ib)<oo)
                {
                //cout<<ia<<","<<ib<<","<<dpx(in,ia,ib)<<","<<ik<<endl;
                    if(ts==1)
                    {
                        //testif(ia-using,ib+using,ia,ib,ik);
                        dpx(!in,ia-using,ib+using)=min(dpx(!in,ia-using,ib+using),dpx(in,ia,ib)+1);
                        //testif(ia-using,ib,ia,ib,ik);
                        dpx(!in,ia-using,ib)=min(dpx(!in,ia-using,ib),dpx(in,ia,ib)+1);
                    }
                    else if(ts==2)
                    {
                        //testif(ia+using,ib-using,ia,ib,ik);
                        dpx(!in,ia+using,ib-using)=min(dpx(!in,ia+using,ib-using),dpx(in,ia,ib)+1);
                        //testif(ia,ib-using,ia,ib,ik);
                        dpx(!in,ia,ib-using)=min(dpx(!in,ia,ib-using),dpx(in,ia,ib)+1);
                    }
                    else
                    {
                        //testif(ia+using,ib,ia,ib,ik);
                        dpx(!in,ia+using,ib)=min(dpx(!in,ia+using,ib),dpx(in,ia,ib)+1);
                        //testif(ia,ib+using,ia,ib,ik);
                        dpx(!in,ia,ib+using)=min(dpx(!in,ia,ib+using),dpx(in,ia,ib)+1);
                    }
                }
            }
            //memcpy(odp,odp2,sizeof(odp));
        }
    }
    if(dp(0,0)>oo&&dp2(0,0)>oo)
    cout<<"impossible";else
    cout<<min(dp(0,0),dp2(0,0));
}
