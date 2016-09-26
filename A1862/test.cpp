#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
//#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
int main()
{
    FILE *f1,*f2;
    f1=fopen("out","r");
    f2=fopen("out2","r");
    char tc1,tc2;
    int line=1;
    while(!feof(f2))
    {
        tc1=getc(f1);
        tc2=getc(f2);
        
        if(tc1!=tc2&&tc1==' ')tc1=getc(f1);
        if(tc1=='\n')line++;
        if(tc1!=tc2)
        {
            cout<<"Err!"<<line<<endl;
            cout<<tc1<<","<<tc2<<endl;
            system("pause");
        }
    }
    cout<<"NoErr"<<endl;
}
