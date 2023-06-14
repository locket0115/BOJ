#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using pii = pair<int, int>;

vector<pii> graph[1005];
priority_queue<int> dist[1005];
priority_queue<pii, vector<pii>, greater<pii>> pq;

int n, m, k;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;

    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        graph[a].push_back({b, c});
    }

    pq.push({0, 1});
    dist[1].push(0);

    while(!pq.empty()) {
        auto[c, cur] = pq.top();
        pq.pop();

        for(auto it : graph[cur]) {
            int next = it.first, d = c + it.second;

            if(dist[next].size() < k) {
                dist[next].push(d);
                pq.push({d, next});
            }
            else if(dist[next].top() > d) {
                dist[next].pop();
                dist[next].push(d);
                pq.push({d, next});
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        if(dist[i].size() < k) cout << "-1\n";
        else cout << dist[i].top() << "\n";
    }

    return 0;
}