#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

#define pii pair<int, int>

int n, d;
vector<pair<int, int>> input;
vector<pii> inputQ;
priority_queue<int, vector<int>, greater<int>> pq;

bool compare(const pair<int, int>& a, const pair<int, int>& b) {
	if (a.second != b.second) {
		return a.second < b.second;
	}
	else if (a.second == b.second) {
		return a.first < b.first;
	}
}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		int h, o;
		cin >> h >> o;
		if (h > o)inputQ.push_back({ o,h });
		else inputQ.push_back({ h,o });
	}
	cin >> d;

	sort(inputQ.begin(), inputQ.end(), compare);

	int maxSize = 0;

	for(int i = 0; i<inputQ.size(); i++){
		int iR = inputQ[i].second;
		int iL = inputQ[i].first;

		if (iR - iL <= d) {
			pq.push(iL);
		}
		else continue;

		while (!pq.empty()) {
			int tmp = pq.top();
			if (iR - tmp <= d) break;
			else 
				pq.pop();		
		}
		maxSize = max(maxSize, (int)pq.size());
	}

	cout << maxSize;
	return 0;
}