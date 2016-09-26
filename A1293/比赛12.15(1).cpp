#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=n;++i)
char tc;int tres;inline int getnum()
{
    //scanf("%d",&tres);
    //return tres;
    
    tc=0;while(tc<'0'||tc>'9')tc=getchar();
    tres=0;while(tc>='0'&&tc<='9')
    {tres=tres*10+tc-'0';tc=getchar();}
    return tres;
}
int inti[61];
//int indata[61][1000001];
int n,nk;
struct tnode
{
    int num;
    int w;
    bool operator <(tnode ano)const
    {
        return w<ano.w;
    }
}myq[10000001];int pmyq;
/*tnode tmq[60000000];*/int tqf=1,tqb;
int addcount[1000001];
int allsum;
int res;
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    n=getnum();nk=getnum();
    int tsi=0;
    int tlast;
    for each(i,nk)
    {
        inti[i]=getnum();
        tlast=-13109;
        for each(j,inti[i])
        {
            
            //indata[i][j]=getnum();
            myq[++pmyq].w=getnum();
            if(tlast==myq[pmyq].w)
            {
                --pmyq;
            }
            myq[pmyq].num=i;
            tlast=myq[pmyq].w;
            
        }
        inplace_merge(myq+1,myq+tsi+1,myq+pmyq+1);
        tsi=pmyq;
    }
    res=2147483647;
    for each(i,pmyq)
    {
        //cout<<myq[i].num<<" "<<myq[i].w<<endl;
        //tmq[++tqb]=myq[i];
        ++tqb;
        if(addcount[myq[i].num]==0)allsum++;
        addcount[myq[i].num]++;
        while(addcount[myq[tqf].num]>1){addcount[myq[tqf].num]--;tqf++;}
        //for(int j=tqf;j<=tqb;++j)
        //cout<<myq[j].num<<" ";
        //cout<<":"<<allsum<<endl;
        if(allsum==nk)res=min(res,myq[tqb].w-myq[tqf].w);
    }
    
    cout<<res<<endl;
}
