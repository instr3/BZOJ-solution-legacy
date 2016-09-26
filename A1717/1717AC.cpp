#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define REP1(i, n) for (int i = 1; i <= (n); ++i)
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define CLR(x, n) memset(x, n, sizeof(x))
#define maxN 20010
#define maxM 1000010
using namespace std;

void setIO(string name) {
	string in_f = name + ".in";
	string out_f = name + ".out";
	freopen(in_f.c_str(), "r", stdin);
	freopen(out_f.c_str(), "w", stdout);
}

struct List {
	int v, next;
} d[maxN];

int head[maxM];
int n, k;
int s[maxN];
int rank[maxM], sa[maxN], pos[maxN], val[maxN][2];
int height[maxN];

inline void add_value(int u, int v, int now) {
	d[now].v = v;
	d[now].next = head[u];
	head[u] = now;
}

inline void radix_sort(int c) {
	c = (c == 1 ? maxM - 9 : n);
	for (int k = 1; k >= 0; --k) {
		CLR(head, 0);
		for (int i = n; i; --i) add_value(val[pos[i]][k], pos[i], i);
		int t = 0;
		FOR(i, 0, c) {
			for (int p = head[i]; p; p = d[p].next) pos[++t] = d[p].v;
		}
	}
	int t = 1;
	rank[pos[1]] = 1;
	FOR(i, 2, n) {
		if (val[pos[i]][0] != val[pos[i - 1]][0] || val[pos[i]][1] != val[pos[i - 1]][1]) ++t;
		rank[pos[i]] = t;
	}		
}

inline void get_surffix_array() {
	int t = 1;
	while ((t >> 1) < n) {
		REP1(i, n) {
			val[i][0] = rank[i];
			val[i][1] = ((i + (t >> 1) > n) ? 0 : rank[i + (t >> 1)]);
			pos[i] = i;
		}
		radix_sort(t);
		t <<= 1;
	}
	REP1(i, n) sa[rank[i]] = i;
}

inline void get_common_prefix() {
	int h[maxN] = {0};
	REP1(i, n) {
		if (rank[i] == 1) {
			h[i] = 0;
			continue;
		}
		if (i > 1 && h[i - 1]) h[i] = h[i - 1] - 1;
		while (i + h[i] <= n && sa[rank[i] - 1] + h[i] <= n && s[i + h[i]] == s[sa[rank[i] - 1] + h[i]]) ++h[i];
		height[rank[i]] = h[i];
	}
}

inline void init() {
	scanf("%d%d", &n, &k);
	REP1(i, n) {
		scanf("%d", s + i);
		++s[i];
		rank[i] = s[i];
	}
	get_surffix_array();
	get_common_prefix();
}

inline void solve() {
	int que[maxN], l, r;
	int ans = 0;
	l = r = 0;
	REP1(i, k - 1) {
		while (l < r && height[que[r - 1]] >= height[i]) --r;
		que[r++] = i;
	}
	FOR(i, k, n) {
		while (l < r && height[que[r - 1]]	>= height[i]) --r;
		que[r++] = i;
		while (que[l] < i - k + 2) ++l;
		if (height[que[l]] > ans) ans = height[que[l]];
	}
	printf("%d\n", ans);
}

int main() {
	setIO("1717");
	init();
	solve();
	return 0;
}
