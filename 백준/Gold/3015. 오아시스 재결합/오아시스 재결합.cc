#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
	
    int n;
	cin >> n;
    
	vector<long long> v(n);
	stack<pair<long, long>> s;
	for(int i = 0; i < n; i++) cin >> v[i];
	long long ans = 0;

	for (int i = 0; i < n; i++){
		int num = 1;
        while(!s.empty() && s.top().first <= v[i]){
        	if(s.top().first == v[i]){
        		ans += s.top().second;
        		num = s.top().second+1;
        		s.pop();
			}else{
				ans += s.top().second;
				s.pop(); num = 1;
			}
		}

		if(!s.empty()) ans++;
		s.push({v[i], num});
    }
	cout << ans;
}