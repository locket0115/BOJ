#include <algorithm>
#include <iostream>
#include <deque>
#include <vector>
using namespace std;
using ii = pair<int, long long>;
vector<ii> v[100001];
int n;
long long ans = 0;
long long dfs(int now, int pre) {
	long long cnt = 1;
	for(ii nxt : v[now]) {
		if(nxt.first == pre) continue;
		long long ex = nxt.second*dfs(nxt.first, now) % 1000000007;
		
		ans += cnt*ex % 1000000007;
		ans %= 1000000007;

		cnt += ex;
		cnt %= 1000000007;
	}
	return cnt;
}
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	for(int i = 1; i < n; i++) {
		int a, b, w;
		cin >> a >> b >> w;
		v[a].push_back({b, w});
		v[b].push_back({a, w});
	}
	dfs(1, -1);
	cout << ans;
}