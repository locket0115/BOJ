#include <iostream>
#include <stack>

using namespace std;

int h[100000];
 
int main(void)
{
    int n;
    cin >> n;
    stack<int> s;
    for (int i = 0; i < n; i++) cin >> h[i];
    long long area = 0;
 
    for (int i = 0; i < n; i++) {
        while (!s.empty() && h[s.top()] > h[i]) {
            long long height = h[s.top()];
            s.pop();
            long long width = i;
            if (!s.empty()) width = i - s.top() - 1;
            if (width*height > area) area = width * height;
        }
        s.push(i);
    }
 
    while (!s.empty()) {
        long long height = h[s.top()];
        s.pop();
        long long width = n;
        if (!s.empty()) width = n - s.top() - 1;
        if (width*height > area) area = width * height;
    }
    cout << area << '\n';
    return 0;
}
