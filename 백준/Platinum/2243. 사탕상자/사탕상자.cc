#include <bits/stdc++.h>
using namespace std;

int seg[4000002];

int add(int taste, int num, int idx, int left, int right) {
    if(taste < left || right < taste) return 0;

    if(left == right && right == taste) {
        seg[idx] += num;
        return seg[idx];
    }

    int mid = (left + right)/2;
    add(taste, num, idx*2, left, mid);
    add(taste, num, idx*2+1, mid+1, right);

    return seg[idx]= seg[idx*2] + seg[idx*2+1];
}

int draw(int order, int idx, int left, int right) {
    if(left == right) {
        cout << left << "\n";
        return --seg[idx];
    }

    int mid = (left + right)/2;
    if(seg[idx*2] >= order) draw(order, idx*2, left, mid);
    else draw(order-seg[idx*2], idx*2+1, mid+1, right);

    return seg[idx]= seg[idx*2] + seg[idx*2+1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N;
    cin >> N;

    for(int i = 0; i < N; i++) {
        int A, B;
        cin >> A >> B;
        if(A==1) draw(B, 1, 1, 1000000);
        else {
            int C;
            cin >> C;

            add(B, C, 1, 1, 1000000);
        }
    }

    return 0;
}