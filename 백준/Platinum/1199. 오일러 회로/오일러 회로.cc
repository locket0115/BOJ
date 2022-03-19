#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

int n;
int nxt[1010];
int adj[1010][1010];
vector<int> route;

void getEuler(int here){
    for (int &there=nxt[here]; there<=n; there++){
        while(adj[here][there]){
            adj[here][there]--;
            adj[there][here]--;
            getEuler(there);
        }
    }
    route.push_back(here);
}

int main() {
    int startPoint=0;
    int edgeNum[1010]={0,};
    
    cin>>n;
    
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            cin>>adj[i][j];
            edgeNum[i] += adj[i][j];
        }
    }
    
    for (int i=1; i<=n; i++){
        if (edgeNum[i] != 0) startPoint = i;
        if (edgeNum[i] % 2 == 1){
            cout<<-1;
            return 0;
        }
    }
    for (int i=1; i<=n; i++) nxt[i]=1;
    getEuler(startPoint);
    
    for (int i=0; i<route.size(); i++){
        cout<<route[i]<<' ';
    }
}