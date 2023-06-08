#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cstring>

using namespace std;
 
using ll = long long;
using pii = pair<int, int>;
const int MOD = 1e9 + 7;
const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };
 
int pa[30000];
 
int fnd(int n) {
	if (pa[n] < 0) return n;
	return pa[n] = fnd(pa[n]);
}
void uni(int a, int b) {
	a = fnd(a), b = fnd(b);
	if (a != b) pa[b] = a;
}
 
// segment tree
const int SZ = 1 << 15;
int tree[SZ << 1];
 
void update(int x, int val) {
	for (tree[x += SZ] = val; x >>= 1; )
		tree[x] = tree[x << 1] + tree[x << 1 | 1];
}
int query(int L, int R) {
	int ret = 0;
	for (L += SZ, R += SZ; L <= R; L >>= 1, R >>= 1) {
		if (L & 1) ret += tree[L++];
		if (~R & 1) ret += tree[R--];
	}
	return ret;
}
 
// HLD
vector<int> adj[30000];
int p[30000], w[30000], d[30000];
int num[30000], hld[30000], ncnt;
 
void dfs(int now) {
	w[now] = 1;
	for (int nxt : adj[now]) if (!w[nxt]) {
		p[nxt] = now;
		d[nxt] = d[now] + 1;
		dfs(nxt);
		w[now] += w[nxt];
	}
}
void dfs2(int now, int prv = -1) {
	num[now] = ncnt++;
	for (int nxt : adj[now]) if (prv != nxt && w[nxt] << 1 >= w[now]) {
		hld[nxt] = hld[now];
		dfs2(nxt, now);
	}
	for (int nxt : adj[now]) if (prv != nxt && w[nxt] << 1 < w[now]) {
		hld[nxt] = nxt;
		dfs2(nxt, now);
	}
}
int hld_query(int a, int b) {
	int ret = 0;
	while (hld[a] != hld[b]) {
		if (d[hld[a]] < d[hld[b]]) swap(a, b);
		ret += query(num[hld[a]], num[a]);
		a = p[hld[a]];
	}
	if (d[a] < d[b]) swap(a, b);
	return ret + query(num[b], num[a]);
}
 
int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    memset(pa, -1, sizeof(pa));
	
    int N;
	cin >> N;
 
	int peng[30000];
	for (int i = 0; i < N; ++i) cin >> peng[i];
 
	int Q;
	cin >> Q;
 
	string cmd;
	vector<tuple<int, int, int>> q(Q);
	for (int a, b, i = 0; i < Q; ++i) {
		cin >> cmd >> a >> b;
		q[i] = { cmd[0] == 'e' ? 2 : cmd[0] == 'p', a, b };
	}
 
	int ans[300000];
    memset(ans, -1, sizeof(ans));


	for (int i = 0; i < Q; ++i) {
		auto[_, a, b] = q[i];
 
		switch (_) {
		case 0:
			if (fnd(--a) != fnd(--b)) {
				uni(a, b);
				adj[a].push_back(b);
				adj[b].push_back(a);
				ans[i] = 1;
			}
			else ans[i] = 0;
			break;
		case 2:
			if (fnd(--a) != fnd(--b)) ans[i] = -2;
			break;
		}
	}
 
	for (int i = 0; i < N; ++i) if (w[i] == 0) {
		dfs(i);
		dfs2(i);
	}
	for (int i = 0; i < N; ++i) update(num[i], peng[i]);
 
	for (int i = 0; i < Q; ++i) {
		auto[_, a, b] = q[i];
 
		switch (_) {
		case 1:
			update(num[a - 1], b);
			break;
		case 2:
			if (ans[i] != -2) ans[i] = hld_query(a - 1, b - 1);
			break;
		}
	}
 
	for (int i = 0; i < Q; ++i) {
		auto[_, a, b] = q[i];
 
		switch (_) {
		case 0:
			if (ans[i]) cout << "yes\n";
			else cout << "no\n";
			break;
		case 2:
			if (ans[i] == -2) cout << "impossible\n";
			else cout << ans[i] << "\n";
		}
	}
 
	return 0;
}