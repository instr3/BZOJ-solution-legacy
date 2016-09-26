#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
FILE *f1=fopen("1562.out","r"),
 *f2=fopen("stdout.cpp","r");
int main()
{
    char tc1,tc2;
    int tline=0;
    while(!feof(f2))
    {
        tc1=getc(f1);
        tc2=getc(f2);
        if(tc1==' ')++tline;
        if(tc1!=tc2)
        {
            cout<<"Error @ Line "<<tline<<endl;
            system("pause");
        }
    }
    cout<<"Right"<<endl;
    system("pause");
}
