#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
struct enode{int to,fr,c,f,tp,next;}mye[10001];int pmye=1;
struct vnode{int first,h,cur;}myv[10001];int pmyv;
int n;
int tot;
int tharr[10001];
int testk[10001];int pstk;
//bool visit[10001];
void addedge(int pf,int pt,int pw)
{
    //cout<<"Addedge:"<<pf<<"->"<<pt<<":"<<pw<<endl;
    mye[++pmye].to=pt;
    mye[pmye].fr=pf;
    mye[pmye].c=pw;
    mye[pmye].f=0;
    mye[pmye].next=myv[pf].first;
    myv[pf].first=pmye;
    
    mye[++pmye].to=pf;
    mye[pmye].fr=pt;
    mye[pmye].c=0;
    mye[pmye].f=0;
    mye[pmye].next=myv[pt].first;
    myv[pt].first=pmye;
}   
void sap()
{
    int pf,pt;
    int minh;
    int minw;
    tharr[0]=n;
    for each(i,n)myv[i].cur=myv[i].first;
    while(true)
    {
        pf=1;
        while(true)
        {
            minh=99999999;
            for(int p;myv[pf].cur;myv[pf].cur=mye[myv[pf].cur].next)
            {
                p=myv[pf].cur;
                pt=mye[p].to;
                if(mye[p].c-mye[p].f>0)
                {
                    minh=min(minh,myv[pt].h+1-myv[pf].h);
                    if(myv[pt].h+1==myv[pf].h)
                    {
                        testk[++pstk]=p;
                        pf=pt;
                        if(pf==n)
                        {
                            minw=99999999;
                            for each(i,pstk)
                            {
                                minw=min(minw,mye[testk[i]].c-mye[testk[i]].f);
                            }
                            tot+=minw;
                            //cout<<minw<<":";
                            while(pstk)
                            {
                                mye[testk[pstk]].f+=minw;
                                mye[testk[pstk]^1].f-=minw;
                                //cout<<mye[testk[pstk]].to<<" ";
                                pstk--;
                            }
                            //cout<<endl;
                            goto m_break;
                        }   
                        goto m_find;
                    }
                }
            }
            tharr[myv[pf].h]--;
            //cout<<pf<<"::"<<myv[pf].h<<"->"<<myv[pf].h+minh<<endl;
            if(!tharr[myv[pf].h]){return;}
            myv[pf].h+=minh;
            if(minh==99999999)return;
            tharr[myv[pf].h]++;
            myv[pf].cur=myv[pf].first;
            //if(myv[pf].h>=9999)return;
            if(!pstk)break;
            pstk--;
            pf=pstk?mye[testk[pstk]].to:1;
            continue;
m_find:;
        }
m_break:;
    }
}
char indata[21][21];
int phdata[21][21];
int tdoor[401],ptd;
bool isdoor[401];
int tvar0,tvar1,tvar2;
int tytot;
int tpath[401][401];
bool task(int tv)
{
    for each(i,n)myv[i].h=0;
    for each(i,pmye)mye[i].f=0;
    tot=0;
    for(int p=tvar1;p<=tvar2;p+=2)
    {
        mye[p].c=tv;
    }
    for(int p=tvar0;p<tvar1;p+=2)
    {
        mye[p].c=(tv>=mye[p].tp)?1:0;
    }
    sap();
    return tot==tytot;
}
int main()
{
    freopen("1189.in","r",stdin);
    freopen("1189.out","w",stdout);
    memset(tpath,38,sizeof(tpath));
    /*
    n=4;
    addedge(1,2,3);
    addedge(2,3,2);
    addedge(3,4,5);
    addedge(2,4,4);
    addedge(1,3,4);
    addedge(1,4,1);
    sap();
    cout<<"tot:"<<tot<<endl;*/
    int nx,ny;scanf("%d%d",&nx,&ny);
    char tc[22];
    n=1;
    for each(i,nx)
    {
        scanf("%s",&tc[1]);
        for each(j,ny)
        {
            indata[i][j]=tc[j];
            if(indata[i][j]!='X')phdata[i][j]=++n;
            //cout<<i<<","<<j<<":"<<n<<":"<<tc[j]<<endl;
            if(indata[i][j]=='D')tdoor[++ptd]=phdata[i][j],isdoor[phdata[i][j]]=true;
        }
    }
    for every(i,2,nx-1)
    for every(j,2,ny-1)
    {
        if(indata[i][j]=='X')continue;
        addedge(1,phdata[i][j],1);
        tytot++;
        if(indata[i-1][j]!='X')/*addedge(phdata[i][j],phdata[i-1][j],99999999),*/tpath[phdata[i][j]][phdata[i-1][j]]=1;
        if(indata[i+1][j]!='X')/*addedge(phdata[i][j],phdata[i+1][j],99999999),*/tpath[phdata[i][j]][phdata[i+1][j]]=1;
        if(indata[i][j-1]!='X')/*addedge(phdata[i][j],phdata[i][j-1],99999999),*/tpath[phdata[i][j]][phdata[i][j-1]]=1;
        if(indata[i][j+1]!='X')/*addedge(phdata[i][j],phdata[i][j+1],99999999),*/tpath[phdata[i][j]][phdata[i][j+1]]=1;
    }
    for every(k,2,n)
    {
        for every(i,2,n)
        {
            if(k==i)continue;
            for every(j,2,n)
            {
                if(i==j or k==j)continue;
                tpath[i][j]=min(tpath[i][j],tpath[i][k]+tpath[k][j]);
            }
        }
    }
    tvar0=pmye+1;
    for every(i,2,n)
    {
        for each(k,ptd)
        {
            if(isdoor[i])continue;
            addedge(i,tdoor[k],9);
            mye[pmye-1].tp=tpath[i][tdoor[k]];
        }
    }
    tvar1=pmye+1;
    ++n;
    for each(i,nx)
    for each(j,ny)
    {
        if(indata[i][j]=='D')
        {
            addedge(phdata[i][j],n,98765432);
        }
    }
    tvar2=pmye;
    int pl=0,pr=999;
    int pm;
    while(pr-1>pl)
    {
        pm=(pl+pr)/2;
        if(!task(pm))pl=pm;else pr=pm;
    }
    if(pr>=900)cout<<"impossible";else
    cout<<pr;
}
