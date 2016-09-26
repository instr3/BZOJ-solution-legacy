#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
//#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
struct wordnode
{
    wordnode *fail,*next[26];
    int count;
};
wordnode *myq[10005];int pfront=1,pback;
wordnode *root=new wordnode();
int n;
char inpas[10001];
int dp[101][10001];
void insert(char *istr,int idex)
{
    int tlen=strlen(istr);
    int tchr;
    wordnode *tp=root;
    for every(i,0,tlen-1)
    {
        tchr=istr[i]-'a';
        if(!tp->next[tchr])tp->next[tchr]=new wordnode();
        tp=tp->next[tchr];
    }
    tp->count=idex;
}
void print(wordnode *iword,int idp)
{
    //if(!iword)return;
    if(iword->count)
    {
        for each(i,idp)cout<<" ";
        cout<<"["<<iword->count<<"]"<<endl;
    }
    for each(i,26)
    {
        if(iword->next[i-1])
        {
            for each(j,idp)cout<<" ";
            if(iword->next[i-1]->fail)
            {
                /*if(iword->next[i-1]->fail!=root)
                {
                    //cout<<"|-"<<(char)(i-1+'A')<<"("<<iword->next[i-1]<<")..."<<(char)(i-1+'A')<<endl;
                    print(iword->next[i-1],idp+1);
                    continue;
                }*/
            }
            cout<<"|-"<<(char)(i-1+'A')<<"("<<iword->next[i-1]<<")"<<"..."<<iword->next[i-1]->fail<<endl;
            print(iword->next[i-1],idp+1);
        }
    }
}
void makefail()
{
    pfront=1;pback=0;
    myq[++pback]=root;
    wordnode *pt,*pfail;
    //int tchr;
    while(pfront!=pback+1)
    {
        pt=myq[pfront++];
        //cout<<"Checking:"<<pt<<endl;
        for each(i,26)
        {
            if(pt->next[i-1]!=0)
            {
                if(pt==root)
                {
                    pt->next[i-1]->fail=root;
                }
                else
                {
                    pfail=pt->fail;
                    while(pfail)
                    {
                        if(pfail->next[i-1])
                        {
                            pt->next[i-1]->fail=pfail->next[i-1];
                            break;
                        }
                        pfail=pfail->fail;
                    }
                    if(!pfail)pt->next[i-1]->fail=root;
                }
                myq[++pback]=pt->next[i-1];
            }
        }
    }
}
int main()
{
    freopen("1030.in","r",stdin);
    freopen("1030.out","w",stdout);
    int nw;
    char tc[101];
    scanf("%d%d",&nw,&n);
    for each(i,nw)
    {
        scanf("%s",&tc[0]);
        insert(&tc[0],i);
    }
    
    makefail();
    print(root,0);
    scanf("%s",&inpas[0]);
    //cout<<read()<<endl;
    
}

