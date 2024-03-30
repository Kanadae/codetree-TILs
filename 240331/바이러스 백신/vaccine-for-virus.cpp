#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int n, m;
int map[51][51];
pair<int, int> hospital[11];
int hos_cnt;
queue<pair<int, int>> q;
vector<pair<int, int>> vec;
bool visited[51][51];
int step[51][51];
int temp_step[51][51];
int sig = 0;
int ans = INT_MAX;

void bfs()
{
	int dx[4] = { 0,1,0,-1 };
	int dy[4] = { 1,0,-1,0 };
	while (!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 > nx || nx >= n || 0 > ny || ny >= n) continue;
			if (visited[nx][ny] || map[nx][ny] == 1) continue;
			visited[nx][ny] = true;
			temp_step[nx][ny] = temp_step[x][y] + 1;
			if (step[nx][ny] == 0 || step[nx][ny] > temp_step[nx][ny])
			{
				step[nx][ny] = temp_step[nx][ny];
			}
			q.push(make_pair(nx, ny));
		}
	}
}

void dfs(int cur, int idx)
{
	if (cur == m || idx == hos_cnt)
	{
		if (cur != m) return;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				step[i][j] = 0;
			}
		}

		for (int i = 0; i < m; i++)
		{
			int x = vec[i].first;
			int y = vec[i].second;
			q.push(make_pair(x, y));
			bfs();
			for (int j = 0; j < n; j++)
			{
				for (int k = 0; k < n; k++)
				{
					visited[j][k] = false;
					temp_step[j][k] = 0;
				}
			}
		}

		int temp = 0;
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				if (temp < step[j][k] && map[j][k] != 2) temp = step[j][k];
				if (map[j][k] == 0 && step[j][k] == 0) return;
				step[j][k] = 0;
			}
		}
		if (ans > temp) ans = temp;
		sig = 1;
		return;
	}

	vec.push_back(hospital[idx]);
	dfs(cur + 1, idx + 1);
	vec.pop_back();
	dfs(cur, idx + 1);
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 2) hospital[hos_cnt++] = make_pair(i, j);
		}
	}

	

	dfs(0, 0);


	if (sig == 0) cout << -1; 
	else
		cout << ans;
}