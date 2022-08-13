#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N;
    cin >> N;

    vector <int> vc;

    for(int i = 0; i < N; i++) {
        string str; cin >> str;

        if(str == "push") {
            int X; cin >> X;

            vc.push_back(X);
        }

        if(str == "pop") {
            if(vc.empty()) cout << "-1\n";
            else {
                cout << vc.back() << "\n";
                vc.pop_back();
            }
        }

        if(str == "size") {
            cout << vc.size() << "\n";
        }

        if(str == "empty") {
            cout << vc.empty() << "\n";
        }

        if(str == "top") {            
            if(vc.empty()) cout << "-1\n";
            else cout << vc.back() << "\n";
        }
    }
}