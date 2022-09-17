#include <bits/stdc++.h>
using namespace std;

vector<int> vtx[102];
int slt[5002];
bool done[5002];
int N, M;

bool dfs(int x) {
	for (int i = 0; i < vtx[x].size(); i++) {
		int p = vtx[x][i];
		if (done[p]) continue;
		done[p] = true;
		
        if (slt[p] == 0 || dfs(slt[p])) {
			slt[p] = x;
			return true;
		}
		
	}
	return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;

    for(int i = 1; i <= M; i++) {
        int a, b; cin >> a >> b;
        vtx[a].push_back(b);
    }

    int cnt = 0;
	for (int i = 1; i <= N; i++) {
		fill(done, done + 5002, false);
		if (dfs(i)) cnt++;
	}

    cout << cnt;
}