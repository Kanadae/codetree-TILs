#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#include <algorithm>
#include <utility>
using namespace std;

int n , r, c; // 격자 칸, 시작 행, 시작 열
int map[21][21];
int step[21][21];
int level = 2; // 현재 레벨
int kill = 0;
bool visited[21][21];
queue<pair<int, int>> q;
vector<pair<int, int>> vec; // 나보다 레벨 낮은 로봇 좌표 저장

vector<pair<int, int>> min_v; // 최소 거리 애들 좌표

int sig = 1;
int total = 0;

// 최소 스텝이 여러개면 하나 없앤뒤 다른거 없애러 바로 가야함



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
			if (map[nx][ny] > level) continue;
			if (visited[nx][ny]) continue;


			step[nx][ny] = step[x][y] + 1;

			if (map[nx][ny]!= 0 && map[nx][ny] < level)
			{
				sig = 1;
				vec.push_back(make_pair(nx, ny));
				visited[nx][ny] = true;
				continue;
			}

			visited[nx][ny] = true;
			q.push(make_pair(nx, ny));
		}
	}

	
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 9)
			{
				r = i; c = j;
				map[i][j] = 0;
			}
		}
	}

	while (sig)
	{
		sig = 0;
		q.push(make_pair(r, c)); // 현재 위치 넣고
		bfs(); // 가장 가까우면서 내 렙보다 낮은 곳 찾기
		if (sig == 0) break;
		int temp_min_step = INT_MAX;
		int minx; int miny;
		for (int i = 0; i < vec.size(); i++)
		{
			int x = vec[i].first;
			int y = vec[i].second;
			if (temp_min_step > step[x][y])
			{
				min_v.clear(); // 최소 좌표들 초기화
				temp_min_step = step[x][y];
				min_v.push_back(make_pair(x,y));
			}
			else if (temp_min_step == step[x][y])
			{
				min_v.push_back(make_pair(x, y));
			}
		}

		sort(min_v.begin(), min_v.end());

		for (int i = 0; i < min_v.size(); i++)
		{
			r = min_v[i].first;
			c = min_v[i].second;
			total += step[r][c];
			map[r][c] = 0;
			
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					visited[i][j] = false;
					step[i][j] = 0;
				}
			}
			q.push(make_pair(r, c));
			bfs();
			kill++;
			if (kill == level)
			{
				kill = 0;
				level++;
			}
		}
		vec.clear();
		min_v.clear();
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				visited[i][j] = false;
				step[i][j] = 0;
			}
		}
	}

	cout << total;

}