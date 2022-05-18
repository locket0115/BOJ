#include <bits/stdc++.h>
using namespace std;

#define MAX 500000 + 1

int N;
pair<int, int> connect[MAX];
pair<int, int> answer[MAX];
int cache[MAX];
bool visited[MAX];
stack<int> s;

int LIS(void) {
    int idx = 0;
    int length = 0;
    cache[idx] = connect[0].second;
    answer[0] = {0, connect[0].first};

    for (int i = 1; i < N; i++) {
        if (cache[idx] < connect[i].second) {
            cache[++idx] = connect[i].second;
            answer[i] = {idx, connect[i].first};
        }
        else {
            int idx2 = lower_bound(cache, cache + idx, connect[i].second) - cache;
            cache[idx2] = connect[i].second;
            answer[i] = {idx2, connect[i].first};
        }
    }
    return idx + 1;
}

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> connect[i].first >> connect[i].second;
        visited[connect[i].first] = true;
    }

    sort(connect, connect + N);

    int result = LIS();
    cout << N - result << "\n";

    int num = result - 1;

    for (int i = N - 1; i >= 0; i--)
        if (answer[i].first == num) {
            s.push(answer[i].second);
            num--;
        }

    while (!s.empty()) {
        visited[s.top()] = false;
        s.pop();
    }

    for (int i = 0; i < MAX; i++) if (visited[i]) cout << i << "\n";
    return 0;
}