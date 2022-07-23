#include <bits/stdc++.h>
using namespace std;

const int nMAX = 40001;
const int iMAX = 16;
int N;

vector<pair<int, int>> adj[nMAX];
bool visited[nMAX];

int length[nMAX][iMAX];
int parent[nMAX][iMAX];
int depth[nMAX];


void dfs(int start, int n){
	visited[start] = true;
	depth[start] = n;
	for(int i=0; i<adj[start].size(); i++){
		int next = adj[start][i].first;
		int weight = adj[start][i].second;
		
		if(visited[next]) continue;
		
		parent[next][0] = start;
		length[next][0] = weight;
		dfs(next, n+1);
	}
}

void connect(){
	for(int p=1; p<iMAX; p++){
		for(int cur=1; cur<=N; cur++){
			int prevParent = parent[cur][p-1];
			parent[cur][p] = parent[prevParent][p-1];
			
			if(parent[prevParent][p-1] == 0) continue;
			
			int prevLength = length[cur][p-1];
			length[cur][p] = prevLength + length[prevParent][p-1];
		}
	}
}

int LCA(int xNode, int yNode){
	if(depth[xNode] > depth[yNode]){
		int temp = xNode;
		xNode = yNode;
		yNode = temp;
	}
	int lenSum = 0;
    
	for(int i=iMAX-1; i>=0; i--){
		int jump = 1 << i;
		if(depth[yNode] - depth[xNode] >= jump){
			lenSum += length[yNode][i];
			yNode = parent[yNode][i];
		}
	}
    
	if(xNode == yNode) return lenSum;
    
	for(int i=iMAX-1; i>=0; i--){
		if(parent[xNode][i] == parent[yNode][i]) continue;
		
		lenSum += length[xNode][i];
		xNode = parent[xNode][i];
		
		lenSum += length[yNode][i];
		yNode = parent[yNode][i];
	}
	
	lenSum += length[xNode][0] + length[yNode][0];
	return lenSum;
}

int main(){
	cin >> N;
	for(int i=1; i<N; i++){
		int s,e,w;
		cin >> s >> e >> w;
		
		adj[s].push_back({e,w});
		adj[e].push_back({s,w});
	}
	
	int M;
	int ans[10001][2];
	
    cin >> M;
	for(int i=0; i<M; i++){
		cin >> ans[i][0] >> ans[i][1];
	}
	
	dfs(1, 0);
	connect();
		
	for(int i=0; i<M; i++){
		int x = ans[i][0], y = ans[i][1];
		cout << LCA(x, y) << "\n";
	}
}