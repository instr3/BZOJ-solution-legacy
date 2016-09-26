#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)

//以下为类文件game.h内容 
struct position    //位置类 
{
    int x,y;
    //int a;
};
struct key    //积木类 
{
    int map[4][4];
    position p[6];
    int nb;
    int num;
    int isrot;key *rot[4];
    int isanti;key *anti;
    key *possrot[9];int nposs;
    int rotrep[4];
    //key(int inum=-1){num=inum;}
    void antiinit()    //初始化该积木的镜像 
    {
        anti=new key();
        anti->num=num;
        for every(x,0,3)
        {
            for every(y,0,3)
            {
                anti->map[x][y]=map[3-x][y];
            }
        }
        anti->mapinit();
    }
    void rotinit(bool tdouble)    //初始化该积木的旋转
    {
        nposs=0;
        rot[0]=this;
        possrot[++nposs]=this;
        if(tdouble)antiinit(); 
        if(isanti)possrot[++nposs]=anti;
        
        for each(i,3)
        {
            rot[i]=new key();
            if(isrot==4||(isrot==2&&i==1))possrot[++nposs]=rot[i];
            rot[i]->num=num;
            for every(x,0,3)
            {
                for every(y,0,3)
                {
                    rot[i]->map[x][y]=rot[i-1]->map[3-y][x];
                }
            }
            rot[i]->mapinit();
            if(tdouble)
            {
                rot[i]->antiinit(); 
                if(isanti)possrot[++nposs]=rot[i]->anti;
            }
        }
        //cout<<num<<":"<<nposs<<endl;
        /*for each(i,nposs)
        {
            cout<<num<<","<<i<<endl;
            possrot[i]->print();
        }*/
    }
    void mapinit()    //初始化映射
    {
        bool t2nimp=false;
        for every(ix,0,3)
        {
            for every(iy,0,3)
            {
                if(map[ix][iy])
                {
                    map[ix][iy]=1;
                    if(t2nimp)
                    {
                        map[ix][iy]=9;
                    }
                    t2nimp=true;
                    ++nb;
                    p[nb].x=ix;
                    p[nb].y=iy;
                }
            }
        }
        //cout<<"Inited["<<num<<"]:"<<nb<<endl;
    }
    
    void print()    //输出
    {
        for every(x,0,3)
        {
            for every(y,0,3)
            {
                cout<<(map[x][y]?(map[x][y]==1?"O":"X"):" ");
            }
            cout<<endl;
        }
    }
};
key play[13];
struct playboard    //面板类 
{
    int map[11][11];
    /*Like this:
    ooo
    oo
    o
              */
    bool placed[13];
    int placecount;
    position p[13];
    void init()
    {
        //map[0][0]=map[0][1]=map[0][2]=map[1][0]=2;
        //print();
        for every(ix,0,9)
        {
            for every(iy,0,9-ix)
            {
                if(map[ix][iy])
                {
                    placed[map[ix][iy]]=true;
                }
            }
        }
        for each(i,12)if(placed[i])placecount++;
    }
    void print(FILE *fout)   //输出到文件 
    {
        for every(ix,0,9)
        {
            for every(iy,0,9-ix)
            {
                if(!map[ix][iy])fprintf(fout,"⊙　");
                else fprintf(fout,"◎"),fprintf(fout,(map[ix][iy]==map[ix][iy+1])?"＝":"　");
                //else cout<<"◎"<<((map[ix][iy]==map[ix][iy+1])?"≒":"　");
                
            }
            fprintf(fout,"\n");
            for every(iy,0,9-ix)
            {
                //fprintf(fout,((map[ix][iy]&&(map[ix][iy]==map[ix+1][iy]))?"‖":""));
                fprintf(fout,((map[ix][iy]&&(map[ix][iy]==map[ix+1][iy]))?"‖  ":"    "));
            }
            fprintf(fout,"\n");
        }
    }
    void print2()   //输出到屏幕 
    {
        for every(ix,0,9)
        {
            for every(iy,0,ix)
            {
                printf("%c",map[9-ix][iy]+'A'-1);
            }
            printf("\n");
        }
    }
    bool testfill(key *pkey,int tc,int ix,int iy)    //兼容性 
    {
        int tx=pkey->p[tc].x;
        int ty=pkey->p[tc].y;
        int tnx,tny;
        for each(i,pkey->nb)
        {
            tnx=ix+pkey->p[i].x-tx;
            tny=iy+pkey->p[i].y-ty;
            if(tnx<0||tny<0)return false;
            if(tnx+tny>9)return false;
            if(map[tnx][tny])
            return false;
        }
        for each(i,pkey->nb)
        {
            map[ix+pkey->p[i].x-tx][iy+pkey->p[i].y-ty]=pkey->num;
        }
        placed[pkey->num]=true;
        placecount++;
        return true;
    }
    void scanboard()    //输入原始游戏面板 
    {
        char tc[20];
        for every(ix,0,9)
        {
            scanf("%s",&tc[0]);
            for every(iy,0,ix)
            {
                map[9-ix][iy]=(tc[iy]=='.'?0:tc[iy]-'A'+1);
            }
        }
    }
    void unfill(key *pkey,int tc,int ix,int iy)    //移除积木 
    {
        int tx=pkey->p[tc].x;
        int ty=pkey->p[tc].y;
        for each(i,pkey->nb)
        {
            map[ix+pkey->p[i].x-tx][iy+pkey->p[i].y-ty]=0;
        }
        placecount--;
        placed[pkey->num]=false;
    }
}board;
void initmap()  //初始化积木映射
{
    const char inmap[16*12+1]=
/*"AA00\
A000\
0000\
0000\
BBB0\
B000\
0000\
0000\
CCCC\
0000\
0000\
0000\
DD00\
DD00\
0000\
0000\
EEEE\
E000\
0000\
0000\
FFFF\
0F00\
0000\
0000\
GGG0\
00GG\
0000\
0000\
HHH0\
H0H0\
0000\
0000\
III0\
II00\
0000\
0000\
JJJ0\
J000\
J000\
0000\
0K00\
KKK0\
0K00\
0000\
LL00\
0LL0\
00L0\
0000";*/
"AA00\
A000\
0000\
0000\
BBBB\
0000\
0000\
0000\
CCC0\
C000\
0000\
0000\
DD00\
DD00\
0000\
0000\
EEE0\
E000\
E000\
0000\
FFFF\
0F00\
0000\
0000\
GGG0\
G0G0\
0000\
0000\
HHH0\
HH00\
0000\
0000\
III0\
00II\
0000\
0000\
0J00\
JJJ0\
0J00\
0000\
KK00\
0KK0\
00K0\
0000\
LLLL\
L000\
0000\
0000";
    const int inrotatable[13]={0,4,2,4,1,4,4,4,4,4,1,4,4};
    const int inantiable [13]={0,0,0,1,0,0,1,0,1,1,0,0,1};
    //分别表示该积木有几个旋转体和几个镜像体 
    int pin=0;
    for each(i,12)
    {
        for every(ix,0,3)
        {
            for every(iy,0,3)
            {
                play[i].map[ix][iy]=(inmap[pin++]!='0');
            }
        }
        play[i].num=i;
        play[i].isrot=inrotatable[i];
        play[i].isanti=inantiable[i];
        play[i].mapinit();
        play[i].rotinit(1);
    }
}

void initgame()
{
    initmap();
    board.init();
}
//以上为类文件game.h内容 

using namespace std;
#define each(i,n) (int i=1;i<=(n);++i)
#define every(i,a,b) (int i=(a);i<=(b);++i)
//FILE *fin,*fout;
long long tot;
bool inserttest()
{
    for every(ix,0,9)
    {
        for every(iy,0,9-ix)
        {
            if(board.map[ix][iy]==8)
            {
                if(board.map[ix+1][iy+2]==8)
                {
                    return (board.map[ix][iy+1]+board.map[ix+1][iy+1]==11+8);
                }
                else
                {
                    return (board.map[ix+1][iy]+board.map[ix+1][iy+1]==11+8);
                }
            }
        }
    }
    return false;
}
bool search()
{
    if(board.placecount>=12)
    {
        //if(inserttest())return true;
        tot++;
        //if(tot%100==0)cout<<"Finish:"<<tot<<endl;
        board.print2();
        exit(0);
        return true; 
    }
    int tx=999999,ty=999999;
    for every(ix,0,9)
    {
        for every(iy,0,9-ix)
        {
            if(board.map[ix][iy]==0)
            {
                tx=ix,ty=iy;
                goto work;
            }
        }
    }
    work:; 
    for(int i=12;i>=1;--i)
    {
        //if(board.placecount==1)cout<<"Searching:"<<i<<":"<<tot<<endl;
        
        if(!board.placed[i])
        {
            for each(k,play[i].nposs)
            {
                for each(j,1)
                {
                    if(board.testfill(play[i].possrot[k],j,tx,ty))
                    {
                        search();
                        board.unfill(play[i].possrot[k],j,tx,ty);
                    }
                }
            }
        }
    }
    return false;
}
int main()
{
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    //fin=fopen("in.txt","r");
    //fout=fopen("out.txt","w");
    //if(board.testfill(&play[2],2,3,3))board.print();
    /*int tp=0;
    for every(ix,0,9)
    {
        for every(iy,0,9-ix)
        {
            if(board.map[ix][iy]==0)board.testfill(&play[(tp++)%12+1],1,ix,iy);
        }
    }
    board.print();*/
    board.scanboard();
    initgame();
    if(!search())printf("No solution");
    //cout<<tot<<endl;
    //system("pause");
    
} 
