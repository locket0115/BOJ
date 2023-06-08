#include <iostream>

using namespace std;

using ll = long long;

ll arr[1000005], a[1000005], b[1000005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

	int n, B, C; cin >> n >> B >> C;
	for (int i = 0; i < n; i++) cin >> arr[i];
    
	if(B <= C) {
		ll ans = 0;
		for(int i = 0; i < n; i++) {
			ans += arr[i];
		}

		cout << ans*B;

		return 0;
	}

	ll ans = 0;
	for (int i = 0; i < n; i++) {
		ans += arr[i] * B;
		a[i] = arr[i], arr[i] = 0;

		if (i + 1 < n) {
			ll t1 = min(a[i], arr[i + 1]);
			ans += t1 * C;
			a[i] -= t1;
			arr[i + 1] -= t1;
			b[i] += t1;
		}
		
        if (i - 1 >= 0 && i + 1 < n) {
			ll t2 = min(b[i - 1], arr[i + 1]);
			ans += t2 * C;
			arr[i + 1] -= t2;
		}
	}
	cout << ans << '\n';
}