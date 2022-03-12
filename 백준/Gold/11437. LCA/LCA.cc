#include <bits/stdc++.h>

using namespace std;

#define MAXN 100005
#define MAXD 20

int N, M;
int parent[MAXN][MAXD];
int depth[MAXN];

vector <int> adj[MAXN];

void makeTree(int cur) {
    for(auto it : adj[cur]) {
        if(depth[it] == -1) {
            depth[it] = depth[cur]+1;
            parent[it][0] = cur;
            makeTree(it);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N;

    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(depth,-1,sizeof(depth));
    fill(depth, depth+N, -1);
    depth[1] = 0;
    
    makeTree(1);

    for(int j = 0; j < MAXD-1; j++) {
        for(int i = 2; i <= N; i++)  {
            if(parent[i][j] != -1)
                parent[i][j+1] = parent[parent[i][j]][j];
        }
    }

    cin >> M;
    for(int m = 0; m < M; m++) {
        int u, v;
        cin >> u >> v;

        if(depth[u] < depth[v]) swap(u,v);
        int diff = depth[u] - depth[v];

        for(int i = 0; diff; i++) {
            if(diff&1) u = parent[u][i];
            diff>>=1;
        }

        if(u!=v) {
            for(int i = MAXD-1; i >= 0; i--) {
                if(parent[u][i] != -1 && parent[v][i] != -1 && parent[u][i] != parent[v][i]){
                    u = parent[u][i];
                    v = parent[v][i];
                }
            }

            u = parent[u][0];
        }
        cout << u << "\n";
    }

    return 0;
}