#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <cmath>
#include <algorithm>
#include <iostream>
#define si set<Tpoint>::iterator
#define PII pair<int, int>
using namespace std;
const int MAXN = 200001;
const double eps = 1e-7;
int n = 50000;
int dcmp(double a)
{
if (fabs(a) < eps) return 0;
return a < 0 ? -1 : 1;
}
struct Tsgt{
double A[MAXN << 2], B[MAXN << 2];
void same(int idx, double _A, double _B)
{
A[idx] = _A; B[idx] = _B;
}
void push(int l, int r, int idx)
{
int m = l + r >> 1;
if (B[idx] > 0){
same(idx * 2, A[idx], B[idx]);
same(idx * 2 + 1,  A[idx] + B[idx] * (m - l + 1), B[idx]);
A[idx] = 0; B[idx] = 0;
}
}
void makesame(int idx, int l, int r, int ll, int rr, double _A, double _B)
{
if (ll <= l && rr >= r) { same(idx, _A + _B * (l - 1), _B); return; }
int m = l + r >> 1;
push(l, r, idx);
if (ll <= m) makesame(idx * 2, l, m, ll, rr, _A, _B);
if (rr > m) makesame(idx * 2 + 1, m + 1, r, ll, rr, _A, _B);
}
double get(int idx, int l, int r, int x)
{
if (l == r) return A[idx];
int m = l + r >> 1;
push(l, r, idx);
if (x <= m) return get(idx * 2, l, m, x); else return get(idx * 2 + 1, m + 1, r, x);
}
} sgt;
struct Tpoint{
double x, y;
Tpoint() { }
Tpoint(double _x, double _y) { x = _x; y = _y; }
bool error() { return x > 1e50; }
Tpoint operator - (Tpoint A)
{
Tpoint temp; temp.x = x - A.x; temp.y = y - A.y;
return temp;
}
double operator * (Tpoint A)
{
return x * A.y - y * A.x;
}
bool operator < (const Tpoint & A) const
{
return dcmp(x - A.x) < 0;
}
bool operator == (const Tpoint & A) const
{
return (dcmp(x - A.x) == 0);
}
} error;
struct Thull{
set<Tpoint> hull;
double calc_k(Tpoint A, Tpoint B)
{
return (A.y - B.y) / (A.x - B.x);
}
Tpoint lower(Tpoint A) //ret >= A
{
si SI = hull.lower_bound(A);
if (SI == hull.end()) return error; else return *SI;
}
Tpoint next(Tpoint A) //ret > A
{
si SI = hull.upper_bound(A);
if (SI == hull.end()) return error; else return *SI;
}
Tpoint pre(Tpoint A) //ret < A
{
si SI = hull.lower_bound(A);
if (SI == hull.begin()) return error; else return *(--SI);
}
PII insert(Tpoint a)
{
if (hull.size() == 0) { hull.insert(a); return make_pair(1, n); }
Tpoint d1 = pre(a), d2 = lower(a);
if (d1.error() && d2.y > a.y) return make_pair(0, -1); 
if ((!d1.error()) && (!d2.error()) && (dcmp((d2 - d1) * (a - d1)) < 0)) return make_pair(0, -1);
if (d2 == a) hull.erase(d2);
Tpoint p1 = a, p2 = next(a);
while(1){
p1 = p2; p2 = next(p2);
if (p1.error() || p2.error()) break;
if (dcmp((p1 - a) * (p2 - a)) < 0) break;
hull.erase(p1);
}
p1 = a; p2 = pre(a);
while(1){
p1 = p2; p2 = pre(p2);
if (p1.error() || p2.error()) break;
if (dcmp((p1 - a) * (p2 - a)) > 0) break;
hull.erase(p1);
}
hull.insert(a);
d1 = pre(a); d2 = next(a);
PII temp(1, n);
if (!d1.error()) temp.first = max(temp.first, (int)ceil(-calc_k(d1, a)) + 1);
if (!d2.error()) temp.second = min(temp.second, (int)floor(-calc_k(a, d2)) + 1);
return temp; 
}
} hull;
int Q;
int main()
{
#ifndef ONLINE_JUDGE
freopen("1568.in", "r", stdin); freopen("1568.out", "w", stdout);
#endif
error.x = 1e99;
hull.insert(Tpoint(0, 0));
scanf("%d", &Q);
for (int i = 1; i <= Q; i++){
scanf(" "); char op[101]; double A, B; int x; 
scanf("%s", op);
switch(*op){
case 'Q' : scanf("%d", &x); printf("%d\n", int(floor(sgt.get(1, 1, n, x) / 100.0))); break;
case 'P' : scanf("%lf%lf", &A, &B); PII temp = hull.insert(Tpoint(B, A)); 
  if (temp.first > temp.second) break;
  sgt.makesame(1, 1, n, temp.first, temp.second, A, B);
  break;
}
}
}
