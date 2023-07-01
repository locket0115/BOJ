#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

const int MAXN = 200000;

ll A[MAXN];
ll B[MAXN];

vector <pll> AB;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for(int i = 0; i < N; i++) {
        cin >> A[i];    
    }

    for(int i = 0; i < N; i++) {
        cin >> B[i];
    }

    
    for(int i = 0; i < N; i++) {
        AB.push_back({A[i], B[i]});
    }

    sort(AB.begin(), AB.end(), [](pll a, pll b) {
        return a.second < b.second;
    });

    priority_queue<ll, vector<ll>, less<ll>> pq;

    ll ans = AB[0].first;
    for(int i = 1; i < N-1; i+=2) {
        pq.push(AB[i].first);
        pq.push(AB[i+1].first);

        ans += pq.top();
        pq.pop();
    }

    cout << ans;
}