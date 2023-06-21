#include <iostream>
using namespace std;

string str;

int main() {
    cin >> str;

    if(str[0] == 'F') {
        cout << "0.0";
        return 0;
    }

   float score;

    if(str[0] == 'A') score = 4;
    else if(str[0] == 'B') score = 3;
    else if(str[0] == 'C') score = 2;
    else if(str[0] == 'D') score = 1;

    if(str[1] == '+') score = score + 0.3;
    if(str[1] == '-') score = score - 0.3;

    printf("%.1f", score);
}