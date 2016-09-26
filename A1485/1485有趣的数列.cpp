#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
int tarr[2000001];
int tpri[1000001];int ppri;
int tpat[2000001];
int tput[1000001];
int n,np;
int mypower(int tb,int tp)
{
    int tres=1;
    while(tp)
    {
        if(tp%2)
        {
            tres=((long long)tres*tb)%np;
        }
        tb=((long long)tb*tb)%np;
        tp/=2;
    }
    return tres;
}
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    scanf("%d%d",&n,&np);
    n*=2;
    int tn=n;
    n/=2;
    int tsn=(int)sqrt(tn);
    for every(i,2,tsn)
    {
        if(tarr[i])continue;
        for(int j=i*i;j<=tn;j+=i)
        {
            if(!tarr[j])tarr[j]=i;
        }
    }
    for every(i,2,tn)
    {
        if(!tarr[i])
        {
            tpri[++ppri]=i;
            tpat[i]=ppri;
        }
    }
    int tnum;
    for every(i,n+2,tn)
    {
        tnum=i;
        while(true)
        {
            if(!tarr[tnum])
            {
                tput[tpat[tnum]]++;
                break;
            }
            tput[tpat[tarr[tnum]]]++;
            tnum/=tarr[tnum];
        }
    }
    for every(i,2,n)
    {
        tnum=i;
        while(true)
        {
            if(!tarr[tnum])
            {
                tput[tpat[tnum]]--;
                break;
            }
            tput[tpat[tarr[tnum]]]--;
            tnum/=tarr[tnum];
        }
    }
    int tres=1;
    for each(i,ppri)
    {
        //cout<<tpri[i]<<":"<<tput[i]<<endl;
        if(tput[i])
        tres=((long long)tres*mypower(tpri[i],tput[i]))%np;
    }
    cout<<tres<<endl;
        
}
/*
int test[100];
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    int n=16;
    int tot=0;
    for each(i,n)test[i]=i;
    do
    {
        //for each(i,n)cout<<test[i]<<" ";cout<<endl;
        for each(i,n-2)
        {
            if(test[i]>test[i+2])goto m_con;
        }
        for(int i=1;i<=n;i+=2)
        {
            if(test[i]>test[i+1])goto m_con;
        }
        tot++;
        m_con:;
    }while(next_permutation(test+2,test+n));
    cout<<tot<<endl;
}
*/
