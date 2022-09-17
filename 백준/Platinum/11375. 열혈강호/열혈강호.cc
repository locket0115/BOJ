#include <bits/stdc++.h>
using namespace std;

#define MAX 1002

vector<int> vtx[MAX];
int slt[MAX];
bool done[MAX];
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

    for(int i = 1; i <= N; i++) {
        int s, t; cin >> s;

        for(int j = 0; j < s; j++) {
            cin >> t;
            vtx[i].push_back(t);
        }
    }

    int cnt = 0;
	for (int i = 1; i <= N; i++) {
		fill(done, done + MAX, false);
		if (dfs(i)) cnt++;
	}

    cout << cnt;
}