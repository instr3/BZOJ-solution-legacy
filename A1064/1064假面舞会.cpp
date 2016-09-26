#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iomanip>
using namespace std;
%:define each(i,n) (int i=1;i<=(n);++i)
%:define every(i,a,b) (int i=(a);i<=(b);++i)
#define union un__ion
int n,nm;
int tmax,tmin;
int tdelta;
int tlast[100001],tfirst[100001];
struct cgroup
{
    int leader[100001];
    int delta[100001];
    int find(int iv)
    {
        if(leader[iv])
        {
            leader[iv]=find(leader[iv]);
            delta[iv]=delta[iv]+tdelta;
            tdelta=delta[iv];
            return leader[iv];
        }
        tdelta=0;
        return iv;
    }
    void union(int iv1,int iv2)//iv1->iv2
    {
        //print();
        int tl1=find(iv1),tl2=find(iv2);
        tdelta=-delta[iv2]+delta[iv1];
        if(tl1==tl2)
        {
            cout<<"Error"<<endl;
        }
        leader[tl2]=tl1;
        delta[tl2]=1+tdelta;
    }
    void print()
    {
        for each(i,n)
        {
            cout<<setw(3)<<leader[i]<<" ";
        }
        cout<<endl;
        for each(i,n)
        {
            cout<<setw(3)<<delta[i]<<" ";
        }
        cout<<endl;
    }
}myt;
inline int gcd(int ia,int ib)
{
    int ir=ia%ib;
    while(ir)
    {
        ia=ib;ib=ir;ir=ia%ib;
    }
    return ib;
}
int main()
{
    freopen("1064.in","r",stdin);
    freopen("1064.out","w",stdout);
    scanf("%d%d",&n,&nm);
    int pf,pt;
    int td1,td2;
    for each(i,nm)
    {
        scanf("%d%d",&pf,&pt);
        if(myt.find(pf)==myt.find(pt))
        {
            myt.find(pf);td1=tdelta;
            myt.find(pt);td2=tdelta;
            tdelta=td1-td2+1;
            //cout<<"Loop:"<<pf<<","<<pt<<":"<<tdelta<<endl;
            
            if(tdelta)
            {
                tdelta=abs(tdelta);
                if(tmax==0)
                {
                    tmax=tdelta;
                }
                else
                {
                    tmax=gcd(tmax,tdelta);
                }
                if(tmax<=2)printf("-1 -1"),exit(0);
            }
        }
        else
        {
            myt.union(pf,pt);
            
            myt.find(pf);td1=tdelta;
            myt.find(pt);td2=tdelta;
            //cout<<"unioned:"<<pf<<","<<pt<<":"<<td1<<","<<td2<<endl;
            //myt.print();
        }
    }
    int tleader;
    if(tmax)
    for(tmin=3;tmin<tmax;++tmin)
    {
        if(tmax%tmin==0)break;
    }
    else
    {
        for each(i,n)
        {
            tleader=myt.find(i);
            if(tleader==i)tmax++;
            tlast[tleader]=min(tlast[tleader],tdelta);
            tfirst[tleader]=max(tfirst[tleader],tdelta);
        }
        
        for each(i,n)
        {
            tmax+=tfirst[i]-tlast[i];
            //tmin=max(tmin,tfirst[i]-tlast[i]+1);
        }
        tmin=3;
    }
    tmin=max(tmin,3);
    if(tmin>tmax)printf("-1 -1"),exit(0);
    printf("%d %d",tmax,tmin);
    //myt.print();
    
}
