#include <stdio.h>
#include <iostream>

using namespace std;

int up[100001][600];
int ucnt[100001];
int down[100001][600];
int dcnt[100001];
int queue[100001];
int visit[100001];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int N, M, X;
	register int i, data, j;

	cin >> N >> M >> X;

	for (i = 1; i <= M; i++) {
		int a, b;
		cin >> a >> b;
		up[a][ucnt[a]++] = b;
		down[b][dcnt[b]++] = a;
	}

	i = 1; j = 0;
	queue[0] = X;
	visit[X] = 1;
	
	while (j < i) {
		int d = queue[j++];
		int cnt = ucnt[d];
		for (int k = 0; k < cnt; k++) {
			data = up[d][k];
			if (visit[data] == 1) continue;
			visit[data] = 1;
			queue[i++] = data;
		}
	}
	
	int downcnt = N - i + 1;
	i = 1; j = 0;
	queue[0] = X;
	
	while (j < i) {
		int d = queue[j++];
		int cnt = dcnt[d];
		for (int k = 0; k < cnt; k++) {
			data = down[d][k];
			if (visit[data] == 1) continue;
			visit[data] = 1;
			queue[i++] = data;
		}
	}
	
	cout << i << " " << downcnt;
}