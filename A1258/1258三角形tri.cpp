#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
int n;
char instr[52];
int main()
{
    freopen("1258.in","r",stdin);
    freopen("1258.out","w",stdout);
    scanf("%s",&instr[0]);
    n=strlen(instr)-1;
    if(instr[n]=='4')
    {
        instr[n]=0;
        printf("%s1\n%s2\n%s3\n",instr,instr,instr);
        return 0;
    }
    bool texist[4]={};
    char tget;
    for(int i=n;i>=1;--i)
    {
        tget=instr[i];instr[i]=0;
        if(!texist[tget-'0'])
        {
            texist[tget-'0']=true;
            printf("%s4\n",instr);
        }
    }
}
