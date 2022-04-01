#include <iostream>

#define MAX 987654321

using namespace std;

int N;
int val[16][16];
int dp[16][1 << 16] = { 0 };

int func(int cur, int visited){
  if(dp[cur][visited] != 0) return dp[cur][visited];

  if(visited == (1 << N) - 1) {
    if(val[cur][0] != 0) return val[cur][0];
    else return MAX;
  }

  int result = MAX;

  for(int i = 0; i < N; i++) {
    if(!((1 << i) & visited) && (val[cur][i] != 0)){
      result = min(result, val[cur][i] + func(i, visited + (1 << i)));
    }
  }

  return dp[cur][visited] = result;
}


int main() {
  cin >> N;
  for(int i = 0; i< N; i++){
    for(int j = 0; j < N; j++){
      cin >> val[i][j];
    }
  }

  cout << func(0, 1) << endl;

  return 0;
}