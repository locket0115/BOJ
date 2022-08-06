#include <iostream>
#include <algorithm>
using namespace std;

const int SIZE = 1<<18;
typedef pair<int, int> P;
 
struct SegTree{
    int arr[SIZE];
    SegTree(){ fill(arr, arr+SIZE, 0); }
    // n번째 리프 노드 1 증가
    void inc(int n){
        n += SIZE/2;
        while(n > 0){
            arr[n]++;
            n /= 2;
        }
    }

    // s~e의 합
    int sum(int s, int e){ return sum(s, e, 1, 0, SIZE/2); }
    int sum(int s, int e, int node, int ns, int ne){
        if(e <= ns || ne <= s) return 0;
        if(s <= ns && ne <= e) return arr[node];
        int mid = (ns+ne)/2;
        return sum(s, e, node*2, ns, mid) + sum(s, e, node*2+1, mid, ne);
    }
};
 
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int T; cin >> T;
    while(T--) {
        SegTree ST;
        P p[75000];
        
        int N, range = 0;
        cin >> N;
        
        for(int i = 0; i < N; i++){
            cin >> p[i].first >> p[i].second;
        }
 
        sort(p, p+N, [](P &a, P &b){
            return a.second < b.second;
        });

        int newY[750000];
        for(int i = 0; i < N; i++){
            if(i > 0 && p[i].second != p[i-1].second) range++;
            newY[i] = range;
        }

        for(int i = 0; i < N; i++) p[i].second = newY[i];

        sort(p, p+N, [](P &a, P &b){
            if(a.first == b.first) return a.second > b.second;
            return a.first < b.first;
        });

        long long result = 0;
        for(int i = 0; i < N; i++){
            result += ST.sum(p[i].second, SIZE/2);
            ST.inc(p[i].second);
        }

        cout << result << "\n";
    }
}