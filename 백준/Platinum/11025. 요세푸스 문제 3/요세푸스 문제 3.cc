#include <iostream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    int n, k, ans = 1;
	
    cin >> n >> k;

	for (int i = 2; i <= n; i++) ans = (ans + k - 1) % i + 1;
	
    cout << ans;
	return 0;
}