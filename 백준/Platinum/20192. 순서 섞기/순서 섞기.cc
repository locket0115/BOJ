#include <iostream>

using namespace std;

int arr[300003];
bool diff[300003];

int main() {
    int N;
    cin >> N;

    int dt = 0;

    for(int i = 1; i <= N; i++) {
        cin >> arr[i];
        diff[i] = (arr[i-1] == arr[i] ? diff[i-1] : arr[i-1] < arr[i]);
    }

    if(arr[1] == arr[2]) {
        int chloc = -1, chval = -1;
        for(int i = 2; i <= N; i++) {
            if(arr[i-1] != arr[i]) {
                chloc = i, chval = diff[i];
                break;
            }
        }

        for(int i = 1; i <= chloc; i++) diff[i] = chval;
    }
    
    diff[0] = 1;

    for(int i = 1; i <= N; i++) {
        dt += diff[i] != diff[i-1];
    }


    int ans = 0;
    while(dt != 0) {
        dt/=2;
        ans++;
    }

    cout << ans;
}