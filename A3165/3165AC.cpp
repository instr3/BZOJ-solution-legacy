#include<stdio.h>

#define if if (
#define then )
#define do )
#define for for (
#define while while (
#define begin {
#define end }

int n,i,ii,tot,k,lastans,t,xx0,xx1,yy0,yy1,op,x0,y0,x1,y1,ans[40000];
double tmp,t2,ansy[40000];

int main()
begin
freopen("segment.in","r",stdin);
freopen("segment.out","w",stdout);
	scanf("%d",&n);
	lastans=0;
	for ii=1;ii<=n;ii++ do begin
		scanf("%d",&op);
		if op==0 then begin
			scanf("%d",&k);
			k=(k+lastans-1)%39989+1;
			printf("%d\n",lastans=ans[k]);
		end else if op==1 then begin
			scanf("%d%d%d%d",&xx0,&yy0,&xx1,&yy1);
			++tot;
			x0=(xx0+lastans-1)%39989+1;
			y0=(yy0+lastans-1)%1000000000+1;
			x1=(xx1+lastans-1)%39989+1;
			y1=(yy1+lastans-1)%1000000000+1;
			if x1<x0 then begin
				t=x1;x1=x0;x0=t;
				t=y1;y1=y0;y0=t;
			end;
			t2=(y1-y0)/(x1-x0+0.0);
			tmp=y0;
			for i=x0;i<=x1;i++ do begin
				if tmp>ansy[i] then begin
					ansy[i]=tmp;ans[i]=tot;
				end;
				tmp+=t2;
			end;
		end;
	end;
end
