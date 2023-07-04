#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 200002;

vector <int> node[MAXN];
int dp[MAXN][2];
int num[MAXN];

int DFS(int cur) {
    if(dp[cur][0] != -1) return max(dp[cur][0], dp[cur][1]);

    dp[cur][0] = dp[cur][1] = 0;

    for(int i : node[cur]) {
        dp[cur][0] += DFS(i);
    }

    for(int i : node[cur]) {
        dp[cur][1] = max(dp[cur][1], dp[cur][0] - max(dp[i][0], dp[i][1]) + dp[i][0] + num[cur]*num[i]);
    }

    return max(dp[cur][0], dp[cur][1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    int temp;
    for(int i = 2; i <= N; i++) {
        cin >> temp;
        node[temp].push_back(i);
    }

    for(int i = 1; i <= N; i++) cin >> num[i];

    memset(dp, -1, sizeof(dp));
    cout << DFS(1);
}