#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

int n, m, k;
int r, c;
int map[101][101];
bool visited[101][101];
vector<pair<int, int>> stone;
vector<pair<int, int>> start;
queue<pair<int, int>> q;
int max_cnt = -1;
int cnt = 0;

void Initial()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			visited[i][j] = false;
		}
	}
}

void Push(int x, int y)
{
	q.push(make_pair(x, y));
	visited[x][y] = true;
}

bool canGo(int x, int y)
{
	if (!(0 <= x && x < n && 0 <= y && y < n)) return false;
	if (visited[x][y]) return false;
	if (map[x][y] == 1) return false;
	return true;
}

void bfs()
{
	int dx[4] = { 0, 1, 0, -1 };
	int dy[4] = { 1, 0, -1, 0 };
	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();
		int x = cur.first;
		int y = cur.second;
		for (int i = 0; i < 4; i++)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (canGo(nx, ny)) {
				Push(nx, ny);
				cnt++;
			}
		}
	}
}

int main()
{
	cin >> n >> k >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 1) stone.push_back(make_pair(i, j));
		}
	}

	for (int i = 0; i < k; i++)
	{
		cin >> r >> c;
		r--; c--;
		start.push_back(make_pair(r, c));
	}

	int s_size = stone.size();
	for (int i = 0; i < s_size - 1; i++)
	{
		pair<int, int> temp_stone = stone[i];
		int stone_x = temp_stone.first;
		int stone_y = temp_stone.second;
		map[stone_x][stone_y] = 0;
		for (int j = 1; j < s_size; j++)
		{
			pair<int, int> second_stone = stone[j];
			int sec_stone_x = second_stone.first;
			int sec_stone_y = second_stone.second;
			map[sec_stone_x][sec_stone_y] = 0;
			for (int b = 0; b < k; b++)
			{
				pair<int, int> start_xy = start[b];
				int start_x = start_xy.first;
				int start_y = start_xy.second;
				Push(start_x, start_y);
				bfs();
			}
			if (cnt > max_cnt) max_cnt = cnt;
			cnt = 0;
			Initial();
			map[sec_stone_x][sec_stone_y] = 1;
		}
		map[stone_x][stone_y] = 1;
	}

	cout << max_cnt;

}