#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define MAX 100005

ll arr[MAX];
ll seg[4*MAX];

int N, Q;

void makeTree(int node, int left, int right, int start, int end) {
    if(start == end) {seg[node] = arr[start]; return;}

    int mid = (start+end)/2;
    makeTree(node*2, left, right, start, mid);
    makeTree(node*2+1, left, right, mid+1, end);

    seg[node] = seg[node*2] + seg[node*2+1];
}

void update(int node, int idx, int val, int start, int end) {
    if(idx == start && start == end) {seg[node] = val; return;}

    if(idx < start || end < idx) return;

    int mid = (start+end)/2;
    update(node*2, idx, val, start, mid);
    update(node*2+1, idx, val, mid+1, end);

    seg[node] = seg[node*2] + seg[node*2+1];
}

ll sum(int node, int left, int right, int start, int end) {
    if(left <= start && end <= right) return seg[node];
    if(right < start || end < left) return 0;

    int mid = (start+end)/2;
    return sum(node*2, left, right, start, mid) + sum(node*2+1, left, right, mid+1, end);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> N >> Q;

    for(int i = 1; i <= N; i++) {
        cin >> arr[i];
    }

    makeTree(1, 1, N, 1, N);

    int x, y, a, b;
    for(int i = 1; i <= Q; i++) {
        cin >> x >> y >> a >> b;
        if(x > y) swap(x, y);

        cout << sum(1, x, y, 1, N) << "\n";
        update(1, a, b, 1, N);
    }

    return 0;
}