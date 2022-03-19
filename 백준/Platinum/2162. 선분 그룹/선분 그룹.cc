#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> p;
typedef pair<p, p> pp;
typedef long long ll;

vector<int> g[3010];
vector<pp> line;

long long ccw(p a, p b){
	return a.first*b.second - a.second*b.first;
}

int ccw(p a, p b, p c){
	long long res = ccw(make_pair(b.first - a.first, b.second - a.second), make_pair(c.first - a.first, c.second - a.second));
	if (res > 0) return 1;
	if (res < 0) return -1;
	return 0;
}

bool chk(pp aa, pp bb){
	p a = aa.first, b = aa.second;
	p c = bb.first, d = bb.second;

	int ab = ccw(a, b, c) * ccw(a, b, d);
	int cd = ccw(c, d, a) * ccw(c, d, b);

	if(ab==0 && cd==0){
		if(b<a) swap(a, b);
		if(d<c) swap(c, d);
		return c<=b && a<=d;
	}

	return ab<=0 && cd<=0;
}

int v[3010];
int bfs(int s){
	queue<int> q;
	q.push(s);
	v[s] = 1;
	int ret = 1;

	while(!q.empty()){
		int poped = q.front(); q.pop();
		for(auto j : g[poped]){
			if(!v[j]){
				q.push(j); ret++;
				v[j] = 1;
			}
		}
	}
	return ret;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;
	line = vector<pp>(n);
	for(int i=0; i<n; i++){
		cin >> line[i].first.first >> line[i].first.second >> line[i].second.first >> line[i].second.second;
	}

	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			if(chk(line[i], line[j])){
				g[i].push_back(j); g[j].push_back(i);
			}
		}
	}

	int maxi = 0, cnt = 0;
	for(int i=0; i<n; i++){
		if(!v[i]){
			cnt++;
			maxi = max(maxi, bfs(i));
		}
	}

	cout << cnt << "\n" << maxi;
}