#include <bits/stdc++.h>

using namespace std;

bool chk[2001][2001];
int gcd(int a, int b) {
    return b==0 ? a : gcd(b, a%b);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
    int d1, d2, ans=0;
	cin >> d1 >> d2;
	
    for(int i = d1; i <= d2; i++){
        for(int j = 1; j <= i; j++){
            int g = gcd(i, j), a = j/g, b = i/g;
            if(!chk[a][b]) {
                ans++;
                chk[a][b] = true;
            }
        }
	}
	cout << ans << "\n";
	return 0;
}