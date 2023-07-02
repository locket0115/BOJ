#include <iostream>
#include <string>
#include <cstring>

using namespace std;

const int MAX = 16;
const int INF = 987654321;
 
int N, P, Answer = INF;
int MAP[MAX][MAX];
int Cost[1 << MAX];
string S;
 
int Min(int A, int B) { if (A < B) return A; return B; }

int Bit_Count(int B) {
    int Cnt = 0;
    while(B != 0) {
        Cnt = Cnt + (B & 1);
        B = B >> 1;
    }
    return Cnt;
}
 
int DFS(int State) {
    if (Bit_Count(State) >= P) return 0;
    if (Cost[State] != -1) return Cost[State];
 
    Cost[State] = INF;
    for (int i = 0; i < N; i++)     {
        if ((State & (1 << i))  == 0) continue;
        
        for (int j = 0; j < N; j++) {
            if ((State & (1 << j)) == 0) {
                int Next_State = State | (1 << j);
                Cost[State] = Min(Cost[State], MAP[i][j] + DFS(Next_State));
            }
        }
    }
    return Cost[State];
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> MAP[i][j];
        }
    }

    cin >> S;
    cin >> P;
    
    int Bit_State = 0;
    for (int i = 0; i < S.length(); i++) {
        if (S[i] == 'Y') 
            Bit_State = Bit_State | (1 << i);
    }
 
    memset(Cost, -1, sizeof(Cost));
    Answer = DFS(Bit_State);
 
    if (Answer == INF) cout << -1 << "\n";
    else cout << Answer << "\n";
    return 0;
}
