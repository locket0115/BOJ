#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <math.h>
#include <algorithm>

using namespace std;

using ll = long long;

int N, M;

struct Point {
	int x, y, w;
};

struct MSP {
	ll sum, lmax, rmax, tmax;
};

Point p[3001];
vector<pair<int, int> > x, y, yy[3001];
MSP seg[12121];

MSP Update(int idx, int val, int n, int l, int r) {
	if (r < idx || idx < l) return seg[n];

	if (l == r && l == idx) {
		seg[n].sum += val, seg[n].lmax += val, seg[n].rmax += val, seg[n].tmax += val;
		return seg[n];
	}

	int mid = (l + r) / 2;
	MSP left, right;
	left = Update(idx, val, n * 2, l, mid);
	right = Update(idx, val, n * 2 + 1, mid + 1, r);

	seg[n].sum = left.sum + right.sum;
	seg[n].lmax = max(left.lmax, left.sum + right.lmax);
	seg[n].rmax = max(right.rmax, right.sum + left.rmax);
	seg[n].tmax = max({ left.tmax, right.tmax, left.rmax + right.lmax });
	return seg[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
	for (int i = 0; i < N; i++) {
		int tx, ty;
        cin >> tx >> ty;
		x.push_back({ tx, i });
		y.push_back({ ty, i });
	}

    cin >> M;
	for (int i = N; i < N+M; i++) {
		int tx, ty;
        cin >> tx >> ty;
		x.push_back({ tx, i });
		y.push_back({ ty, i });
	}

    int c1, c2;
    cin >> c1 >> c2;

    for(int i = 0; i < N; i++) p[i].w = c1;
    for(int i = N; i < N+M; i++) p[i].w = -c2;

	sort(x.begin(), x.end());
	sort(y.begin(), y.end());

	int num = 0;
	for (int i = 0; i < N+M; i++) {
		if (i > 0 && x[i - 1].first != x[i].first) num++;
		p[x[i].second].x = num;
	}

	num = 0;
	for (int i = 0; i < N+M; i++)  
	{
		if (i > 0 && y[i - 1].first != y[i].first) num++;
		p[y[i].second].y = num;
	}

	for (int i = 0; i < N+M; i++)
		yy[p[i].y].push_back({ p[i].x, p[i].w });

	ll res = 0; 
	for (int sy = 0; sy < N+M; sy++) {
		for (int i = 0; i < 12121; i++) {
			MSP temp;
			temp.sum = 0, temp.lmax = 0, temp.rmax = 0, temp.tmax = 0;
			seg[i] = temp;
		}

		for (int ey = sy; ey < N+M; ey++) {
			for (int i = 0; i < yy[ey].size(); i++) {
				int hx = yy[ey][i].first, hy = ey, hw = yy[ey][i].second;

				Update(hx, hw, 1, 0, N+M - 1);
			}

			res = max(res, seg[1].tmax);
		}
	}

    cout << res;
	
    return 0;
}