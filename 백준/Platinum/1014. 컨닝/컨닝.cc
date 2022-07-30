#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
string field[15];
int dp[15][1025]; // dp[i][j]=> i번째 줄에 j비트 모양으로 학생을 배치할때, i번째까지 사람을 앉힐 수 있는 최대수
bool seat_check(string& seats, int bit) {
	for (size_t i = 0; i < seats.length(); i++) {
		if (seats[i] == 'x' && (bit & (1 << i))) return false;
	}
	return true;
}
bool adj_check(int bit, int width) {
	for (int i = 0; i < width - 1; i++) {
		int val = (3 << i);
		if ((bit & val) == val) return false;
	}
	return true;
}
bool bits_check(int bit, int fbit, int width) {
	//앞자리랑 뒷자리 관계가 제대로 성립하는지 확인
	for (int i = 0; i < width; i++) {
		if ((1 << i) & fbit) { //앞자리에 앉는 녀석이 있을 때
			if (i > 0 && ((1 << (i - 1)) & bit)) return false; //왼쪽에 뒤에 앉는 경우
			if ((1 << (i + 1) & bit)) return false; //오른쪽 뒤에 앉는 경우
		}
	}
	return true;
}
void solve() {
	int ans = 0;
	memset(dp, 0, sizeof(dp));
	int n, m; cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> field[i];
	}
	vector<pii> bits_set; //인접한 자리가 아닌 비트 마스크들을 미리 만들어놓음.
	for (int bit = 0; bit < (1 << m); bit++) {
		if (adj_check(bit, m)) {
			int cnt = 0;
			for (int i = 0; i < m; i++) {
				if ((1 << i) & bit) cnt++;
			}
			bits_set.push_back(make_pair(bit, cnt));
		}
	}
	for (int i = 1; i <= n; i++) {
		//i 번째 줄을 채울 예정
		for (pii bit : bits_set) {
			if (!seat_check(field[i], bit.first)) continue; //부서진 자리에 앉으려고 하는 경우
			for (pii fbit : bits_set) { //앞자리 앉는 녀석
				if (bits_check(bit.first, fbit.first, m)) {
					dp[i][bit.first] = max(dp[i][bit.first], dp[i - 1][fbit.first] + bit.second);
					ans = max(ans, dp[i][bit.first]);
				}
			}
		}
	}
	cout << ans << endl;
	return;
}
int main() {
	int tc; cin >> tc;
	while (tc--) solve();
}