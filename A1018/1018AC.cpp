//SHOI2008 Traffic
//Memo : Segment Tree
//#pragma GCC optimize ("O3")
//Note that this pragma is only avaliable on GCC 4.4+
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;
 
const int MXN = 100005, id[2][2] = {{0, 3}, {1, 2}};
typedef bool info[4][4];
struct node {
        int l, r, m;
        info dt;
        node *lc, *rc;
} NBuff[MXN * 2], *NCur = NBuff, *root;
int n;
 
//21
//30
inline void floyd (info x)
{
        x[2][0] = x[0][2] = x[0][2] || x[0][1] && x[1][2] || x[0][3] && x[3][2];
        x[3][1] = x[1][3] = x[1][3] || x[3][0] && x[0][1] || x[3][2] && x[2][1];
        x[2][1] = x[1][2] = x[1][2] || x[2][3] && x[3][0] && x[0][1] ||
                x[2][0] && x[0][3] && x[3][1];
        x[0][1] = x[1][0] = x[1][0] || x[0][3] && x[3][2] && x[2][1] ||
                x[0][2] && x[2][3] && x[3][1];
        x[3][0] = x[0][3] = x[0][3] || x[0][1] && x[1][2] && x[2][3] ||
                x[0][2] && x[2][1] && x[1][3];
        x[3][2] = x[2][3] = x[2][3] || x[2][1] && x[1][0] && x[0][3] ||
                x[2][0] && x[0][1] && x[1][3];
}
#define F_CLR(X) (X[0][0]=X[1][1]=X[2][2]=X[3][3]=true)
inline void merge (info x, info _l, info _r)
{
        info l, r;
        memcpy(l, _l, sizeof(l));
        memcpy(r, _r, sizeof(r));
        floyd(l); floyd(r);
        F_CLR(x);
        x[1][0] = x[0][1] = l[0][1] && r[0][1] || l[0][2] && r[3][1];
        x[2][0] = x[0][2] = l[0][2] && r[3][2] || l[0][1] && r[0][2];
        x[3][0] = x[0][3] = l[0][3] || l[0][1] && r[0][3] && l[2][3];
        x[2][1] = x[1][2] = r[1][2] || r[1][0] && l[1][2] && r[3][2];
        x[3][1] = x[1][3] = l[3][2] && r[3][1] || l[3][1] && r[0][1];
        x[3][2] = x[2][3] = l[3][2] && r[3][2] || l[3][1] && r[0][2];
}
 
void build (node *x, int l, int r)
{
        x->l = l, x->r = r, x->m = (l + r) >> 1;
        //memset(x->dt, false, sizeof(x->dt));
        F_CLR(x->dt);
        if (l != r)
                build(x->lc = NCur++, l, x->m),
                build(x->rc = NCur++, x->m + 1, r);
}
void modify (node *x, int ps, int a, int b, bool ndt)
{
        if (x->l == x->r)
                x->dt[a][b] = x->dt[b][a] = ndt;
        else
        {
                modify(ps <= x->m ? x->lc : x->rc, ps, a, b, ndt);
                merge(x->dt, x->lc->dt, x->rc->dt);
        }
}
void query (node *x, int l, int r, info res)
{
        if (l <= x->l && r >= x->r)
        {
                memcpy(res, x->dt, sizeof(x->dt));
                return;
        }
        bool lme = (l <= x->m), rme = (r > x->m);
        if (lme ^ rme)
                query(lme ? x->lc : x->rc, l, r, res);
        else
        {
                info linfo, rinfo;
                query(x->lc, l, r, linfo);
                query(x->rc, l, r, rinfo);
                merge(res, linfo, rinfo);
        }
}
 
inline void query (int l, int r, info res)
{
        query(root, l, r, res);
        floyd(res);
}
 
inline bool query (int ax, int ay, int bx, int by)
{ 
        info l, m, r; --ay, --by;
        if (ax == bx)
        {
                if (ay == by) return true; //...
                if (ax > 1) query(1, ax - 1, l); else l[1][2] = false;
                if (ax < n) query(ax, n - 1, r); else r[0][3] = false;
                return l[1][2] || r[0][3];
        }
        if (ax > bx) swap(ax, bx), swap(ay, by);
        bool res(false);
        query(ax, bx - 1, m);
        res = m[id[0][ay]][id[1][by]];
        if (!res && ax != 1)
        {
                query(1, ax - 1, l);
                res = res || l[id[1][ay]][id[1][!ay]] 
                        && m[id[0][!ay]][id[1][by]];
        }
        if (!res && bx != n)
        {
                query(bx, n - 1, r);
                res = res || r[id[0][by]][id[0][!by]] 
                        && m[id[1][!by]][id[0][ay]];
        }
        if (!res && ax != 1 && bx != n)
                res = res || l[id[1][ay]][id[1][!ay]] &&
                        m[id[0][!ay]][id[1][!by]] && r[id[0][!by]][id[0][by]];
        return res;
}
 
inline void modify (int ax, int ay, int bx, int by, bool nval)
{
        --ay, --by;
        if (ax > bx) swap(ax, bx), swap(ay, by);
        if (ax == bx)
        {
                if (ay == by) return;
                if (ax < n) modify(root, ax, 0, 3, nval);
                if (ax > 1) modify(root, ax - 1, 1, 2, nval);
        }
        else
                modify(root, ax, id[0][ay], id[1][by], nval);
}
 
inline void skip (int i) { while (i--) getchar(); }
 
inline void read (int &x)
{
        x = 0; char ch;
        do ch = getchar(); while (!(ch >= '0' && ch <= '9'));
        x = ch - '0';
        while (ch = getchar(), (ch >= '0' && ch <= '9'))
                x = x * 10 + ch - '0';
}
 
int main ()
{
    freopen("1018.in","r",stdin);
    freopen("1018.out","w",stdout);
        bool cont(true);
        read(n);
        build(root = NCur++, 1, n - 1);
        while (cont)
        {
                char ch; do ch = getchar(); while (isspace(ch));
                switch (ch)
                {
                        case 'O' : { skip(3);
                                int ax, ay, bx, by;
                                read(ay); read(ax); read(by); read(bx);
                                modify(ax, ay, bx, by, true);
                                break;
                        }
                        case 'C' : { skip(4);
                                int ax, ay, bx, by;
                                read(ay); read(ax); read(by); read(bx);
                                modify(ax, ay, bx, by, false);
                                break;
                        }
                        case 'A' : { skip(2);
                                int ax, ay, bx, by;
                                read(ay); read(ax); read(by); read(bx);
                                if(query(ax, ay, bx, by))printf("Y");else printf( "N");
                                putchar('\n');
                                break;
                        }
                        default : skip(3);
                                cont = false;
                }
        }
        return 0;
}
