#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
//#include <cassert>
using namespace std;
#define rep(i,n) for(int i=1;i<=(n);++i)
#define rep2(i,a,b) for(int i=(a);i<=(b);++i)
#define trimax(a,b,c) max(max((a),(b)),(c))
#define inf 2000000000
struct tnode
{
	tnode *p,*c[2];
	int w,size;
	int sum,lmax,rmax,imax;//Assume right whenever rev and same=whatever
	bool rev,same;
	inline bool isrc(){return p->c[1]==this;}
	inline void marksame(int iw)
	{
		w=iw;
		same=true;
		sum=size*w;
		lmax=rmax=imax=max(sum,w);
	}
	inline void markrev()
	{
		rev^=1;
		swap(lmax,rmax);
	}
	inline void relax()
	{
		if(rev)
		{
			swap(c[0],c[1]);
			if(c[0])c[0]->markrev();
			if(c[1])c[1]->markrev();
			rev=0;
		}
		if(same)
		{
			if(c[0])c[0]->marksame(w);
			if(c[1])c[1]->marksame(w);
			same=false;
		}
	}
	inline void update()
	{
		#define assert(condition) if(!(condition))while(1)
		assert(!rev&&!same);
		size=(c[0]?c[0]->size:0)+(c[1]?c[1]->size:0)+1;
		sum=(c[0]?c[0]->sum:0)+(c[1]?c[1]->sum:0)+w;
		lmax=max(c[0]?c[0]->lmax:-inf,(c[0]?c[0]->sum:0)+w+max(c[1]?c[1]->lmax:0,0));
		rmax=max(c[1]?c[1]->rmax:-inf,(c[1]?c[1]->sum:0)+w+max(c[0]?c[0]->rmax:0,0));
		imax=trimax(c[0]?c[0]->imax:-inf,c[1]?c[1]->imax:-inf,max(c[0]?c[0]->rmax:0,0)+w+max(c[1]?c[1]->lmax:0,0));
	}
	inline void setc(tnode *it,bool isrc)
	{
		c[isrc]=it;
		if(it)it->p=this;
	}
	inline void print(int idp=0,bool clear=false)
	{
		if(clear)relax();
		if(c[1])c[1]->print(idp+1,clear);
		rep(i,idp)putchar(' ');
		printf("[%d]%d:$%d(%d,%d,%d)<r:%d s:%d>\n",size,w,sum,lmax,imax,rmax,rev,same);
		if(c[0])c[0]->print(idp+1,clear);
	}
}pool[1000002],*ppool[1000002];int pat;
tnode *buildfrom(int *arr,int il,int ir)
{
	if(il>ir)return 0;
	tnode *it=ppool[pat++];//new tnode();
	int im=(il+ir)>>1;
	it->w=arr[im];
	it->rev=it->same=0;
	it->setc(buildfrom(arr,il,im-1),0);
	it->setc(buildfrom(arr,im+1,ir),1);
	it->update();
	return it;
}
void erasenode(tnode *&ip)
{
	if(ip==0)return;
	erasenode(ip->c[0]);
	erasenode(ip->c[1]);
	//delete ip;
	ppool[--pat]=ip;
	ip=0;
}
struct splaytree
{
	tnode *root;
	inline void rotate(tnode *it)
	{
		tnode *par=it->p;
		par->relax();
		it->relax();
		int isrc=it->isrc();
		if(par==root){root=it;it->p=0;}else par->p->setc(it,par->isrc());
		par->setc(it->c[!isrc],isrc);
		it->setc(par,!isrc);
		par->update();
	}
	inline void splay(tnode *it,tnode *par=0)
	{
		while(it->p!=par)
		{
			if(it->p->p==par)rotate(it);
			else
			{
				if(it->p->isrc()==it->isrc())
				{
					rotate(it->p);rotate(it);
				}
				else
				{
					rotate(it);rotate(it);
				}
			}
		}
		it->update();
	}
	tnode* selectk(int ik)
	{
		tnode *tp=root;
		while(tp)
		{
			tp->relax();
			int tget=tp->c[0]?tp->c[0]->size:0;
			if(ik<=tget)
			{
				tp=tp->c[0];
			}
			else if(ik==tget+1)return tp;
			else
			{
				ik-=tget+1;
				tp=tp->c[1];
			}
		}
		return 0;
	}
}myt;
int ind[500002];
int n,nm;
int main()
{
	scanf("%d%d",&n,&nm);
	rep(i,n)scanf("%d",&ind[i]);
	rep2(i,0,1000001)ppool[i]=pool+i;
	ind[0]=0;
	ind[n+1]=0;
	myt.root=buildfrom(ind,0,n+1);
	rep(im,nm)
	{
		char ts[19];
		scanf("%s",ts);
		if(ts[0]=='I')//insert after a
		{
			int tp;
			scanf("%d%d",&tp,&n);
			if(n==0)continue;
			rep(i,n)scanf("%d",&ind[i]);
			myt.splay(myt.selectk(tp+1));
			myt.splay(myt.selectk(tp+2),myt.root);
			myt.root->c[1]->setc(buildfrom(ind,1,n),0);
			myt.root->c[1]->update();
			myt.root->update();
		}
		else if(ts[0]=='D')//a-b delete
		{
			int tp;
			scanf("%d%d",&tp,&n);
			myt.splay(myt.selectk(tp));
			myt.splay(myt.selectk(tp+n+1),myt.root);
			erasenode(myt.root->c[1]->c[0]);
			myt.root->c[1]->update();
			myt.root->update();
		}
		else if(ts[2]=='K')//a-b makesame
		{
			int tp,tc;
			scanf("%d%d%d",&tp,&n,&tc);
			myt.splay(myt.selectk(tp));
			myt.splay(myt.selectk(tp+n+1),myt.root);
			if(myt.root->c[1]->c[0])myt.root->c[1]->c[0]->marksame(tc);
			myt.root->c[1]->update();
			myt.root->update();
		}
		else if(ts[0]=='R')//a-b reverse
		{
			int tp;
			scanf("%d%d",&tp,&n);
			myt.splay(myt.selectk(tp));
			myt.splay(myt.selectk(tp+n+1),myt.root);
			if(myt.root->c[1]->c[0])myt.root->c[1]->c[0]->markrev();
			myt.root->c[1]->update();
			myt.root->update();
		}
		else if(ts[0]=='G')//a-b sum
		{
			int tp;
			scanf("%d%d",&tp,&n);
			myt.splay(myt.selectk(tp));
			//myt.selectk(tp)->print();
			//myt.root->print(0,true);
			myt.splay(myt.selectk(tp+n+1),myt.root);
			printf("%d\n",myt.root->c[1]->c[0]?myt.root->c[1]->c[0]->sum:0);
		}
		else if(ts[2]=='X')//max continues sum
		{
			myt.splay(myt.selectk(1));
			myt.splay(myt.selectk(myt.root->size),myt.root);
			printf("%d\n",myt.root->c[1]->c[0]->imax);
		}
		//myt.root->print(0,true);
	}
	//int tarr[11]={1,-3,5,-7,2,-4,6,-8};
	//myt.root=buildfrom(tarr,0,7);
	//myt.root->print();
}
