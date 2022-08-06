#include <iomanip>
#include<iostream>
using namespace std;
 
#define alpha 26
#define maxn 100000
bool inital;
int ans, n;
char arr[maxn][81];
 
struct trie {
    trie* pan[alpha];
    bool end;
    int cnt;
 
    trie() {
        for (int i = 0; i < alpha; ++i)
            pan[i] = nullptr;
        end = false;
        cnt = 0;
    }
    ~trie() {
        for (int i = 0; i < alpha; ++i)
            if (pan[i] != nullptr)
                delete pan[i];
    }
 
    void insert(char* str) {
        if (*str == '\0') {
            end = true;
            return;
        }
            
 
        int cur = *str - 'a';
        if (pan[cur] == nullptr) {
            pan[cur] = new trie();
            cnt++;
        }
        pan[cur]->insert(str + 1);
    }
 
    void find(char* str) {
        if (*str == '\0')
            return;
 
        if (inital) {
            inital = false;
            ans++;
        }
        else {
            if (end)
                ans++;
            else if (cnt > 1)
                ans++;
        }
            
        int cur = *str - 'a';
        pan[cur]->find(str + 1);
    }
};
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin>>n) {
        trie* root = new trie();
        ans = 0;
 
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
            root->insert(arr[i]);
        }
            
        for (int i = 0; i < n; ++i) {
            inital = true;
            root->find(arr[i]);
        }
 
        cout << fixed << setprecision(2)<< (double)ans / (double)n<<'\n';
        delete root;
 
    }
    return 0;
}