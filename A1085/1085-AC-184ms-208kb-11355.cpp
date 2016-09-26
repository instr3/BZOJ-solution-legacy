#include <iostream>
#include <queue>
#include <map>

#define INFINIT 10000000
#define CHESS(b,p) ((((ll)b)>>(((ll)p)<<(ll)1))&(ll)3)
#define GETPOS(chess,p) (((ll)chess)<<(((ll)p)<<(ll)1))
#define ll long long

#define WHITE 0
#define BLACK 1
#define BLANK 2
#define MAXSTEP 15
//
//ll GETPOS(ll chess,ll p){
//	return chess<<(p<<1);
//}
//ll CHESS(ll b,ll p){
//	return (b>>(p<<1))&3;
//}
using namespace std;

map<ll,bool> hash;
const int fx[] = {-1,-2,-2,-1,1,2,2,1};
const int fy[] = {2,1,-1,-2,-2,-1,1,2};

ll dest = 0;
int value[25][4];
int dist[25][25];
int blackpos[12] = {0,1,2,3,4,6,7,8,9,13,14,19};
int whitepos[12] = {5,10,11,15,16,17,18,20,21,22,23,24};
int blankpos = 12;
int p[25][25];
class Board{
public:
	ll b;
	int g,f,x,y;
int H(){
		int ret = 0;
		for (int i = 0; i<25; i++)
			if (CHESS(b,i)!=BLANK)
				ret += value[i][CHESS(b,i)];
		return ret;
	}
	void move(int nx,int ny){
		int p1 = x*5+y,p2 = nx*5+ny;
		int chess = CHESS(b,p2);
		b -= GETPOS(BLANK,p1);
		b |= GETPOS(chess,p1);
		b -= GETPOS(chess,p2);
		b |= GETPOS(BLANK,p2);
		x = nx,y = ny;
	}
	friend bool operator < (const Board &a,const Board &b){
		return a.f>b.f;
	}
};
void Solve();
void InitValue(){
	for (int i = 0; i<25; i++)
		for (int j = 0; j<25; j++)
			dist[i][j] = INFINIT;
	for (int i = 0; i<25; i++)
		dist[i][i] = 0;
	for (int i = 0; i<25; i++){
		int x = i/5,y = i%5;
		for (int k = 0; k<8; k++){
			int tx = x+fx[k],ty = y+fy[k];
			if (tx>=0&&tx<5&&ty>=0&&ty<5)
				dist[i][tx*5+ty] = 1;
		}
	}
	for (int k = 0; k<25; k++)
		for (int i = 0; i<25; i++)
			for (int j = 0; j<25; j++)
				if (dist[i][k]+dist[k][j]<dist[i][j])
					dist[i][j] = dist[i][k]+dist[k][j];
	for (int i = 0; i<25; i++){
		value[i][WHITE] = value[i][BLACK] = value[i][BLANK] = INFINIT;
		for (int j = 0; j<12; j++){
			value[i][WHITE] = min(value[i][WHITE],dist[i][whitepos[j]]);
			value[i][BLACK] = min(value[i][BLACK],dist[i][blackpos[j]]);
		}
		value[i][BLANK] = dist[i][blankpos];
	}
}
void InitDest(){
	for (int j = 4; j>=0; j--)
		dest = (dest<<2)+WHITE;
	dest = (dest<<2)+BLACK;
	for (int j = 3; j>=0; j--)
		dest = (dest<<2)+WHITE;
	for (int j = 4; j>=3; j--)
		dest = (dest<<2)+BLACK;
	dest = (dest<<2)+BLANK;
	for (int j = 1; j>=0; j--)
		dest = (dest<<2)+WHITE;
	for (int j = 4; j>=1; j--)
		dest = (dest<<2)+BLACK;
	dest = (dest<<2)+WHITE;
	for (int j = 4; j>=0; j--)
		dest = (dest<<2)+BLACK;
}
void InitPos(){
	for (int i = 0; i<5; i++)
		for (int j = 0; j<5; j++){
			int x = i*5+j;
			for (int k = 0; k<8; k++){
				int tx = i+fx[k],ty = j+fy[k];
				if (tx>=0&&tx<5&&ty>=0&&ty<5)
					p[x][++p[x][0]] = tx*5+ty;
			}
		}
}
void Init(){
	int t;
	scanf("%d",&t);
	InitValue();
	InitDest();
	InitPos();
	while (t--)
		Solve();
}
int H(ll b){
		int ret = 0;
		for (int i = 0; i<25; i++)
			if (CHESS(b,i)!=BLANK)
				ret += value[i][CHESS(b,i)];
		return ret;
		/*
		for (int i = 0; i<25; i++)
			ret += (CHESS(b,i)!=CHESS(dest,i));
		return ret;
		*/
	}
ll move(ll b,int p1,int p2){
		int chess = CHESS(b,p2);
		b -= GETPOS(BLANK,p1);
		b |= GETPOS(chess,p1);
		b -= GETPOS(chess,p2);
		b |= GETPOS(BLANK,p2);
		return b;
	}
bool dfs(int x,ll b,int limit,int h,int g){
		if (b == dest) return true;
	for (int i = 1; i<=p[x][0]; i++){
			ll nb = move(b,x,p[x][i]);
			int tmp = h-value[p[x][i]][CHESS(b,p[x][i])]+value[x][CHESS(b,p[x][i])];
			if (tmp+g+1<=limit)
			if (dfs(p[x][i],nb,limit,tmp,g+1))
				return true;
		}
	return false;
}
void Solve(){
	char map[5][6];
	for (int i = 0; i<5; i++)
		scanf("%s",map[i]);
	Board start;
	start.b = start.g = start.f = 0;
	for (int i = 4; i>=0; i--)
		for (int j = 4; j>=0; j--){
			start.b = (start.b << 2) + (map[i][j] == '1'?BLACK:(map[i][j]=='0'?WHITE:BLANK));
			if (map[i][j] == '*')
				start.x = i,start.y = j;
		}
	for (int i = 1;i<=15; i++){
		if (dfs(start.x*5+start.y,start.b,i,H(start.b),0)){
			printf("%d\n",i);
			return;
		}
	}
	printf("-1\n");
}
int main(){
    freopen("1085.in","r",stdin);
    freopen("1085.out","w",stdout);
	Init();
	return 0;
}


