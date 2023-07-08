#include <iostream>
#include <math.h>
#include <vector>
#include <limits>
using namespace std;

constexpr double INF = numeric_limits<double>::max();

struct Point{
	long double x, y;
};

struct Circle{
	Point p;
	long double r;
};

double dist(Point const A, Point const B){
	return (double)(sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2)));
}

Point center(Point const& A, Point const& B){
	long double XX = A.x * A.x + A.y * A.y;
	long double YY = B.x * B.x + B.y * B.y;
	long double D = A.x * B.y - A.y * B.x;
	
	return { (B.y * XX - A.y * YY) / (D * 2), (A.x * YY - B.x * XX) / (D * 2) };
}

Circle getCircle(Point const& A, Point const& B){
	Point point = { (A.x + B.x) / 2.0, (A.y + B.y) / 2.0 };
	return { point, dist(A, B) / 2.0 };
}

Circle getCircle(Point const& A, Point const& B, Point const& C){
	Point point = center({B.x-A.x, B.y-A.y}, {C.x-A.x, C.y-A.y});
	point.x += A.x;
	point.y += A.y;
	
	return {point, dist(point, A)};
}

bool isValid(vector<Point> const& p, Circle const& A){
	for(Point const& i : p){
		if(A.r < dist(A.p, i)) return false;
	}
	
	return true;
}

Circle Solve(vector<Point> const& p){
	int n = (int)p.size();
	
	if(n == 0) return { { 0, 0 }, 0.0 };
	if(n == 1) return { { p[0] }, 0.0 };
	
	Circle result = { { 0, 0 }, INF };
	
	for(int i = 0;i < n; i++){
		for(int j = i+1;j < n; j++){
			Circle temp = getCircle(p[i], p[j]);
			
			if(temp.r < result.r && isValid(p, temp)) result = temp;
		}
	}
	
	for(int i = 0; i < n; i++){
		for(int j = i+1; j < n; j++){
			for(int k = j+1; k < n; k++){
				Circle temp = getCircle(p[i], p[j], p[k]);
				
				if(temp.r < result.r && isValid(p, temp)) result = temp;
			}
		}
	}
	
	return result;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	vector<Point> point;
	int N;
	
	cin >> N;
	for(int i = 0; i < N; i++){
		long double x, y;
		cin >> x >> y;
		
		point.push_back({ x, y });
	}
	
	Circle ans = Solve(point);
	
    cout << fixed;
	cout.precision(2);
	cout << ans.r * 2;
}