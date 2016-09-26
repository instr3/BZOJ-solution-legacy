#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
bool vis[101][101];
int f[101][101];
char s[101];
int dp(int l, int r)
{
if (l == r) return 1; if (l > r) return 0;
if (vis[l][r]) return f[l][r];
int & x = f[l][r]; x = 0x3f3f3f3f;
vis[l][r] = true;
if (s[l] == s[r]) x = min(x, dp(l + 1, r - 1) + 1);
for (int i = l; i < r; i++) x = min(x, dp(l, i) + dp(i + 1, r));
if (s[l] != s[r]) return x;
for (int i = l + 1; i < r; i++) if (s[l] == s[i]) 
x = min(x, dp(l, i) + dp(i + 1, r - 1));
return x;
}
int main()
{

freopen("1260.in", "r", stdin); freopen("1260.out", "w", stdout);

scanf("%s", s);
printf("%d\n", dp(0, strlen(s) - 1));
}
