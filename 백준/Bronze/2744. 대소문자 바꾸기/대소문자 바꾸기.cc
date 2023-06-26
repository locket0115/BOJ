#include <iostream>
#include <string>

using namespace std;

int main() {
    string str;
    cin >> str;

    for(int i = 0; i < str.length(); i++) {
        if('a' <= str[i] && str[i] <= 'z') str[i] += 'A'-'a';
        else if('A' <= str[i] && str[i] <= 'Z') str[i] += 'a'-'A';
    }

    cout << str;
}