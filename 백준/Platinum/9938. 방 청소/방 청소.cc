#include <stdio.h>

bool taken[300005];
int parent[300005];

int find(int x)
{
	if (x == parent[x])
		return x;
	else
		return parent[x] = find(parent[x]);
}

void untie(int x, int y)
{
	x = find(x);
	y = find(y);
	parent[x] = y;
	puts("LADICA");
}

int main()
{
	int n, l;
	scanf("%d %d", &n, &l);

	for (int i = 1; i <= l; i++)
		parent[i] = i;

	for (int i = 0; i < n; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);

		if (!taken[a])
		{
			taken[a] = true;
			untie(a, b);
		}
		else if (!taken[b])
		{
			taken[b] = true;
			untie(b, a);
		}
		else if (!taken[find(a)])
		{
			taken[find(a)] = true;
			untie(a, b);
		}
		else if (!taken[find(b)])
		{
			taken[find(b)] = true;
			untie(b, a);
		}
		else
			puts("SMECE");
	}
	return 0;
}