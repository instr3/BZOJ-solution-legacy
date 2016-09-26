#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=b;++i)
bool tlt[100001];
bool ttp[2][100001];
bool visit[2][321];
int n,sqrtn;
bool map[1281][1281];
int nv;
bool tchange[321];
/*void dfs(bool ix,int iy)
{
    cout<<"Dfs:"<<ix<<","<<iy<<endl;
    int tmy=iy%sqrtn;
    visit[ix][tmy]=true;
    if(tlt[iy])
    if(!visit[!ix][tmy])
    {
        dfs(!ix,iy);
    }
    if(tmy>0)
    {
        if(ttp[ix][iy-1])
        {
            if(!visit[ix][tmy-1])
            {
                dfs(ix,iy-1);
            }
        }
    }
    else tarrive[iy/sqrtn][ix][0]=true;
    if(tmy<sqrtn-1)
    {
        if(ttp[ix][iy])
        {
            if(!visit[ix][tmy+1])
            {
                dfs(ix,iy+1);
            }
        }
    }
    else tarrive[iy/sqrtn][ix][1]=true;
}
void dfsat(bool ix,int iy)
{
    memset(visit,0,sizeof visit);
    memset(tarrive[iy/sqrtn],0,sizeof tarrive[iy/sqrtn]);
    dfs(ix,iy);
}
void dfslite(bool ix1,int iy1)
{
    cout<<"Dfs:"<<ix<<","<<iy<<endl;
    int tmy=iy%sqrtn;
    visit[ix][tmy]=true;
    if(tlt[iy])
    if(!visit[!ix][tmy])
    {
        dfs(!ix,iy);
    }
    if(tmy>0)
    {
        if(ttp[ix][iy-1])
        {
            if(!visit[ix][tmy-1])
            {
                dfs(ix,iy-1);
            }
        }
    }
    else ;
    if(tmy<sqrtn-1)
    {
        if(ttp[ix][iy])
        {
            if(!visit[ix][tmy+1])
            {
                dfs(ix,iy+1);
            }
        }
    }
    else ;
}
void dfsall(int iblock)
{
    
    dfs(0,iblock*sqrtn);
    memset(tarrive[iblock],0,sizeof tarrive[iblock]);
    dfs(0,(iblock+1)*sqrtn-1);
    memset(tarrive[iblock],0,sizeof tarrive[iblock]);
    dfs(1,iblock*sqrtn);

}*/
bool blockconnecttest(bool ix,int iy,bool ix2,int iy2)
{
    //cout<<"BCT:"<<ix<<","<<iy<<endl;
    if(iy==iy2)if(ix==ix2)return true;
    int tmy=iy%sqrtn;
    visit[ix][tmy]=true;
    if(tlt[iy])
    if(!visit[!ix][tmy])
    {
        if(blockconnecttest(!ix,iy,ix2,iy2))return true;
    }
    if(tmy>0)
    {
        if(ttp[ix][iy-1])
        {
            if(!visit[ix][tmy-1])
            {
                if(blockconnecttest(ix,iy-1,ix2,iy2))return true;
            }
        }
    }
    if(tmy<sqrtn-1)
    {
        if(ttp[ix][iy])
        {
            if(!visit[ix][tmy+1])
            {
                if(blockconnecttest(ix,iy+1,ix2,iy2))return true;
            }
        }
    }
    return false;
}
void blockconnectall(bool ix,int iy)
{

    int tmy=iy%sqrtn;
    visit[ix][tmy]=true;
    if(tlt[iy])
    if(!visit[!ix][tmy])
    {
        blockconnectall(!ix,iy);
    }
    if(tmy>0)
    {
        if(ttp[ix][iy-1])
        {
            if(!visit[ix][tmy-1])
            {
                blockconnectall(ix,iy-1);
            }
        }
    }
    if(tmy<sqrtn-1)
    {
        if(ttp[ix][iy])
        {
            if(!visit[ix][tmy+1])
            {
                blockconnectall(ix,iy+1);
            }
        }
    }
}
void dfsall(int iblock)
{
    #define fadd(a,b) \
    /*cout<<"Add:"<<a<<","<<b<<endl;*/\
    map[iblock4+a][iblock4+b]=map[iblock4+b][iblock4+a]=1; \
    else map[iblock4+a][iblock4+b]=map[iblock4+b][iblock4+a]=0;
    
    int ty1=iblock*sqrtn,ty2=(iblock+1)*sqrtn-1;
    int iblock4=iblock*4-1;
    memset(visit,0,sizeof visit);
    blockconnectall(0,ty1);
    if(visit[1][0])fadd(1,2);
    //memset(visit,0,sizeof visit);
    if(visit[0][sqrtn-1])fadd(1,3);
    //memset(visit,0,sizeof visit);
    if(visit[1][sqrtn-1])fadd(1,4);
    memset(visit,0,sizeof visit);
    if(blockconnecttest(0,ty2,1,ty2))fadd(3,4);
    memset(visit,0,sizeof visit);
    blockconnectall(1,ty1);
    if(visit[1][sqrtn-1])fadd(2,4);
    //memset(visit,0,sizeof visit);
    if(visit[0][sqrtn-1])fadd(2,3);
}
int findpossiblecorner(bool ix,int iy)
{
    int iblock=iy/sqrtn;
    //int ty1=iblock*sqrtn,ty2=(iblock+1)*sqrtn-1;
    memset(visit,0,sizeof visit);
    blockconnectall(ix,iy);
    
    if(visit[0][0])return iblock*4+0;
    //memset(visit,0,sizeof visit);
    if(visit[1][0])return iblock*4+1;
    //memset(visit,0,sizeof visit);
    if(visit[0][sqrtn-1])return iblock*4+2;
    //memset(visit,0,sizeof visit);
    if(visit[1][sqrtn-1])return iblock*4+3;
    return 0;
}
bool visit2[1281];
bool mapconnecttest(int iv,int iv2)
{
    visit2[iv]=true;
    if(iv==iv2)return true;
    for every(i,iv-3,iv+3)
    {
        if(map[iv][i])
        if(!visit2[i])if(mapconnecttest(i,iv2))return true;
    }
    return false;
}
inline char getcharacter()
{
    char tc=0;
    while(tc<'A'||tc>'Z')tc=getchar();
    return tc;
}
inline int getnum()
{
    char tc=0;int res=0;
    while(tc<'0'||tc>'9')tc=getchar();
    while(tc>='0'&&tc<='9')
    {
        res=res*10+tc-'0';
        tc=getchar();
    }
    return res;
}
int main()
{
    freopen("1018.in","r",stdin);
    freopen("1018.out","w",stdout);
    scanf("%d",&n);++n;sqrtn=max((int)sqrt((double)n),2);
    nv=(n/sqrtn)*4+3;
    char tget[10];
    int pfx,pfy,ptx,pty;
    int tbf,tbt;
    int tv1,tv2;
    int tlfx=0,tlfy=0,tltx=0,tlty=0,tla=0;
    while(true)
    {
        //cout<<"New T"<<endl;
        tget[0]=getcharacter();
        
        if(tget[0]=='O')
        {
            pfx=-1;
            //scanf("%d%d%d%d",&pfx,&pfy,&ptx,&pty);
            pfx=getnum();pfy=getnum();
            ptx=getnum();pty=getnum();
            
            pfx--;ptx--;
            if(pfx>ptx)swap(pfx,ptx);
            if(pfy>pty)swap(pfy,pty);
            if(pfx==ptx)
            {
                ttp[pfx][pfy]=1;
            }
            else
            {
                tlt[pfy]=1;
            }
            tbf=pfy/sqrtn;tbt=pty/sqrtn;
            if(tbf!=tbt)
            {
                map[tbf*4+2+pfx][tbt*4+ptx]=1;
                map[tbt*4+ptx][tbf*4+2+pfx]=1;
                //cout<<"CCCC:"<<tbf*4+2+pfx<<","<<tbt*4+ptx<<endl;
            }
            else tchange[pfy/sqrtn]=true;//dfsall(pfy/sqrtn);
            tlfx=-1;
        }
        else if(tget[0]=='C')
        {
            
            //scanf("%d%d%d%d",&pfx,&pfy,&ptx,&pty);
            pfx=getnum();pfy=getnum();
            ptx=getnum();pty=getnum();
            pfx--;ptx--;
            if(pfx>ptx)swap(pfx,ptx);
            if(pfy>pty)swap(pfy,pty);
            if(pfx==ptx)
            {
                ttp[pfx][pfy]=0;
            }
            else
            {
                tlt[pfy]=0;
            }
            tbf=pfy/sqrtn;tbt=pty/sqrtn;
            if(tbf!=tbt)
            {
                map[tbf*4+2+pfx][tbt*4+ptx]=0;
                map[tbt*4+ptx][tbf*4+2+pfx]=0;
            }
            else tchange[pfy/sqrtn]=true;//dfsall(pfy/sqrtn);
            tlfx=-1;
        }
        else if(tget[0]=='A')
        {
            //scanf("%d%d%d%d",&pfx,&pfy,&ptx,&pty);
            pfx=getnum();pfy=getnum();
            ptx=getnum();pty=getnum();
            if(tlfx==pfx&&tlfy==pfy&&tltx==ptx&&tlty==pty)
            {
                
                if(tla)putchar('Y'),putchar('\n');else putchar('N'),putchar('\n');;
                continue;
            }
            tlfx=pfx,tlfy=pfy;tltx=ptx,tlty=pty;
            pfx--;ptx--;
            if(pfy>pty)
            {
                swap(pfx,ptx);
                swap(pfy,pty);
            }
            tbf=pfy/sqrtn;tbt=pty/sqrtn;
            for every(i,0,sqrtn+4)
            {
                if(tchange[i])
                {
                    dfsall(i);
                    tchange[i]=false;
                }
            }
            //if(tbf==tbt)
            //{
            //    memset(visit,0,sizeof visit);
            //    if(blockconnecttest(pfx,pfy,ptx,pty))printf("Y\n");else printf("N\n");
            //}
            //else
            {
                //memset(visit,0,sizeof visit);
                //tarr[0]=visit[0][sqrtn-1];
                //tarr[1]=visit[1][sqrtn-1];
                tv1=findpossiblecorner(pfx,pfy);
                tv2=findpossiblecorner(ptx,pty);
                if(tv1==0||tv2==0)
                {
                    memset(visit,0,sizeof visit);
                    if(blockconnecttest(pfx,pfy,ptx,pty))
                    {
                        //printf("Y\n");
                        putchar('Y');putchar('\n');
                        tla=1;
                    }
                    else
                    {
                        //printf("N\n");
                        putchar('N');putchar('\n');
                        tla=0;
                    }
                }
                else
                {
                    /*cout<<"Asking:"<<tv1<<","<<tv2<<endl;
                    for each(i,nv)cout<<i<<" ";cout<<endl;
                    for each(i,nv)
                    {
                        cout<<i<<" ";
                        for each(j,nv)
                        {
                            cout<<map[i][j]<<" ";
                        }
                        cout<<endl;
                    }*/
                    memset(visit2,0,sizeof visit2);
                    if(mapconnecttest(tv1,tv2))
                    {
                        //printf("Y\n");
                        putchar('Y');putchar('\n');
                        tla=1;
                    }
                    else
                    {
                        //printf("N\n");
                        putchar('N');putchar('\n');
                        tla=0;
                    }
                }
            }
        }
        else return 0;
    }
}
