#include <cstdio> 
int e[20],f[1020][256][16],i,k,j,sta,sp,qq,lmt,a[1020],b[1020],n,val; 
  
int main() 
{ 
    freopen("1226.in","r",stdin);
    freopen("1226.out","w",stdout);
//  freopen("input.in","r",stdin); 
//  freopen("output.out","w",stdout); 
    e[0]=1; 
    sp=8; 
    for (i=1; i<=7; ++i) e[i]=e[i-1]<<1; 
    for (scanf("%d",&qq); qq; --qq) 
    { 
        scanf("%d",&n); 
        for (i=1; i<=n; ++i) scanf("%d%d",&a[i],&b[i]); 
        for (i=n+1; i<=n+10; ++i) b[i]=-1; 
        for (i=1; i<=n+10; ++i) 
        for (sta=0; sta<256; ++sta) 
        for (k=0; k<=15; ++k) f[i][sta][k]=1000000007; 
        f[1][0][sp-1]=0; 
        for (i=1; i<=n; ++i) 
        for (sta=0; sta<256; ++sta) 
        for (k=-8; k<=7; ++k) 
        if (f[i][sta][sp+k]<1000000007) 
        { 
//          printf("get f[%d][%d][%d]=%d\n",i,sta,k,f[i][sta][sp+k]); 
            if (sta&1) 
            { 
                if (f[i][sta][sp+k]<f[i+1][sta/2][sp+k-1]) f[i+1][sta/2][sp+k-1]=f[i][sta][sp+k]; 
                continue; 
            } 
            lmt=i+b[i]; 
            for (j=1; j<=7; ++j) 
              if ((sta|e[j])!=sta && i+j+b[i+j]<lmt) lmt=i+j+b[i+j]; 
            for (j=i; j<=lmt; ++j) 
            if ((sta|e[j-i])!=sta) 
            { 
    //          printf("meiju j=%d\n",j);  
                if (i+k==0) val=0; else val=a[i+k]^a[j];  
    //          printf("val=%d\n",val); 
                if (j==i) 
                { 
                    if (f[i][sta][sp+k]+val<f[i+1][sta/2][sp-1]) f[i+1][sta/2][sp-1]=f[i][sta][sp+k]+val; 
                } else
                if (f[i][sta][sp+k]+val<f[i][sta+e[j-i]][sp+j-i]) f[i][sta+e[j-i]][sp+j-i]=f[i][sta][sp+k]+val; 
            } 
        } 
        j=1000000007; 
        for (k=0; k<=15; ++k) 
        if (f[n+1][0][k]<j) j=f[n+1][0][k]; 
        printf("%d\n",j); 
    } 
    return 0; 
}
