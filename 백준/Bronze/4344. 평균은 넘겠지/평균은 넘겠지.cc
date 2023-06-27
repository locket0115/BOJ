#include <iostream>

using namespace std;

int arr[1005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed;
    cout.precision(3);

    int T;
    cin >> T;

    while(T--) {
        int n;
        cin >> n;

        float avg = 0.0;

        for(int i = 0; i < n; i++) {
            cin >> arr[i];

            avg += arr[i];
        }

        avg /= n;

        int res = 0;
        for(int i = 0; i < n; i++) {
            if(arr[i] > avg) res++;
        }

        float ans = (float)res / n *100;
        cout << ans << "%\n";
    }
}