#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define rc1(i) rcount1[(i)+100000]
#define rc2(i) rcount2[(i)+100000]
int data[100001];
int counts[100001];
int rcount1[200001];
int rcount2[200001];
int main()
{
    int tn;
    int n,nt;scanf("%d%d",&n,&nt);
    for each(i,n){scanf("%d",&data[i]);if(data[i]==nt)tn=i;}
    for(int i=tn-1;i>=1;--i)counts[i]=counts[i+1]+(data[i]>nt?1:-1),++rc1(counts[i]);
    for(int i=tn+1;i<=n;++i)counts[i]=counts[i-1]+(data[i]>nt?1:-1),++rc2(counts[i]);
    int tot=0;
    rc1(0)++;rc2(0)++;
    for each(i,n)tot=tot+rc1(i)*rc2(-i)+rc2(i)*rc1(-i);
    tot=tot+rc1(0)*rc2(0);
    cout<<tot;
    system("pause");
}
    
