#include <stdio.h>

long long dp[40];
char rank[40];


int main() {
    long long N, s, g, p, d;
    scanf("%lld", &N);
    scanf("%lld %lld %lld %lld", &s, &g, &p, &d);
    scanf("%s", rank);

    switch (rank[0]) {
    case 'B':
        dp[0] = s-1;
        break;
    case 'S':
        dp[0] = g-1;
        break;
    case 'G':
        dp[0] = p-1;
        break;
    case 'P':
        dp[0] = d-1;
        break;
    case 'D':
        dp[0] = d;
        break;
    }

    for(int i = 1; i < N; i++) {
        if(rank[i] == 'B') {
            if(dp[i-1] > s-1) {
                dp[i-1] = s-1;
            }
            dp[i] = s-1-dp[i-1];
        }
        if(rank[i] == 'S') {
            if(dp[i-1] > g-1) {
                dp[i-1] = g-1;
            }
            dp[i] = g-1-dp[i-1];
        }
        if(rank[i] == 'G') {
            if(dp[i-1] > p-1) {
                dp[i-1] = p-1;
            }
            dp[i] = p-1-dp[i-1];
        }
        if(rank[i] == 'P') {
            if(dp[i-1] > d-1) {
                dp[i-1] = d-1;
            }
            dp[i] = d-1-dp[i-1];
        }
        if(rank[i] == 'D') {
            dp[i] = d;
        }
    }


    long long ans = 0;
    for(int i = 0; i < N; i++) {
        ans += dp[i];
    }

    printf("%lld\n", ans);
}