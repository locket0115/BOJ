#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <cstring>

using namespace std;

using ll = long long;

int n, k;
ll dp[1 << 15][111];
string s[22];
int arr[22], len[22];
int pw[55];

ll f(int bit, int md){
    ll &res = dp[bit][md];

    if(res != -1) return res;
    
    if(bit + 1 == 1 << n){
        if(md) return res = 0;
        else return res = 1;
    }
    
    res = 0;
    
    for(int i = 0; i < n; i++){
        if(!(bit & (1 << i))){
            int t = md * pw[len[i]] + arr[i];
            res += f(bit | (1 << i), t % k);
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n;
    
    for(int i = 0; i < n; i++) {
        cin >> s[i];
    }
    
    cin >> k;
    
    
    for(int i = 0; i < n; i++) {
        len[i] = s[i].size();
        int t = 0;
        for(auto c : s[i]) {
            t *= 10; t %= k;
            t += c - '0'; t %= k;
        }
        arr[i] = t;
    }

    memset(dp, -1, sizeof dp);
    
    pw[0] = 1 % k;
    
    for(int i = 1; i < 55; i++) pw[i] = pw[i-1] * 10 % k;
    
    ll p = f(0, 0), q = 1;

    if(p == 0) {
        cout << "0/1"; return 0;
    }
    
    for(int i = 1; i <= n; i++) q *= i;
    
    ll g = __gcd(p, q);
    p /= g; q /= g;
    cout << p << "/" << q;
}