#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

int pdx[9] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
int pdy[9] = { 0, 0, 1, 1, 1, 0, -1, -1, -1 };

int map[10][10];
int n, m, k;
int history[10][10];
int visited[10][10];
int turn = 1;
int back_x[10][10];
int back_y[10][10];

int active[10][10];

void attack()
{
	int min_AD = INT_MAX;
	int ax, ay;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] == 0) continue;
			if (map[i][j] < min_AD)
			{
				min_AD = map[i][j];
				ax = i; ay = j;
			}
			else if (map[i][j] == min_AD)
			{
				if (history[i][j] > history[ax][ay])
				{
					ax = i; ay = j;
				}
				else if (history[i][j] == history[ax][ay])
				{
					if (ax + ay < i + j)
					{
						ax = i; ay = j;
					}
					else if (ax + ay == i + j)
					{
						if (ay < j)
						{
							ax = i; ay = j;
						}
					}
				}
			}
		}

	int MAX_AD = INT_MIN;
	int vx, vy;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] == 0) continue;
			if (ax == i && ay == j) continue;
			if (map[i][j] > MAX_AD)
			{
				MAX_AD = map[i][j];
				vx = i; vy = j;
			}
			else if (map[i][j] == MAX_AD)
			{
				if (history[i][j] < history[vx][vy])
				{
					MAX_AD = map[i][j];
					vx = i; vy = j;
				}
				else if (history[i][j] == history[vx][vy])
				{
					if (i + j < vx + vy)
					{
						vx = i; vy = j;
					}
					else if (i + j == vx + vy)
					{
						if (j < vy)
						{
							vx = i; vy = j;
						}
					}
				}
			}
		}
	//cout << ax << " " << ay << " " << vx << " " << vy;
	map[ax][ay] += m + n;
	active[ax][ay] = 1; active[vx][vy] = 1;
	history[ax][ay] = turn;
	int razer = 0;
	queue<pair<int, int>> q;
	q.push(make_pair(ax, ay));
	while (!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		if (x == vx && y == vy)
		{
			razer = 1;
			break;
		}
		for (int i = 0; i < 4; i++)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx < 0) nx = n - 1;
			else if (nx >= n) nx = 0;
			if (ny < 0) ny = m - 1;
			else if (ny >= m) ny = 0;
			if (map[nx][ny] == 0) continue;
			if (visited[nx][ny]) continue;
			visited[nx][ny] = true;
			back_x[nx][ny] = x;
			back_y[nx][ny] = y;
			q.push(make_pair(nx, ny));
		}
	}

	if (razer == 1)
	{
		int x = vx; int y = vy;
		while (!(x == ax && y == ay))
		{
			if (x == vx && y == vy)
			{
				map[x][y] -= map[ax][ay];
				if (map[x][y] < 0) map[x][y] = 0;
				active[x][y] = 1;
			}
			else
			{
				map[x][y] -= (map[ax][ay] / 2);
				if (map[x][y] < 0) map[x][y] = 0;
				active[x][y] = 1;
			}
			int nx = back_x[x][y];
			int ny = back_y[x][y];
			x = nx;
			y = ny;
		}
	}

	else if (razer == 0)
	{
		int x = vx; int y = vy;
		for (int i = 0; i < 9; i++)
		{
			int nx = x + pdx[i];
			int ny = y + pdy[i];
			if (nx < 0) nx = n - 1;
			else if (nx >= n) nx = 0;
			if (ny < 0) ny = m - 1;
			else if (ny >= m) ny = 0;
			if (map[nx][ny] == 0) continue;
			if (nx == ax && ny == ay) continue;
			if (nx == vx && ny == vy)
			{
				map[nx][ny] -= map[ax][ay];
			}
			else map[nx][ny] -= (map[ax][ay] / 2);
			if (map[nx][ny] < 0) map[nx][ny] = 0;
			active[nx][ny] = 1;
		}
	}

}

pair<int,int> count()
{
	int ans = 0;
	int cnt = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] == 0) continue;
			cnt++;
			if (active[i][j] == 0)
			{
				map[i][j]++;
			}
			if (map[i][j] > ans)
			{
				ans = map[i][j];
			}
		}

	return make_pair(ans, cnt);
}

void init()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			visited[i][j] = false;
			active[i][j] = 0;
			back_x[i][j] = 0;
			back_y[i][j] = 0;
		}
}

void Print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << map[i][j] << " ";
		}
		cout << "\n";
	}
}

int main()
{
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			cin >> map[i][j];
		}

	int ans, cnt;
	while (turn <= k)
	{
		//cout << turn << "턴\n";
		//Print();
		attack();
		pair<int, int> temp = count();
		ans = temp.first; cnt = temp.second;
		if (cnt <= 1) break;
		init();
		turn++;
		//cout << turn << "턴\n";
		//Print();
	}

	cout << ans;
}