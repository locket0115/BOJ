#include <bits/stdc++.h>
using namespace std;

int seg[800000];
int loc[200000];

int n, m;

void update(int node, int start, int end, int left, int right, int val) {
    if(end < left || right < start) return;
    if(start == end) {
        seg[node] = val; 
        return;
    }

    int mid = (start+end)/2;

    update(node*2, start, mid, left, right, val);
    update(node*2+1, mid+1, end, left, right, val);

    seg[node] = seg[node*2] + seg[node*2+1];
    return;
}

int sum(int node, int start, int end, int left, int right) {
    if(left <= start && end <= right) return seg[node];
    if(end < left || right < start) return 0;

    int mid = (start+end)/2;

    return sum(node*2, start, mid, left, right) + sum(node*2+1, mid+1, end, left, right);
}

bool init() {
    update(1, 1, n+m, 1, n, 1);
    update(1, 1, n+m, n+1, n+m, 0);
    
    for(int i = 0; i < n; i++) loc[n-i] = i+1;

    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int T;
    cin >> T;

    while(T--) {
        cin >> n >> m;
        init();

        int it;
        for(int i = 1; i <= m; i++) {
            cin >> it;
            cout << sum(1, 1, n+m, loc[it]+1, n+m) << " ";
            
            update(1, 1, n+m, loc[it], loc[it], 0);
            update(1, 1, n+m, n+i, n+i, 1);

            loc[it] = n+i;
        }

        cout << "\n";
    }

    return 0;
}