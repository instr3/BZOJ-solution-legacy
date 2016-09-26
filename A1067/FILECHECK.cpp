#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
FILE *f1,*f2,*ftest;
string fstring1="1067.out"
,fstring2="2.ans";
int main()
{
    ftest=fopen("flist,txt","r");

    f1=fopen(fstring1.c_str(),"r");
    f2=fopen(fstring2.c_str(),"r");
    char c1,c2;
    int tline=0;
    while(fscanf(f1,"%c",&c1)!=EOF)
    {
        fscanf(f2,"%c",&c2);
        if((int)c2==10)tline++;
        //cout<<c2;
        //cout<<":"<<(int)c2<<endl;
        //system("pause");
        //cout<<c1;
        if(c1!=c2)
        {
            cout<<c1<<","<<c2<<endl;
            cout<<"at line "<<tline<<endl;
            break;
        }
    }
    cout<<"True"<<endl;
    system("pause");
}
