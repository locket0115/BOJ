#include <bits/stdc++.h>
using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;

#define x first
#define y second
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
#define IDX(v, x) (lower_bound(all(v), x) - v.begin())

constexpr int S = 1 << 18;

struct Event{
    int op, x, y, c;
    Event() = default;
    Event(int op, int x, int y, int c) : op(op), x(x), y(y), c(c) {}
    bool operator < (const Event &e) { return tie(x, op) < tie(e.x, e.op); }
};

struct SegmentTree{
    int T[S << 1], L[S << 1];
    void clear(){ memset(T, 0, sizeof T); memset(L, 0, sizeof L); }
    void push(int node, int s, int e){
        T[node] += L[node];
        if(s != e) for(auto c : {node<<1, node<<1|1}) L[c] += L[node];
        L[node] = 0;
    }
    void update(int l, int r, int v, int node=1, int s=0, int e=S-1){
        push(node, s, e);
        if(r < s || e < l) return;
        if(l <= s && e <= r){ L[node] += v; push(node, s, e); return; }
        int m = s + e >> 1;
        update(l, r, v, node<<1, s, m);
        update(l, r, v, node<<1|1, m+1, e);
        T[node] = max(T[node<<1], T[node<<1|1]);
    }
    int query(){ push(1, 0, S-1); return T[1]; }
} Seg;

int N, K, X[101010], Y[101010], C[101010];
vector<Event> events;
multiset<int> st[252525];

bool Check(int R){
    Seg.clear();
    for(int i=1; i<=K; i++) st[i] = multiset<int>{0, S-1};
    events.clear();
    for(int i=1; i<=N; i++){
        events.emplace_back(+1, X[i], Y[i], C[i]);
        events.emplace_back(-1, X[i]+R, Y[i], C[i]);
    }
    sort(all(events));

    for(const auto &[op, x, y, c] : events){
        if(op == -1){
            auto it = st[c].lower_bound(y);
            int l = max(y, *prev(it) + R);
            int r = min(y + R, *next(it));
            Seg.update(l, r-1, -1);
            st[c].erase(it);
        }
        else{
            auto it = st[c].insert(y);
            int l = max(y, *prev(it) + R);
            int r = min(y + R, *next(it));
            Seg.update(l, r-1, +1);
            if(Seg.query() == K) return true;
        }
    }
    return false;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> N >> K;
    for(int i=1; i<=N; i++) cin >> X[i] >> Y[i] >> C[i];

    events.reserve(N+N);
    int l = 1, r = 252525;
    while(l < r){
        int m = l + r >> 1;
        if(Check(m)) r = m;
        else l = m + 1;
    }
    cout << r - 1;
}