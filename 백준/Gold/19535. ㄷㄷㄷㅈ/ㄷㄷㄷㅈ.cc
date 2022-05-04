#include <stdio.h>
#include <vector>

using namespace std;

vector <int> graph[300002];

long long answer[2];

long long C[300002][5];

int main()
{
	C[0][0] = 1;
	for (int i = 1; i <= 300001; i++)
	for (int j = 0; j <= 3; j++)
		C[i][j] = C[i - 1][j - 1] + C[i - 1][j];

	int N;
	scanf("%d", &N);

	int u, v;
	for (int i = 1; i < N; i++)
	{
		scanf("%d %d", &u, &v);
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	for (int i = 1; i <= N; i++)
	{
		if (graph[i].size() >= 3)
			answer[1] += C[graph[i].size()][3];

		for (int j : graph[i])
		{
			if (j < i)
				continue;

			answer[0] += (graph[i].size() - 1) * (graph[j].size() - 1);
		}
	}
	if (answer[0] > answer[1] * 3)
		printf("D\n");
	else if (answer[0] == answer[1] * 3)
		printf("DUDUDUNGA\n");
	else if (answer[0] < answer[1] * 3)
		printf("G\n");

	return 0;
}