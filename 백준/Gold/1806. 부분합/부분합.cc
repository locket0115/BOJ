#include <iostream>

using namespace std;

int arr[100005];
int idx[100005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int N, S;
    cin >> N >> S;

    for(int i = 1; i <= N; i++) {
        cin >> arr[i];
        idx[i] = idx[i-1] + arr[i];
    }

    int l = 0, r = 1;

    int ans = 1234567890;

    while(1){
        int sum = idx[r] - idx[l];
        if(sum >= S) {
            ans = min(ans, r-l);
            l++;
        }
        else if(r < N) r++;
        else break;
    }

    if(ans != 1234567890) cout << ans;
    else cout << 0;
}