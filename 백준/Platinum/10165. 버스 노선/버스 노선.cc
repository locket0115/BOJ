#include <bits/stdc++.h>
using namespace std;

struct busline{
	int u, v, num;
	bool operator < (busline &b){
		if(u == b.u) return v > b.v;
		return u < b.u;
	}
};

bool cmp(busline a, busline b) {
    return a.num < b.num;
}

int main() {
	ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

	int n, m;
    cin >> n >> m;
	
    vector<busline> v(m);

	int back = 0;

	for(int i = 0; i < m; i++){
		cin >> v[i].u >> v[i].v;
		v[i].num = i+1;
		if(v[i].u > v[i].v){
			back = max(back, v[i].v);
			v[i].v += n;
		}
	}
	sort(v.begin(), v.end());

	deque <busline> dq;
	for(auto i : v){
		if(dq.empty() || dq.back().v < i.v)
            dq.push_back(i);
	}

	while(!dq.empty() && dq.front().v <= back) dq.pop_front();
	
    sort(dq.begin(), dq.end(), cmp);

	for(auto i : dq) cout << i.num << " ";
}