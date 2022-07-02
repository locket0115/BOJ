#include <bits/stdc++.h>
using namespace std;

vector <int> vc[10002];
int discovered[10002];
bool isCut[10002];

int num;

int dfs(int here, bool isRoot) {
    int ret = discovered[here] = ++num;

    int child = 0;

    for(auto next : vc[here]) {
        if(discovered[next]) {
            ret = min(ret, discovered[next]);
            continue;
        }

        child++;
        int prev = dfs(next, false);

        if(!isRoot && prev >= discovered[here])
            isCut[here] = true;

        ret = min(ret, prev);
    }
    if(isRoot)
        isCut[here] = (child >= 2);

    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int V, E;
    cin >> V >> E;

    for(int i = 0; i < E; i++) {
        int A, B;
        cin >> A >> B;

        vc[A].push_back(B);
        vc[B].push_back(A);
    }

    for(int i = 1; i <= V; i++) {
        if(!discovered[i]) dfs(i, true);
    }

    int res = 0;
    for(int i = 1; i <= V; i++) {
        if(isCut[i]) res++;
    }

    cout << res << "\n";
    for(int i = 1; i <= V; i++) {
        if(isCut[i]) cout << i << " ";
    }

    return 0;
}