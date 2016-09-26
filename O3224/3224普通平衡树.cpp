#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cassert>
using namespace std;
#define rep(i,n) for(int i=1;i<=(n);++i)
#define rep2(i,a,b) for(int i=(a);i<=(b);++i)
struct tnode
{
	int w;
	int size;
	tnode *c[2],*p;
	inline bool isrc(){return p->c[1]==this;}
	inline void setc(tnode *it,bool isrc){c[isrc]=it;if(it)it->p=this;}
	inline void relax()
	{
		
	}
	inline void update()
	{
		size=(c[0]?c[0]->size:0)+(c[1]?c[1]->size:0)+1;
	}
	void print(int idp=0)
	{
		if(c[1])c[1]->print(idp+1);
		rep(i,idp)putchar(' ');
		printf("[%d](%d)\n",w,size);
		if(c[0])c[0]->print(idp+1);
	}
};
tnode *buildfrom(int *arr,int il,int ir)
{
	if(il>ir)return 0;
	int im=(il+ir)>>1;
	tnode *it=new tnode();
	it->w=arr[im];
	it->setc(buildfrom(arr,il,im-1),0);
	it->setc(buildfrom(arr,im+1,ir),1);
	it->update();
	return it;
}
tnode *first(tnode *it)
{
	while(it->c[0])it=it->c[0];return it;
}
tnode *last(tnode *it)
{
	while(it->c[1])it=it->c[1];return it;
}
tnode *next(tnode *it)
{
	if(it->c[1])return first(it->c[1]);
	while(it->p&&it->isrc())it=it->p;
	return it->p;
}
tnode *prev(tnode *it)
{
	if(it->c[0])return last(it->c[0]);
	while(it->p&&!it->isrc())it=it->p;
	return it->p;
}
void erase(tnode *&it)
{
	if(it==0)return;
	erase(it->c[1]);
	erase(it->c[0]);
	delete it;
	it=0;
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
				if(it->isrc()==it->p->isrc())
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
	tnode *lowerbound(tnode *it,int iw)
	{
		it->relax();
		if(it==0)return 0;
		if(it->w>=iw)
		{
			tnode *res=lowerbound(it->c[0],iw);
			return res?res:it;
		}
		else return lowerbound(it->c[1],iw);
	}
	tnode *upperbound(tnode *it,int iw)
	{
		it->relax();
		if(it==0)return 0;
		if(it->w>iw)
		{
			tnode *res=upperbound(it->c[0],iw);
			return res?res:it;
		}
		else return upperbound(it->c[1],iw);
	}
}myt;
int n;
int main()
{
	int tarr[2]={-1999999999,1999999999};
	myt.root=buildfrom(tarr,0,1);
	scanf("%d",&n);
	rep(i,n)
	{
		int top,tx;
		tnode *it;
		scanf("%d%d",&top,&tx);
		switch(top)
		{
		case 1:
			it=prev(myt.upperbound(myt.root,tx));
			myt.splay(it);
			myt.splay(next(it),it);
			it->c[1]->setc(buildfrom(&tx,0,0),0);
			it->c[1]->update();
			it->update();
			break;
		case 2:
			it=myt.lowerbound(myt.root,tx);
			if(it->w!=tx)break;
			it=prev(it);
			myt.splay(it);
			myt.splay(next(next(it)),it);
			erase(it->c[1]->c[0]);
			it->c[1]->update();
			it->update();
			break;
		case 3:
			it=myt.lowerbound(myt.root,tx);
			myt.splay(it);
			printf("%d\n",it->c[0]->size);
			break;
		case 4:
			printf("%d\n",myt.selectk(tx+1)->w);
			break;
		case 5:
			printf("%d\n",prev(myt.lowerbound(myt.root,tx))->w);
			break;
		case 6:
			printf("%d\n",myt.upperbound(myt.root,tx)->w);
			break;
		}
		//myt.root->print();
	}
	/*
	int tarr[13];
	rep(i,12)tarr[i]=i*10;
	myt.root=buildfrom(tarr,0,12);
	myt.root->print();
	myt.lowerbound(myt.root,3)->print();*/
}
