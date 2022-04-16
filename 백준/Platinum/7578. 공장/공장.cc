#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> tree, arr;
int h[1000010];

void update(int node, int start, int end, int idx, int diff){
	if(idx < start || idx > end) return;
	tree[node] += diff;
	if(start ^ end){
		update(node*2, start, (start+end)/2, idx, diff);
     update(node*2+1, (start+end)/2+1, end, idx, diff);
	}
}

ll sum(int node, int start, int end, int left, int right){
	if(left>end || right<start){
    	return 0;
	}
	if(left<=start && end<=right){
    	return tree[node];
	}
	return sum(node*2, start, (start+end)/2, left, right) + sum(node*2+1, (start+end)/2+1, end, left, right);
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	arr = vector<ll>(n+10);
	tree = vector<ll>(4*n+40);
	for(int i=1; i<=n; i++){
		ll t; cin >> t;
		h[t] = i;
	}
	for(int i=1; i<=n; i++){
		ll t; cin >> t;
		arr[i] = h[t];
	}

	ll ans = 0;

	for(int i=1; i<=n; i++){
		int j = arr[i];
		ans += sum(1, 1, n, j+1, n);
		update(1, 1, n, j, 1);
	}

	cout << ans;
}