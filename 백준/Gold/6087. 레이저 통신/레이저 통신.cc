#include<iostream>
#include<cstring>
#include<queue>
 
#define endl "\n"
#define MAX 100
using namespace std;
 
int W, H;
char MAP[MAX][MAX];
int Visit[MAX][MAX][5];
 
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };
 
pair<int, int> Start, End;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int Tmp = 0;
    cin >> W >> H;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> MAP[i][j];
            if (MAP[i][j] == 'C') {
                if (Tmp == 0) {
                    Start.first = i;
                    Start.second = j;
                    Tmp++;
                }
                else {
                    End.first = i;
                    End.second = j;
                }
            }
            for(int k =0; k < 4; k++)Visit[i][j][k] = 1234567890;
        }
    }

    queue<pair<pair<int, int>, pair<int, int>>> Q;
    
    for (int i = 0; i < 4; i++) {
        Q.push(make_pair(Start, make_pair(i, 0)));
    }

    for(int k =0; k < 4; k++)Visit[Start.first][Start.second][k] = 0;

    
 
    while (Q.empty() == 0) {
        auto[x, y] = Q.front().first;
        auto [Dir, Cnt] = Q.front().second;
        Q.pop();
 
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nCnt = Cnt;
 
            if (nx < 0 || ny < 0 || nx >= H || ny >= W) continue;
            if (MAP[nx][ny] == '*') continue;
            if (Dir != i) nCnt = nCnt + 1;
            if (Visit[nx][ny][i] > nCnt) {
                Visit[nx][ny][i] = nCnt;
                Q.push(make_pair(make_pair(nx, ny), make_pair(i, nCnt)));
            }
        }
    }

    int res = 1234567890;

    for(int k =0; k < 4; k++)res = min(res, Visit[End.first][End.second][k]);


    cout << res << "\n";
    return 0;
}