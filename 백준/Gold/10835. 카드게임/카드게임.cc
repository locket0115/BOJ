#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;

int n, a[2001], b[2001], dp[2001][2001] = { 0 };

int card(int left, int right)
{
	if (left == n || right == n)
		return 0;
	if (dp[left][right] != -1)
		return dp[left][right];
	
	dp[left][right] = max(card(left + 1, right), card(left + 1, right + 1));

	if (a[left] > b[right])
		dp[left][right] = max(dp[left][right], card(left, right + 1) + b[right]);
	return dp[left][right];
}

int main()
{
	memset(dp, -1, sizeof(dp));
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	for (int i = 0; i < n; i++)
		scanf("%d", &b[i]);
	printf("%d\n", card(0, 0));
	return 0;
}