#include <iostream>
#include <vector>

using namespace std;

vector <int> graph[300003];

int N;

long long lownode[300003];
long long t[300003];

void solve(int cur) {
    lownode[cur] = 1;

    vector <long long> llnode;
    long long mnode = 0;

    for(int it : graph[cur]) {
        if(lownode[it] == 0) {
            solve(it);

            llnode.push_back(lownode[it]);
            lownode[cur] += lownode[it];
            t[cur] += t[it];
        }
    }

    if(lownode[cur] == 1) {
        t[cur] = N-1;
        return;
    }

    t[cur] += N - lownode[cur];

    for(int it : llnode) mnode += it * (lownode[cur] - it - 1);
    t[cur] -= mnode / 2;

    return;
}

int main() {
    cin >> N;
    for(int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    solve(1);

    long long ans = 0;

    for(int i = 2; i <= N; i++) {
        ans += t[i];
    }

    cout << ans;
}