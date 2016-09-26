#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
int n,sqrtn,nblock;
int indata[100001];
long long td[100001];
long long tdd[100001];
struct cbox
{
    bool last;
    int res[2];
    int lt,rt;
    bool full;
}tblock[321];
int tlocate[100001];
int tupdate[5];
inline void updateblock(int ib)
{
    cbox &tb=tblock[ib];
    int tcount=0;
    tb.res[0]=tb.res[1]=0;
    for every(j,tb.lt,tb.rt)
    {
        if(!tdd[j])
        {
            tb.res[0]+=(tcount+1)/2;
            tb.res[1]+=(tcount+0)/2;
            tcount=0;
            for every(k,j+1,tb.rt)
            {
                if(!tdd[k])
                {
                    tb.res[0]+=(tcount+1)/2;
                    tb.res[1]+=(tcount+1)/2;
                    tcount=0;
                }
                else tcount++;
            }
            tb.res[0]+=(tcount+1)/2;
            tb.res[1]+=(tcount+1)/2;
            tb.last=(tcount%2)?1:0;
            //cout<<tblock[ib].res[0]<<","<<tblock[ib].res[1]<<","<<tblock[ib].last<<endl;
            tb.full=false;
            return;
        }
        else tcount++;
    }
    tb.res[0]+=(tcount+1)/2;
    tb.res[1]+=(tcount+0)/2;
    tb.last=(tcount%2)?1:0;
    tb.full=true;
    //cout<<tblock[ib].res[0]<<","<<tblock[ib].res[1]<<","<<tblock[ib].last<<endl;
    return;
}
int main()
{
    freopen("1558.in","r",stdin);
    freopen("1558.out","w",stdout);
    scanf("%d",&n);
    sqrtn=(int)sqrt((double)n);
    if(sqrtn%2)sqrtn++;
    nblock=(n-1)/sqrtn+1;
    int tl,tr;
    for each(i,n)
    {
        scanf("%d",&indata[i]);
        td[i]=indata[i]-indata[i-1];
        tdd[i]=td[i]-td[i-1];
        //cout<<tdd[i]<<" ";
    }
    for each(i,nblock)
    {
        tl=(i-1)*sqrtn+1;
        tr=min(i*sqrtn,n);
        for every(j,tl,tr)tlocate[j]=i;
        tblock[i].lt=tl;tblock[i].rt=tr;
        updateblock(i);
    }

    int nop;scanf("%d",&nop);
    char tc[2];
    int ta,tb;
    int tlen;
    int res;bool tlast;
    int tcount;
    for each(i,nop)
    {
        scanf("%s",&tc[0]);
        if(tc[0]=='A')
        {
            scanf("%d%d%d%d",&tl,&tr,&ta,&tb);
            tlen=tr-tl+1;
            {
                tlast=tdd[tl];
                tdd[tl]+=ta;
                tupdate[1]=tlocate[tl];
                if(((bool)tlast)==((bool)tdd[tl]))tupdate[1]=tupdate[0];
            }
            if(tl+1<=n)
            {
                tlast=tdd[tl+1];
                tdd[tl+1]+=tb-ta;
                tupdate[2]=tlocate[tl+1];
                if(((bool)tlast)==((bool)tdd[tl+1]))tupdate[2]=tupdate[1];
            }
            if(tr+1<=n)
            {
                tlast=tdd[tr+1];
                tdd[tr+1]+=-ta-tlen*(long long)tb;
                tupdate[3]=tlocate[tr+1];
                if(((bool)tlast)==((bool)tdd[tr+1]))tupdate[3]=tupdate[2];
            }
            if(tr+2<=n)
            {
                tlast=tdd[tr+2];
                tdd[tr+2]+=ta+(tlen-1)*(long long)tb;
                tupdate[4]=tlocate[tr+2];
                if(((bool)tlast)==((bool)tdd[tr+2]))tupdate[4]=tupdate[3];
            }
            //for each(i,n)cout<<tdd[i]<<" ";
            //cout<<endl;
            if(tupdate[0]!=tupdate[1])updateblock(tlocate[tl]);
            if(tl+1<=n)if(tupdate[1]!=tupdate[2])updateblock(tlocate[tl+1]);
            if(tr+1<=n)if(tupdate[2]!=tupdate[3])updateblock(tlocate[tr+1]);
            if(tr+2<=n)if(tupdate[3]!=tupdate[4])updateblock(tlocate[tr+2]);
            
        }
        else
        {
            scanf("%d%d",&tl,&tr);
            tl+=2;
            res=0;
            if(tl>tr){printf("1\n");continue;}
            tcount=0;
            if(tlocate[tl]==tlocate[tr])
            {
                for every(j,tl,tr)
                {
                    if(!tdd[j])
                    {
                        res+=(tcount+1)/2;
                        tcount=0;
                    }
                    else tcount++;
                }
                res+=(tcount+1)/2;
                tcount=0;
            }
            else
            {
                for every(j,tl,tblock[tlocate[tl]].rt)
                {
                    if(!tdd[j])
                    {
                        res+=(tcount+1)/2;
                        tcount=0;
                    }
                    else tcount++;
                }
                res+=(tcount+1)/2;
                tlast=tcount%2;tcount=0;
                for every(ib,tlocate[tl]+1,tlocate[tr]-1)
                {
                    res+=tblock[ib].res[tlast];
                    if(!tblock[ib].full)tlast=tblock[ib].last;
                }
               // cout<<res<<","<<tlast<<endl;
                tcount=-(int)tlast;
                for every(j,tblock[tlocate[tr]].lt,tr)
                {
                    if(!tdd[j])
                    {
                        res+=(tcount+1)/2;
                        tcount=0;
                    }
                    else tcount++;
                }
                res+=(tcount+1)/2;
            }
            printf("%d\n",res+1);
        }
    }

}
