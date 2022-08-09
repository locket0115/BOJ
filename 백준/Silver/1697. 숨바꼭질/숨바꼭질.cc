#include <stdio.h>
#include <queue>

using namespace std;

queue <pair<int, int>> que;

int v[100005];

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);

	if (n > m)
	{
		printf("%d\n", n - m);
		return 0;
	}

	que.push({ n, 0 });
	v[n] = 1;

	while (!que.empty())
	{
		int l = que.front().first, t = que.front().second;

		if (l == m)
		{
			printf("%d\n", t);
			return 0;
		}

		if (l - 1 >= 0 && !v[l - 1])
		{
			que.push({ l - 1, t + 1 });
			v[l - 1] = 1;
		}
		if (l + 1 <= 100000 && !v[l + 1])
		{
			que.push({ l + 1, t + 1 });
			v[l + 1] = 1;
		}
		if (l * 2 <= 100000 && !v[l * 2])
		{
			que.push({ l * 2, t + 1 });
			v[l * 2] = 1;
		}

		que.pop();
	}

	return 0;
}