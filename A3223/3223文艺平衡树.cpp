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
struct tnode
{
	int w;int size;
	bool rev;
	tnode *c[2],*p;
	inline bool isrc(){return p->c[1]==this;}
	inline void setc(tnode *it,bool isrc){c[isrc]=it;if(it)it->p=this;}
	inline void relax()
	{
		if(rev)
		{
			swap(c[0],c[1]);
			if(c[0])c[0]->rev^=1;
			if(c[1])c[1]->rev^=1;
			rev=0;
		}
	}
	inline void update()
	{
		size=(c[0]?c[0]->size:0)+(c[1]?c[1]->size:0)+1;
	}
	void print(bool irelax=false,int idp=0)
	{
		if(irelax)relax();
		if(c[1])c[1]->print(irelax,idp+1);
		rep(i,idp)putchar(' ');
		printf("[%d](%d)<r:%d>\n",w,size,rev);
		if(c[0])c[0]->print(irelax,idp+1);
	}
};
tnode *buildfrom(int *arr,int il,int ir)
{
	if(il>ir)return 0;
	tnode *pt=new tnode();
	int im=(il+ir)>>1;
	pt->w=arr[im];
	pt->rev=0;
	pt->setc(buildfrom(arr,il,im-1),0);
	pt->setc(buildfrom(arr,im+1,ir),1);
	pt->update();
	return pt;
}
tnode *first(tnode *it)
{
	it->relax();
	while(it->c[0])
	{
		it=it->c[0];
		it->relax();
	}
	return it;
}
tnode *next(tnode *it)
{
	it->relax();
	if(it->c[1])return first(it->c[1]);
	while(it->p&&it->isrc())it=it->p;
	return it->p;
}
struct splaytree
{
	tnode *root;
	void rotate(tnode *it)
	{
		tnode *par=it->p;
		par->relax();
		it->relax();
		bool isrc=it->isrc();
		if(par==root){root=it;it->p=0;}else{par->p->setc(it,par->isrc());}
		par->setc(it->c[!isrc],isrc);
		it->setc(par,!isrc);
		par->update();
	}
	void splay(tnode *it,tnode *par=0)
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
	tnode *selectk(int ik)
	{
		tnode *pt=root;
		while(pt)
		{
			pt->relax();
			int tget=pt->c[0]?pt->c[0]->size:0;
			if(ik<=tget)
			{
				pt=pt->c[0];
			}
			else if(ik==tget+1)return pt;
			else
			{
				ik-=tget+1;
				pt=pt->c[1];
			}
		}
		return 0;
	}
}myt;
int n,ind[100002];
int nm;
int main()
{
	scanf("%d%d",&n,&nm);
	rep(i,n+1)ind[i]=i;
	myt.root=buildfrom(ind,0,n+1);
	//myt.root->print();
	rep(i,nm)
	{
		int tl,tr;
		scanf("%d%d",&tl,&tr);
		myt.splay(myt.selectk(tl));
		myt.splay(myt.selectk(tr+2),myt.root);
		myt.root->c[1]->c[0]->rev^=1;
		//myt.root->print();
	}
	//myt.root->print(true);
	for(tnode *p=next(first(myt.root));next(p);p=next(p))
	{
		printf("%d ",p->w);
	}
}
		
	
	
