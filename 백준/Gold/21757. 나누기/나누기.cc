#include <bits/stdc++.h>

#define LM 100000+10
#define INF 199999999

using namespace std;
 
int N;
long long sum[LM],arr[LM];
long long dp[LM][5];

long long DP(){
    for(int i = 1 ; i <= N ; i++)
        sum[i] = sum[i - 1] + arr[i];
 
    long long query = sum[N] / 4;
    if(query * 4 != sum[N]) return 0;
 
    dp[0][0] = 1;
    for(int i = 1 ; i <= N ; i++){
        dp[i][0] = 1;
        for(int j = 1 ; j <= 3 ; j++){
            dp[i][j] = dp[i - 1][j];
            if(query * j == sum[i]) dp[i][j] += dp[i - 1][j - 1];
        }
    }
    return dp[N - 1][3];
}
 
int main(){
    cin >> N;
    for(int i = 1 ; i <= N ; i++) cin >> arr[i];
    cout << DP();
    return 0;
}