#include <cstdio>
#include <queue>

using namespace std;

#define max(n, m) n > m ? n : m

vector<pair<int, int>> world[10001];
vector<pair<int, int>> back[10001];

int dist[10001];
int idx[10001];
int visit[10001];

int main()
{

	int n, m;
	scanf("%d %d", &n, &m);
	while (m--)
	{
		int x, y, t;
		scanf("%d %d %d", &x, &y, &t);
		world[x].push_back({ y, t });
		back[y].push_back({ x, t });
		idx[y] += 1;
	}

	int s, e;
	scanf("%d %d", &s, &e);

	queue<int> q;
	q.push(s);

	while (!q.empty())
	{
		int x = q.front();
		q.pop();

		for (int k = 0; k < world[x].size(); k++)
		{
			int node = world[x][k].first;
			int dst = world[x][k].second;

			idx[node]--;
			if (idx[node] == 0)
			{
				q.push(node);
			}
			dist[node] = max(dist[node], dist[x] + dst);
		}
	}

	q.push(e);
	int cnt = 0;
	while (!q.empty())
	{
		int x = q.front();
		q.pop();

		for (int k = 0; k < back[x].size(); k++)
		{
			int node = back[x][k].first;
			int dst = back[x][k].second;

			if (dst == dist[x] - dist[node])
			{
				cnt += 1;
				if (!visit[node])
				{
					visit[node] = 1;
					q.push(node);
				}
			}
		}
	}
	printf("%d\n%d\n", dist[e], cnt);
	return 0;
}