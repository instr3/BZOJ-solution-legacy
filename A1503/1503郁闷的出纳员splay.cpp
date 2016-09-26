#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define rep(i,n) for(int i=1;i<=(n);++i)
#define rep2(i,a,b) for(int i=(a);i<=(b);++i)
struct tnode
{
	int w,size;
	int add;
	tnode *p,*c[2];
	bool isrc(){return p->c[1]==this;}
	void setc(tnode *it,int isrc){c[isrc]=it;if(it)it->p=this;}
	void relax()
	{
		if(add)
		{
			if(c[0])c[0]->add+=add;
			if(c[1])c[1]->add+=add;
			w+=add;
			add=0;
		}
	}
	void update()
	{
		size=(c[0]?c[0]->size:0)+(c[1]?c[1]->size:0)+1;
	}
	void print(bool needrelax=false,int idp=0)
	{
		if(needrelax)relax();
		if(c[1])c[1]->print(needrelax,idp+1);
		rep(i,idp)putchar(' ');
		printf("[%d](%d)<a:%d>\n",w,size,add);
		if(c[0])c[0]->print(needrelax,idp+1);
	}
};
tnode *buildnode[2];
tnode *buildfrom(int *tarr,int il,int ir,bool record=false)
{
	if(il>ir)return 0;
	tnode *tp=new tnode();
	int im=(il+ir)>>1;
	if(record)buildnode[im]=tp;
	tp->w=tarr[im];
	tp->add=0;
	tp->setc(buildfrom(tarr,il,im-1,record),0);
	tp->setc(buildfrom(tarr,im+1,ir,record),1);
	tp->update();
	return tp;
}
tnode *selectless(tnode *it,int iw)
{
	if(it==0)return 0;
	it->relax();
	if(it->w<iw)
	{
		tnode *res=selectless(it->c[1],iw);
		return res?res:it;
	}
	else return selectless(it->c[0],iw);
}
int totdelete;
void erasenode(tnode *&it)
{
	if(it==0)return;
	erasenode(it->c[0]);
	erasenode(it->c[1]);
	delete it;
	++totdelete;
	it=0;
}
tnode *first(tnode *it)
{
	while(it->c[0])it=it->c[0];return it;
}
tnode *next(tnode *it)
{
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
		int isrc=it->isrc();
		if(par==root){root=it;it->p=0;}else{par->p->setc(it,par->isrc());}
		par->setc(it->c[!isrc],isrc);
		it->setc(par,!isrc);
		par->update();
	}
	tnode *splay(tnode *it,tnode *par=0)
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
		return it;
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
}myt;
int n,nmin;
int main()
{
	int tarr[2]={-1000000001,1000000001};
	myt.root=buildfrom(tarr,0,1,true);
	scanf("%d%d",&n,&nmin);
	rep(i,n)
	{
		char top[2];
		tnode *tp;
		scanf("%s",top);
		int tn;
		switch(top[0])
		{
		case 'A':
		case 'S':
			scanf("%d",&tn);
			if(top[0]=='S')tn=-tn;
			myt.splay(buildnode[0]);
			myt.splay(buildnode[1],buildnode[0]);
			if(buildnode[1]->c[0])
			{
				buildnode[1]->c[0]->add+=tn;
				//there is no need to update other nodes.
			}
			tp=next(selectless(myt.root,nmin));
			myt.splay(tp,buildnode[0]);
			erasenode(tp->c[0]);
			tp->update();
			buildnode[0]->update();
			break;
		case 'I':
			scanf("%d",&tn);
			if(tn<nmin)continue;
			tp=selectless(myt.root,tn);
			myt.splay(tp);
			myt.splay(next(tp),tp);
			tp->c[1]->setc(buildfrom(&tn,0,0),0);
			tp->c[1]->update();
			tp->update();
			break;
		case 'F':
			scanf("%d",&tn);
			tp=myt.selectk(myt.root->size-tn);
			if(tp&&tp!=buildnode[0])
			{
				printf("%d\n",tp->w);
			}
			else printf("-1\n");
			break;
		}
		//myt.root->print();
	}
	printf("%d\n",totdelete);
	/*
	int arr[101];
	rep(i,15)arr[i]=i;
	myt.root=buildfrom(arr,1,15);
	myt.splay(selectless(myt.root,2));
	for(tnode *p=first(myt.root);p;p=next(p))
	p->print();*/
	
}
