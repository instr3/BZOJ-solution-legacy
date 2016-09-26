#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <iomanip>
#include <queue>
using namespace std;
#include <cmath>
using std::pow;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
#define chr(in) ((char)(in+'A'))
#define asc(ic) ((int)(ic-'A')) 
#define alnext(i) every(i,0,25)
int tdp[101][6002];
struct actheory
{
    struct wordnode
    {
        wordnode *next[27],*fail;
        int mark;
    }*root,plist[6002];int ppl;
    inline void init()
    {
        root=&plist[++ppl];
    }
    void printnode(wordnode *it,int idp)
    {
        if(it->mark){for each(i,idp)cout<<" ";cout<<"("<<it->mark<<")"<<endl;}
        for alnext(i)
        {
            if(it->next[i])
            {
                for each(j,idp)cout<<" ";
                cout<<"["<<chr(i)<<"]"<<it->next[i]-plist<<":"<<it->next[i]->fail-plist<<endl;
                printnode(it->next[i],idp+1);
            }
        }
    }
    void print()
    {
        cout<<root<<endl;
        printnode(root,0);
    }
    void insertword(char *istr,int in)
    {
        int tlen=strlen(istr);
        int tasc;
        wordnode *tp=root;
        for every(i,0,tlen-1)
        {
            tasc=asc(istr[i]);
            if(!tp->next[tasc])
            tp->next[tasc]=&plist[++ppl];
            tp=tp->next[tasc];
        }
        tp->mark=in;
    }
    void makefail()
    {
        //root->fail=root;
        queue<wordnode *>myq;
        myq.push(root);
        wordnode *tt,*tp;
        while(!myq.empty())
        {
            tt=myq.front();
            myq.pop();
            for alnext(p)
            {
                if(tt->next[p])
                {
                    myq.push(tt->next[p]);
                    if(tt==root)goto die;
                    for(tp=tt->fail;;tp=tp->fail)
                    {
                        //cout<<tp<<endl;
                        if(tp->next[p])
                        {
                            tt->next[p]->fail=tp->next[p];
                            break;
                        }
                        if(tp==root)
                        {
                            die:;
                            tt->next[p]->fail=root;
                            break;
                        }
                    }
                }
            }
        }
    }
    void testsen(char *istr)
    {
        int tlen=strlen(istr);
        wordnode *tp,*tfail;
        int tasc;
        for every(i,0,tlen-1)
        {
            tasc=asc(istr[i]);
            for(;tp;tp=tp->fail)
            {
                if(tp->next[tasc])
                {
                    tp=tp->next[tasc];
                    for(tfail=tp;tfail;tfail=tfail->fail)
                    if(tfail->mark)
                    {
                        cout<<tfail->mark<<"Found Near"<<i<<endl;
                    }
                    break;
                }
            }
            if(!tp)tp=root;
        }
    }
    bool dfs(wordnode *it)
    {
        if(it->mark)return true;
        wordnode *tp;
        for(tp=it->fail;tp;tp=tp->fail)
        {
            if(tp->mark)
            {
                it->mark=-1;
                return true;
            }
        }
        return false;
    }
}mym;
int n,nlen;
int main()
{
    freopen("1030.in","r",stdin);
    freopen("1030.out","w",stdout);
    //char cs[100001];
    char cp[1001][1001];
    //nlen=2;
    //scanf("%s",&cs[0]);
    scanf("%d",&n);
    scanf("%d",&nlen);
    mym.init();
    for each(i,n)
    {
        scanf("%s",&cp[i][0]);
        mym.insertword(cp[i],i);
    }
    mym.makefail();
    //mym.testsen(cs);
    tdp[0][1]=1;
    #define getpos(pointer) ((pointer)-mym.plist)
    #define getp(intnum) (&(mym.plist[intnum]))
    for each(ip,mym.ppl)
    {
        mym.dfs(getp(ip));
    }
    //mym.print();
    actheory::wordnode *tp;
    for every(ilen,0,nlen-1)
    {
        for each(ip,mym.ppl)
        {
            if(!tdp[ilen][ip])continue;
            for alnext(i)
            {
                for(tp=getp(ip);tp;tp=tp->fail)
                {
                    if(tp->next[i])
                    {
                        if(tp->next[i]->mark)break;
                        tdp[ilen+1][getpos(tp->next[i])]=(tdp[ilen+1][getpos(tp->next[i])]+tdp[ilen][ip])%10007;
                        //cout<<ilen+1<<","<<getpos(tp->next[i])<<"Added:"<<tdp[ilen][ip]<<endl;
                        break;
                    }
                }
                if(!tp)
                {
                    tdp[ilen+1][1]=(tdp[ilen+1][1]+tdp[ilen][ip])%10007;
                }
            }
        }
    }
    int tot=1;
    for each(i,nlen)
    {
        tot=(tot*26)%10007;
    }
    for each(ip,mym.ppl)
    {
        tot=(tot-tdp[nlen][ip])%10007;
    }
    cout<<(tot+10007)%10007<<endl;
}

