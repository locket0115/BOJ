#include <iostream>
#include <algorithm>
#include <string>
 
using namespace std;
 
const int MAXN = 100001 * 2;
 
string str, tmp;
int A[MAXN];
 
void func() {
    int r = 0, p = 0;
    for (int i = 0; i < str.length(); i++) {
        if (i <= r) A[i] = min(A[2 * p - i], r - i);
        else A[i] = 0;
        while (i - A[i] - 1 >= 0 && i + A[i] + 1 < str.length() && str[i - A[i] - 1] == str[i + A[i] + 1]) A[i]++;
 
        if (r < i + A[i]) {
            r = i + A[i];
            p = i;
        }
    }
}

int main() {
    cin >> tmp;
 
    for(int i = 0; i < tmp.length(); i++) {
        str += "#";
        str += tmp[i];
    }
    str += "#";

    func();

    int ans = -1;
    for (int i = 0; i < str.length(); i++) ans = max(ans, A[i]);
    cout << ans;
 
    return 0;
}