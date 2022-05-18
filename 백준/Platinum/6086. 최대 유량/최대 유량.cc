#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <memory.h>

#define MAX 52
#define INF 987654321
 
using namespace std;

vector<int> adj[MAX];

int c[MAX][MAX];
int f[MAX][MAX];
 
int main() {
  int n; scanf("%d", &n);
  
  for (int i = 0; i < n; i++) {
    char chfrom, chto; int val;
    scanf(" %c %c %d", &chfrom, &chto, &val);
 
    int from, to;
    if ('A' <= chfrom && chfrom <= 'Z') from = chfrom - 'A';
    else from = chfrom - 'a' + 26;

    if ('A' <= chto && chto <= 'Z') to = chto - 'A';
    else to = chto - 'a' + 26;
 
    c[from][to] += val;
    c[to][from] += val; 
    
    adj[from].push_back(to);
    adj[to].push_back(from);
  }
 
  int totalFlow = 0, S = 0, T = 'Z' - 'A';
  
  while (1) {
    int prev[MAX];
    memset(prev, -1, sizeof(prev));
 
    queue<int> q;
    q.push(S);
 
    while (!q.empty()) {
      int cur = q.front();
      q.pop();
 
      for (int next : adj[cur]) {
        if (prev[next] != -1) continue;
 
        if (c[cur][next] - f[cur][next] > 0) {
          q.push(next);
          prev[next] = cur;
          if (next == T) break;
        }
      }
    }
 
    if (prev[T] == -1) break;
 
    int flow = INF;
 
    for (int i = T; i != S; i = prev[i])
      flow = min(flow, c[prev[i]][i] - f[prev[i]][i]);
      
    for (int i = T; i != S; i = prev[i]) {
      f[prev[i]][i] += flow;
      f[i][prev[i]] -= flow;
    }
 
    totalFlow += flow;
  }
 
  printf("%d\n", totalFlow);
 
  return 0;
}