/* ***********************************************
Author        :kuangbin
Created Time  :2014/9/30 8:13:45
File Name     :E:\2014ACM\专题学习\数据结构\ScapeGoatTree\BZOJ3224.cpp
************************************************ */

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int MAXN = 200010;
const double alpha = 0.75;
struct Node{
	Node *ch[2];
	int size,key,nodeCount;
	bool exist;
	bool isBad(){
		return ch[0]->nodeCount > alpha*nodeCount + 5 || ch[1]->nodeCount > alpha*nodeCount + 5;
	}
	void push_up(){
		size = exist + ch[0]->size + ch[1]->size;
		nodeCount = 1 + ch[0]->nodeCount + ch[1]->nodeCount;
	}
};
struct ScapeGoatTree{
	Node pool[MAXN];
	Node *tail,*root,*null;
	Node *bc[MAXN];//内存回收
	int bc_top;
	void init(){
		tail = pool;
		null = tail++;
		null->ch[0] = null->ch[1] = null;
		null->size = null->key = null->nodeCount = 0;
		root = null;
		bc_top = 0;
	}
	inline Node *newNode(int key){
		Node *p;
		if(bc_top)p = bc[--bc_top];
		else p = tail++;
		p->ch[0] = p->ch[1] = null;
		p->size = 1;
		p->key = key;
		p->nodeCount = 1;
		p->exist = true;
		return p;
	}
	inline void Travel(Node *p,vector<Node *>&v){
		if(p == null)return;
		Travel(p->ch[0],v);
		if(p->exist)v.push_back(p);
		else bc[bc_top++] = p;
		Travel(p->ch[1],v);
	}
	inline Node *divide(vector<Node *>&v,int l,int r){
		if(l >= r)return null;
		int mid = (l+r)/2;
		Node *p = v[mid];
		p->ch[0] = divide(v,l,mid);
		p->ch[1] = divide(v,mid+1,r);
		p->push_up();
		return p;
	}
	inline void rebuild(Node *&p){
		vector<Node *>v;
		Travel(p,v);
		p = divide(v,0,v.size());
	}
	Node **insert(Node *&p,int val){
		if(p == null){
			p = newNode(val);
			return &null;
		}
		else {
			p->size++;
			p->nodeCount++;
			int d = (val >= p->key);
			Node **res = insert(p->ch[d],val);
			if(p->isBad())res = &p;
			return res;
		}
	}
	//插入一个值为val的点
	void insert(int val){
		Node **p = insert(root,val);
		if(*p != null)rebuild(*p);
	}
	//删除第id个点
	void erase(Node *p,int id){
		if(p->exist && id == p->ch[0]->size+1){
			p->exist = 0;
			p->size--;
			return;
		}
		p->size--;
		if(id <= p->ch[0]->size+p->exist)
			erase(p->ch[0],id);
		else erase(p->ch[1],id - p->ch[0]->size - p->exist);
	}
	//查询小于val的数的个数+1
	int rank(int val){
		Node *now = root;
		int ans = 1;
		while(now != null){
			if(now->key >= val)now = now->ch[0];
			else {
				ans += now->ch[0]->size + now->exist;
				now = now->ch[1];
			}
		}
		return ans;
	}
	int get_kth(int k){
		Node *now = root;
		while(now != null){
			if(now->exist && k == now->ch[0]->size+1)
				return now->key;
			else if(now->ch[0]->size >= k)now = now->ch[0];
			else {
				k -= now->ch[0]->size + now->exist;
				now = now->ch[1];
			}
		}
	}
	//删除一个值为val的点
	void erase(int val){
		erase(root,rank(val));
		if(root->size < alpha*root->nodeCount)
			rebuild(root);
	}
}tree;

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
	while(scanf("%d",&n) == 1){
		tree.init();
		int op,x;
		while(n--){
			scanf("%d%d",&op,&x);
			if(op == 1)tree.insert(x);
			else if(op == 2) tree.erase(x);
			else if(op == 3)printf("%d\n",tree.rank(x));
			else if(op == 4)printf("%d\n",tree.get_kth(x));
			else if(op == 5)printf("%d\n",tree.get_kth(tree.rank(x)-1));
			else printf("%d\n",tree.get_kth(tree.rank(x+1)));

		}
	}
    return 0;
}
