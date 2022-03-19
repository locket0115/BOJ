#include <bits/stdc++.h>

using namespace std;

int N, K;

int idx[2001][2001];
int parent[100001];

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

queue<pair<int, int>> union_;
queue<pair<int, int>> bfs;

int find_parent(int idx) {
    if (idx == parent[idx]) return idx;
    return parent[idx] = find_parent(parent[idx]);
}

void untie(int a, int b) {
    int parentA = find_parent(a);
    int parentB = find_parent(b);

    if (parentA != parentB) {
        parent[parentA] = parentB;
    }
}

void untie_civil() {
    while (union_.empty() == false) {
        auto [curx, cury] = union_.front();
        bfs.push({ curx, cury });
        union_.pop();

        for (int i = 0; i < 4; i++) {
            int nx = curx + dx[i];
            int ny = cury + dy[i];

            if (nx < 1 || nx > N || ny < 1 || ny > N || idx[nx][ny] == 0)
                continue;

            if (idx[curx][cury] == idx[nx][ny] || find_parent(idx[curx][cury]) == find_parent(idx[nx][ny]))
                continue;

            untie(idx[curx][cury], idx[nx][ny]);
            K--;
        }
    }
}

void bfs_civil() {
    while (bfs.empty() == false) {
        auto [curx, cury] = bfs.front();
        bfs.pop();

        for (int i = 0; i < 4; i++) {
            int nx = curx + dx[i];
            int ny = cury + dy[i];

            if (nx < 1 || nx > N || ny < 1 || ny > N || idx[nx][ny] != 0)
                continue;

            idx[nx][ny] = idx[curx][cury];
            union_.push({ nx, ny });
        }
    }
}

int main() {
    cin >> N >> K;

    for (int i = 1; i <= K; i++) {
        int x, y;	cin >> x >> y;
        union_.push(make_pair(x, y));
        idx[x][y] = i;
    }

    for (int i = 0; i <= 100000; i++)
        parent[i] = i;

    for (int year = 0;; year++) {
        untie_civil();

        if (K == 1) {
            cout << year << "\n";
            return 0;
        }

        bfs_civil();
    }
}