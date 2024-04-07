#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAX_N 10
#define MAX_M 10
#define MAX_K 1000
#define REI 4
#define PO 8

int n, m, k;
int turn = 1;
int ad[MAX_K+1][11][11];
int history[11][11]; // 값이 클수록 최근 공격

int step[10][10]; // 최단경로
int rei_dx[4] = { 0,1,0,-1 };
int rei_dy[4] = { 1,0,-1,0 };
int po_dx[8] = { -1,-1,0,1,1,1,0,-1 };
int po_dy[8] = { 0,1,1,1,0,-1,-1,-1 };

int back_x[11][11]; int back_y[11][11];
bool visited[11][11];
int is_active[MAX_K+1][11][11];

pair<int,int> choice_attacker()
{
	int min_ad = 50000;
	int mini, minj;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if (ad[turn - 1][i][j] == 0) continue;
			if (ad[turn - 1][i][j] < min_ad)
			{
				min_ad = ad[turn - 1][i][j];
				mini = i; minj = j;
			}
			else if (ad[turn - 1][i][j] == min_ad)
			{
				if (history[i][j] >= history[mini][minj])
				{
					mini = i; minj = j;
				}
			}
		}
	return make_pair(mini, minj);
}

pair<int, int> victim(pair<int, int> temp)
{
	int max_ad = -1;
	int maxi = -1, maxj = -1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			
			if (ad[turn - 1][i][j] == 0 || make_pair(i, j) == temp) continue;
			if (ad[turn - 1][i][j] > max_ad)
			{
				
				max_ad = ad[turn - 1][i][j];
				maxi = i; maxj = j;
			}
			else if (ad[turn - 1][i][j] == max_ad)
			{
				if (history[i][j] < history[maxi][maxj])
				{
					maxi = i; maxj = j;
				}
			}
		}
		
	}
	return make_pair(maxi, maxj);
}

int attack()
{
	queue<pair<int, int>> q;
	pair<int, int> temp = choice_attacker();
	pair<int, int> vic = victim(temp);
	int sx = temp.first; int sy = temp.second;
	
	ad[turn - 1][sx][sy] += n + m;
	history[sx][sy] = turn;
	int ex = vic.first; int ey = vic.second;
	if (ex == -1 || ey == -1)
	{
		ad[turn - 1][sx][sy] -= n + m;
		k = 0;
		return ad[turn - 1][sx][sy];
	}
	is_active[turn - 1][sx][sy] = 1;
	is_active[turn - 1][ex][ey] = 1;
	
	int is_rei = 0;
	q.push(make_pair(sx, sy));
	while (!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		if (x == ex && y == ey)
		{
			is_rei = 1;
			break;
		}
		for (int i = 0; i < 4; i++)
		{
			int nx = x + rei_dx[i];
			int ny = y + rei_dy[i];
			if (nx == n) nx = 0;
			else if (nx == -1) nx = n - 1;
			if (ny == m) ny = 0;
			else if (ny == -1) ny = m - 1;
			if (!ad[turn - 1][nx][ny] || visited[nx][ny]) continue;
			visited[nx][ny] = true;
			q.push(make_pair(nx, ny));
			back_x[nx][ny] = x; back_y[nx][ny] = y;
		}
	}

	if (is_rei)
	{
		ad[turn - 1][ex][ey] -= ad[turn - 1][sx][sy];
		if (ad[turn - 1][ex][ey] <= 0)
		{
			ad[turn - 1][ex][ey] = 0;
		}

		int x = back_x[ex][ey]; int y = back_y[ex][ey];
		while (!(x == sx && y == sy))
		{
			ad[turn - 1][x][y] -= ad[turn - 1][sx][sy] / 2;
			is_active[turn - 1][x][y] = 1;
			if (ad[turn - 1][x][y] < 0)
			{
				ad[turn - 1][x][y] = 0;
			}
			int nx = back_x[x][y]; int ny = back_y[x][y];
			x = nx;
			y = ny;
		}
	}

	if (!is_rei)
	{
		ad[turn - 1][ex][ey] -= ad[turn - 1][sx][sy];
		for (int i = 0; i < PO; i++)
		{
			int x = (ex + po_dx[i] + n) % n;
			int y = (ey + po_dy[i] + m) % m;
			if (x == sx && y == sy) continue;
			if (ad[turn - 1][x][y] == 0) continue;
			ad[turn - 1][x][y] -= ad[turn - 1][sx][sy] / 2;
			if (ad[turn - 1][x][y] <= 0) ad[turn - 1][x][y] = 0;
			is_active[turn - 1][x][y] = 1;
		}
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if (ad[turn - 1][i][j] <= 0) ad[turn - 1][i][j] = 0;
			ad[turn][i][j] = ad[turn - 1][i][j];
			if (ad[turn][i][j] && !is_active[turn - 1][i][j])
			{
				ad[turn][i][j]++;
			}
		}
	int potap = 0;
	int max_ad = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			int t_ad = ad[turn][i][j];
			if (t_ad > 0) potap++;
			if (max_ad < t_ad) max_ad = t_ad;
			visited[i][j] = false;
		}
	if (potap <= 1) return max_ad;
	return max_ad;
}

int main()
{
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> ad[0][i][j];
		}
	}
	
	int ans;
	while (turn <= k)
	{
		ans = attack();
		if (ans == 0)
		{
			cout << 0;
			return 0;
		}
		turn++;
	}
	cout << ans;
}