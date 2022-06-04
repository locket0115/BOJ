#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

long long int bt[4000005];
int n, m, k, h = 0;

int pow(int a, int b)
{
	int c = 1;
	for (int i = 0; i < b; i++, c *= a);
	return c;
}

long long int print(int t, int f, int s, int e, int n)
{
	if (s <= t && f <= e)return bt[n];
	if (f < s || e < t)return 0;
	return print(t, (t+f) / 2, s, e, n * 2) + print((t+f) / 2 + 1, f, s, e, n * 2 + 1);
}

void change(int n)
{
	bt[n] = bt[n * 2] + bt[n * 2 + 1];
	if (n>=1) change(n / 2);
}

int main()
{
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; n > i; i *= 2, h++);
	for (int i = 0; i < n; i++)scanf("%lld", &bt[pow(2, h) + i]);
	for (int i = pow(2, h)-1; i >= 1; i--)bt[i] = bt[i * 2] + bt[i * 2 + 1];
	for (int i = 0; i < m + k; i++)
	{
		int a;
		long long b, c;
		scanf("%d %lld %lld", &a, &b, &c);
		if (a == 1)
		{
			bt[pow(2, h) + b-1] = c;
			change((pow(2, h) + b-1)/2);
		}
		else printf("%lld\n", print(1, pow(2, h), b, c, 1));
	}
	return 0;
}