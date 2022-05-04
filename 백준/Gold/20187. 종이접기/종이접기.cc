#include <iostream>

using namespace std;

char cmd[20];

int horizon[5] = {2, 3, 0, 1};
int vertic[5] = {1, 0, 3, 2};

bool us[10];

int h[5][5], ans[5][5];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int k;
	cin >> k;

	for(int i = 0; i < 2*k; i++) {
		cin >> cmd[i];
	}

	cin >> h[1][1];
	us[h[1][1]] = true;
	
	int hor = -1, ver = -1;
	
	for(int i = 2*k-1; i >= 0; i--) {
		if(hor == -1 && (cmd[i] == 'D' || cmd[i] == 'U')) {
			if(cmd[i] == 'D') hor = 0;
			else hor = 2;
				
			h[hor][1] = horizon[h[1][1]];
			us[horizon[h[1][1]]] = true;
		}
			
		if(ver == -1 && (cmd[i] == 'R' || cmd[i] == 'L')) {
			if(cmd[i] == 'R') ver = 0;
			else ver = 2;
				
			h[1][ver] = vertic[h[1][1]];
			us[vertic[h[1][1]]] = true;
		}
			
		if(ver != -1 && hor != -1) break;
	}
	
	
	for(int i = 0; i <= 3; i++) {
		if(us[i] == false) h[hor][ver] = i;
	}
	
	ans[0][0] = h[min(1, hor)][min(1, ver)];
	ans[0][1] = h[min(1, hor)][max(1, ver)];
	ans[1][0] = h[max(1, hor)][min(1, ver)];
	ans[1][1] = h[max(1, hor)][max(1, ver)];
	
	int l = 1;
	for(int i = 0; i < k-1; i++) l*=2;
	
	for(int i = 0; i < l; i++) {
		for(int k = 0; k <= 1; k++) {
			for(int j = 0; j < l; j++) { cout << ans[k][0] << " " << ans[k][1] << " "; }
			cout << "\n";
		}
	}
	
	return 0;
}