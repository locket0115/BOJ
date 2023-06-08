#include <iostream>

using namespace std;

int arr[10005], a[10005], b[10005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

	int n; cin >> n;
	for (int i = 0; i < n; i++) cin >> arr[i];
    
	int ans = 0;
	for (int i = 0; i < n; i++) {
		ans += arr[i] * 3;
		a[i] = arr[i], arr[i] = 0;

		if (i + 1 < n) {
			int t1 = min(a[i], arr[i + 1]);
			ans += t1 * 2;
			a[i] -= t1;
			arr[i + 1] -= t1;
			b[i] += t1;
		}
		
        if (i - 1 >= 0 && i + 1 < n) {
			int t2 = min(b[i - 1], arr[i + 1]);
			ans += t2 * 2;
			arr[i + 1] -= t2;
		}
	}
	cout << ans << '\n';
}