#include <bits/stdc++.h>
using namespace std;

vector <int> vc[100002];
int discovered[100002];
vector <pair<int, int>> isCut;

int num;

int dfs(int here, int parent) {
    int ret = discovered[here] = ++num;

    for(auto next : vc[here]) {
        if(next == parent) continue;

        if(discovered[next]) {
            ret = min(ret, discovered[next]);
            continue;
        }

        int prev = dfs(next, here);

        if(prev > discovered[here]) isCut.push_back({min(here, next), max(here, next)});

        ret = min(ret, prev);
    }

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
        if(!discovered[i]) dfs(i, 0);
    }

    sort(isCut.begin(), isCut.end());

    cout << isCut.size() << "\n";

    for(auto it : isCut) {
        cout << it.first << " " << it.second << "\n";
    }

    return 0;
}