#include <bits/stdc++.h>

using namespace std;

vector <int> vc;

int main() {
    ios::sync_with_stdio(0);
    cout.tie(0); cout.tie(0);

    int n, k;
    cin >> n >> k;

    for(int i = 0; i < n; i++) {
        int t;
        cin >> t;
        vc.push_back(t);
    }

    sort(vc.begin(), vc.end());

    int sum = 0;

    for(int i = n-1, j = 0; i >= n-k; i--, j++) {
        sum += vc[i]-j;
    }

    cout << sum;
}