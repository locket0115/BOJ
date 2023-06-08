#include <iostream>
#include <cmath>

using namespace std;

using ll = long long;

int c[10005];
ll sum[20005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    
    for(int i = 1; i <= n; i++) {
        cin >> c[i];
        sum[i] = sum[i-1] + c[i];
    }

    for(int i = n+1; i <= 2*n; i++) {
        sum[i] = sum[i-1] + c[i-n];
    }

    ll s = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = i+1; j <= i+n; j++) {
            if(sum[j] - sum[i] < 0) {
                s += (ll)ceil((sum[i]-sum[j])/((long double)sum[n]));
            }
        }
    }

    cout << (ll)s;

    return 0;
}