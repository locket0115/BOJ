#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

int main() {
	int T;
	scanf("%d", &T);
	
	while(T--) {
		int v, e;
		scanf("%d %d", &v, &e);
		
		vector <int> edge[20002];
		
		for(int i = 0; i < e; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			
			edge[a].push_back(b);
			edge[b].push_back(a);
		}
		
		vector <int> vertex(20002, 0);
		queue <int> q;
		
		bool flag = true;
		
		while(true) {
			for(int i = 1; i <= v; i++) {
				if(vertex[i] == 0) {
					q.push(i);
					vertex[i] = 1;
					break;
				}
			}
			
			if(q.empty()) {
				break;
			}
			
			while(!q.empty()) {
				int loc = q.front();
				q.pop();
			
				for(int ret : edge[loc]) {
					if(vertex[ret] == vertex[loc]) {
						flag = false;
						break;
					}
				
					if(vertex[ret] == 0) {
						vertex[ret] = vertex[loc] * -1;
						q.push(ret);
					}
				}
				if(flag == false) break;
			}
			if(flag == false) break;
		}
		
		printf(flag ? "YES\n" : "NO\n");
	}
	
	return 0;
}