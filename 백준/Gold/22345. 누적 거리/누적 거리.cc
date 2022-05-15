#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pl;

ll N, Q, p[200011], cnt[200011], d[200011];

vector<ll> a;
vector<pl> v;

int main() {
    ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N >> Q;
	for (int i = 0; i < N; i++) {
		ll n, cost;
		cin >> n >> cost;
		a.push_back(cost);
		v.push_back({ cost, n });
	}
	sort(all(a));
	sort(all(v));
	
    for (int i = 1; i <= N; i++) {
		p[i] = p[i - 1] + v[i - 1].first;
		d[i] = d[i - 1] + v[i - 1].first * v[i - 1].second;
		cnt[i] = cnt[i - 1] + v[i - 1].second;
	}

	while (Q--) {
		ll n;
		cin >> n;
		ll idx = lower_bound(all(a), n) - a.begin();
		cout << d[N]-2*d[idx]-(n*(cnt[N]-2*cnt[idx])) << "\n";
	}
}