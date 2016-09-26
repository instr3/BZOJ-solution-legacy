#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cassert>
using namespace std;
#define rep(i,n) for(int i=1;i<=(n);++i)
#define rep2(i,a,b) for(int i=(a);i<=(b);++i)
double tdp[100011];
int n;
double na[100011],nb[100011],rate[100011];

double tk[100011];
double tx[100011],ty[100011];
//int sortk[100011];
int sortp[100011];
int tstk[100011],pstk;
int stemp[100011];
int memsortk[20][100011];
/*inline bool cmpk(int ia,int ib)
{
	return tk[ia]>tk[ib];
}*/
void prepartition(int il,int ir,int idp)
{
	if(il+1==ir)
	{
		memsortk[idp][il]=il;
		return;
	}
	int im=(il+ir)>>1;
	prepartition(il,im,idp+1);
	prepartition(im,ir,idp+1);
	for(int p1=il,p2=im,p3=il;p3<ir;++p3)
	{
		if(p1!=im&&(p2==ir||tk[memsortk[idp+1][p1]]>tk[memsortk[idp+1][p2]]))memsortk[idp][p3]=memsortk[idp+1][p1++];else memsortk[idp][p3]=memsortk[idp+1][p2++];
	}
}
void partition(int il,int ir,int idp) // [il,ir)
{
	if(il+1==ir)
	{
		assert(sortp[il]==il);
		tdp[il]=max(tdp[il],tdp[il-1]);
		tx[il]=tdp[il]/(rate[il]*na[il]+nb[il]);
		ty[il]=tdp[il]*rate[il]/(rate[il]*na[il]+nb[il]);
		return;
	}
	int im=(il+ir)>>1;
	partition(il,im,idp+1);
	tstk[pstk=1]=il;
	rep2(i,il+1,im-1)
	{
		while(pstk>=2)//Make a convex hull
		{
			int ta=sortp[tstk[pstk-1]],tb=sortp[tstk[pstk]],tc=sortp[i];
			if(abs((tx[tb]-tx[ta])*(ty[tc]-ty[tb])-(tx[tc]-tx[tb])*(ty[tb]-ty[ta]))>1e-8)
			if((tx[tb]-tx[ta])*(ty[tc]-ty[tb])-(tx[tc]-tx[tb])*(ty[tb]-ty[ta])<=0)break;
			--pstk;
		}
		tstk[++pstk]=i;
	}
	int tp=1;
	#define calc(j,i) ((-tk[i]*tx[j]+ty[j])*na[i])
	//This is O(n log^2 n) approach
	//n log^2 n 1012ms 8308 kb
	//n log n 968ms 15728 kb
	//
	//rep2(i,im,ir-1)stemp[i]=sortk[i];
	//sort(sortk+im,sortk+ir,cmpk);
	#define sortk memsortk[idp+1]
	rep2(i,im,ir-1)
	{
		while(tp<pstk&&calc(sortp[tstk[tp]],sortk[i])<calc(sortp[tstk[tp+1]],sortk[i]))
		{
			++tp;
		}
		tdp[sortk[i]]=max(tdp[sortk[i]],calc(sortp[tstk[tp]],sortk[i]));
	}
	#undef sortk
	partition(im,ir,idp+1);
	
	#define cmp(a,b) (tx[a]<tx[b])
	for(int p1=il,p2=im,p3=il;p3<ir;++p3)
	{
		if(p1!=im&&(p2==ir||cmp(sortp[p1],sortp[p2])))stemp[p3]=sortp[p1++];else stemp[p3]=sortp[p2++];
	}
	rep2(i,il,ir-1)sortp[i]=stemp[i];
}
int main()
{
	scanf("%d%lf",&n,&tdp[0]);
	rep(i,n)scanf("%lf%lf%lf",&na[i],&nb[i],&rate[i]);
	rep(i,n)
	{
		tk[i]=-nb[i]/na[i];
	}
	tdp[1]=tdp[0];
	rep(i,n)sortp[i]=i;
	prepartition(1,n+1,0);
	partition(1,n+1,0);
	printf("%.3lf\n",tdp[n]);
	return 0;
	//This is O(n^2) approach
	double ttdp[100011];
	ttdp[0]=tdp[0];
	rep(i,n)
	{
		ttdp[i]=ttdp[i-1];
		rep(j,i-1)
		{
			ttdp[i]=max(ttdp[i],ttdp[j]*(rate[j]*na[i]+nb[i])/(rate[j]*na[j]+nb[j]));
		}
	}
	printf("%.3lf\n",ttdp[n]);
}
