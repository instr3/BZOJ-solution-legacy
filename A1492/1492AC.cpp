#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

#define MAXN 100000
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define INFINITE 1e10
#define EPS 1e-8
using namespace std;

int n;
double f[MAXN + 1];
double A[MAXN + 1], B[MAXN + 1], Rate[MAXN + 1];
double X[MAXN + 1], Y[MAXN + 1];
void Init()
{
    scanf("%d%lf", &n, &f[1]);
    for (int i = 1; i <= n; i ++)
        scanf("%lf%lf%lf", &A[i], &B[i], &Rate[i]);
}

class SplayNode
{
    public:
        int lt, rt, fa;
        double x, y;
};
SplayNode node[MAXN + 1];
int cntNode = 0;
double CrossProduct(double x0, double y0, double x1, double y1, double x2, double y2)
{
    return (x1 - x0) * (y2 - y0) - (y1 - y0) * (x2 - x0);
}
double CrossProduct(int a, int b, int c)
{
    return CrossProduct(node[a].x, node[a].y, 
            node[b].x, node[b].y, 
            node[c].x, node[c].y);
}

class SplayTree
{
    private:
        int root;
        void RightRotate(int x)
        {
            int lc = node[x].lt, fa = node[x].fa;
            node[x].lt = node[lc].rt; node[node[x].lt].fa = x;
            node[lc].rt = x, node[x].fa = lc;
            if (fa)
            {
                if (x == node[fa].lt)
                    node[fa].lt = lc;
                else
                    node[fa].rt = lc;
            }
            node[lc].fa = fa;
        }
        void LeftRotate(int x)
        {
            int rc = node[x].rt, fa = node[x].fa;
            node[x].rt = node[rc].lt; node[node[x].rt].fa = x;
            node[rc].lt = x, node[x].fa = rc;
            if (fa)
            {
                if (x == node[fa].lt)
                    node[fa].lt = rc;
                else
                    node[fa].rt = rc;
            }
            node[rc].fa = fa;
        }
        void Splay(int x, int FA)
        {
            int fa, Fa;
            while (node[x].fa != FA)
            {
                fa = node[x].fa;
                Fa = node[fa].fa;
                if (Fa == FA)
                {
                    if (x == node[fa].lt)
                        RightRotate(fa);
                    else
                        LeftRotate(fa);
                }
                else
                {
                    if (x == node[fa].lt)
                    {
                        if (fa == node[Fa].lt)
                        {
                            RightRotate(Fa);
                            RightRotate(fa);
                        }
                        else
                        {
                            RightRotate(fa);
                            LeftRotate(Fa);
                        }
                    }
                    else
                    {
                        if (fa == node[Fa].rt)
                        {
                            LeftRotate(Fa);
                            LeftRotate(fa);
                        }
                        else
                        {
                            LeftRotate(fa);
                            RightRotate(Fa);
                        }
                    }
                }
            }
            if (FA == 0)
                root = x;
        }
        int Pred(int x)
        {
            if (node[x].lt)
            {
                x = node[x].lt;
                while (true)
                {
                    if (!node[x].rt)
                        return x;
                    x = node[x].rt;
                }
            }
            else
            {
                while (true)
                {
                    if (node[x].fa)
                    {
                        if (x == node[node[x].fa].rt)
                            return node[x].fa;
                        x = node[x].fa;
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
        }
        int Succ(int x)
        {
            if (node[x].rt)
            {
                x = node[x].rt;
                while (true)
                {
                    if (!node[x].lt)
                        return x;
                    x = node[x].lt;
                }
            }
            else
            {
                while (true)
                {
                    if (node[x].fa)
                    {
                        if (x == node[node[x].fa].lt)
                            return node[x].fa;
                        x = node[x].fa;
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
        }
        void Del(int now)
        {
            Splay(now, 0);
            int pred = Pred(now), succ = Succ(now);
            if (pred && succ)
            {
                Splay(pred, 0);
                Splay(succ, root);
                node[node[root].rt].lt = 0;
            }
            else if (pred && !succ)
            {
                Splay(pred, 0);
                node[root].rt = 0;
            }
            else if (succ && !pred)
            {
                Splay(succ, 0);
                node[root].lt = 0;
            }
            else
                root = 0;
        }
        void AdjustLeft(int now)
        {
            while (true)
            {
                int p1 = Pred(now), p2 = Pred(p1);
                if (p1 && p2)
                {
                    if (CrossProduct(p2, p1, now) >= 0 || node[p1].y <= node[now].y)
                        Del(p1);
                    else
                        break;
                }
                else if (p1 && node[p1].y <= node[now].y)
                {
                    Del(p1);
                }
                else
                    break;
            }
        }
        void AdjustRight(int now)
        {
            while (true)
            {
                int p1 = Succ(now), p2 = Succ(p1);
                if (p1 && p2)
                {
                    if (CrossProduct(now, p1, p2) >= 0)
                        Del(p1);
                    else
                        break;
                }
                else
                    break;
            }
        }
        void Adjust(int now)
        {
            int pred = Pred(now), succ = Succ(now);
            if (pred && succ && CrossProduct(pred, now, succ) >= 0)
                Del(now);
            else if (succ && node[succ].y >= node[now].y)
                Del(now);
            else
            {
                AdjustLeft(now);
                AdjustRight(now);
            }
        }
    public:
        SplayTree():root(0){}
        void Add(double x, double y)
        {
            int now = root, fa = 0, flag = 0;
            while (true)
            {
                if (!now)
                {
                    now = ++cntNode;
                    node[now].x = x, node[now].y = y;
                    node[now].fa = fa;
                    if (flag == 0)
                        node[fa].lt = now;
                    else
                        node[fa].rt = now;
                    Splay(now, 0);
                    break;
                }
                else
                {
                    fa = now;
                    if (x <= node[now].x) now = node[now].lt, flag = 0;
                    else now = node[now].rt, flag = 1;
                }
            }
            Adjust(root);
        }
        double Calculate(double x, double y, double A, double factor)
        {
            // y = -(A / factor)x + P / factor
            // P = y * factor + A * x
            return A * x + y *factor;
        }
        double Slope(double x, double y)
        {
            if (fabs(x) < EPS)
                return INFINITE;
            return y / x;
        }
        double Ask(double A, double factor)
        {
            double k = -A / factor;
            int now = root, lc, rt;
            double x, y;
            while (true)
            {
                double x = node[now].x, y = node[now].y;
                int pred = Pred(now), succ = Succ(now);
                if (!pred && !succ)
                    return Calculate(x, y, A, factor);
                else if (pred && !succ)
                {
                    if (k <= Slope(x - node[pred].x, y - node[pred].y))
                        return Calculate(x, y, A, factor);
                    else
                    {
                        if (node[now].lt)
                            now = node[now].lt;
                        else
                            return Calculate(x, y, A, factor);
                    }
                }
                else if (!pred && succ)
                {
                    if (k >= Slope(node[succ].x - x, node[succ].y - y))
                        return Calculate(x, y, A, factor);
                    else
                    {
                        if (node[now].rt)
                            now = node[now].rt;
                        else
                            return Calculate(x, y, A, factor);
                    }
                }
                else
                {
                    double kl = Slope(x - node[pred].x, y - node[pred].y);
                    double kr = Slope(node[succ].x - x, node[succ].y - y);
                    if (kl >= k && k >= kr)
                        return Calculate(x, y, A, factor);
                    else if (k <= kr)
                        now = node[now].rt;
                    else
                        now = node[now].lt;
                }
            }
        }
};

SplayTree T;
int s[MAXN + 1];
void Solve()
{
    double minx = INFINITE, maxx = -INFINITE;
    /*
     * P = X[j] * A[i] + Y[j] * B[i]
     * Y[j] = (-A[i] / B[i]) X[j] + P / B[i];
     */
    Y[1] = f[1] / (A[1] * Rate[1] + B[1]);
    X[1] = Y[1] * Rate[1];
    T.Add(X[1], Y[1]);
    for (int j = 2; j <= n; j ++)
    {
        f[j] = f[j - 1];
        double v = T.Ask(A[j], B[j]);
        f[j] = max(f[j], v);
        
        Y[j] = f[j] / (A[j] * Rate[j] + B[j]);
        X[j] = Y[j] * Rate[j];
        T.Add(X[j], Y[j]);
    }
    printf("%.3lf\n", f[n]);
}

int main()
{
    Init();
    Solve();
    return 0;
}

