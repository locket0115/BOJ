#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int N, K, Q;
    cin >> N >> K >> Q;
    vector<vector<int>> arr(N,vector<int>(K));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            cin >> arr[i][j];
        }
    }

    long long dist = 0;
    bool all_one = true;
    for (int i = 0; i < arr[0].size(); i++) {
        if (arr[0][i] != 1) {
            all_one = false;
            break;
        }
    }
    if (all_one) dist += N;
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < K; j++) {
            dist += (arr[i-1][j] >= i ? arr[i-1][j] - i : N - i + arr[i-1][j]);
        }
    }
    cout << ((dist + N - 1) / N <= Q ? 1 : 0);
}