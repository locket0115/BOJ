#include <bits/stdc++.h>
using namespace std;

struct Node {
    string data;
    vector<Node*> s;
}s;

Node* root = new Node;

void insert(vector<string> str, int idx, Node* node) {
    if(str.size() <= idx) return;

    int next = -1;
    for(int i = 0; i < node->s.size(); i++) {
        if(str[idx] == node->s[i]->data) {
            insert(str, idx+1, node->s[i]);
            return;
        }
        if(str[idx] < node->s[i]->data) {    
            Node* nnode = new Node;
            nnode->data = str[idx];
            node->s.insert(node->s.begin()+i, nnode);
            insert(str, idx+1, nnode);

            return;
        }
    }

    Node* nnode = new Node;
    nnode->data = str[idx];
    node->s.push_back(nnode);
    insert(str, idx+1, nnode);
}

void print(Node* node, int idx) {

    if(node->s.empty()) return;

    for(int i = 0; i < node->s.size(); i++) {
        for(int j = 0; j < idx; j++) cout << "--";
        cout << node->s[i]->data << "\n";

        print(node->s[i], idx+1);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int N;
    cin >> N;

    int K;
    vector <string> vc; string str;
    for(int i = 0; i < N; i++) {
        cin >> K;
        for(int j = 0; j < K; j++) {
            cin >> str;
            vc.push_back(str);
        }

        insert(vc, 0, root);

        vc.clear();
    }

    print(root, 0);
    return 0;
}