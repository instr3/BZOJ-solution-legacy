#include <io.h>
#include <stdio.h>
#include <stdlib.h>
bool checkfile(const char *filename)
{
    if(_access(filename,0)==-1)
    {
        return false;
    }
    return true;
}
int indata[10001];
int n=1;
int main()
{
    while(scanf("%d",&indata[n]),indata[n]!=-1)
    {
        ++n;
    }
    --n;
    char tc[11]={};
    tc[0]='A';
    for(int i=1;i<=n;++i)
    {
        itoa(indata[i],&tc[1],10);
        if(!checkfile(tc))
        {
            printf("File %s Missing.\n",tc);
        }
    }
    system("pause");
}
