#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

int n, m, last = 0;
vector<int> tree[400000], arr;

void init(int i, int S, int E) {
	if (S == E) tree[i].push_back(arr[S]);
	else {
		tree[i].resize(E-S+1);
		init(2 * i, S, (S + E) / 2);
		init(2 * i + 1, (S + E) / 2 + 1, E);
		merge(all(tree[2 * i]), all(tree[2 * i + 1]), tree[i].begin());
	}
}

int query(int i, int S, int E, int L, int R,int val) {
	if (E < L || R < S) return 0;
	if (L <= S && E <= R) return tree[i].end()-upper_bound(all(tree[i]),val);
	return query(2 * i, S, (S + E) / 2, L, R,val)
		+ query(2 * i + 1, (S + E) / 2 + 1, E, L, R,val);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
    cin >> n;
	arr.resize(n);
	for (int i = 0; i < n; i++) cin >> arr[i];

	init(1, 0, n - 1);

	cin >> m;
	for (int i = 0; i < m; i++) {
    	int a, b, c;
		cin >> a >> b >> c;
		cout<<query(1, 0, n - 1, a - 1, b - 1, c) << '\n';
	}
	return 0;
}