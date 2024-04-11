#include <iostream>
#include <vector>
using namespace std;
int n, m;
int map[26][26];
int temp[26][26];
int visited[26][26];
int tvisit[26][26];
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

int tdx[4] = { 0,1,0,-1 };
int tdy[4] = { -1,0,1,0 };
int px, py; // 현재 플레이어 위치
int score;

int lines[626];
int newlines[626];

void Print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << map[i][j] << " ";
		}
		cout << "\n";
	}
}

bool inRange(int x, int y)
{
	return 0 <= x && x < n && 0 <= y && y < n;
}

void attack(int d, int p)
{
	for (int i = 1; i <= p; i++)
	{
		int nx = px + dx[d] * i;
		int ny = py + dy[d] * i;
		if (!inRange(nx, ny)) break;
		score += map[nx][ny];
		map[nx][ny] = 0;
	}

}

void arrange() // 시작점으로부터 달팽이모양으로 걸어가면서 temp 채우기
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			tvisit[i][j] = false;
			visited[i][j] = false;
			temp[i][j] = 0;
		}
	}
	int sx = px; int sy = py;
	visited[sx][sy] = 1;
	tvisit[sx][sy] = 1;
	int sd = 3;
	int tx = sx; int ty = sy;
	int td = 3;
	while (!(sx==0 && sy == 0))
	{
		int nd = (sd + 1) % 4;
		int nx = sx + tdx[nd];
		int ny = sy + tdy[nd];
		if (!visited[nx][ny])
		{
			sx = nx; sy = ny;
			sd = nd;
		}
		else
		{
			sx = sx + tdx[sd];
			sy = sy + tdy[sd];
		}
		visited[sx][sy] = 1;

		if (map[sx][sy] != 0)
		{
			int tnd = (td + 1) % 4;
			int tnx = tx + tdx[tnd];
			int tny = ty + tdy[tnd];
			if (!tvisit[tnx][tny])
			{
				tx = tnx; ty = tny;
				td = tnd;
			}
			else
			{
				tx = tx + tdx[td];
				ty = ty + tdy[td];
			}
			tvisit[tx][ty] = 1;
			temp[tx][ty] = map[sx][sy];
		}

	}
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			map[i][j] = temp[i][j];
			temp[i][j] = 0;
			tvisit[i][j] = false;
			visited[i][j] = false;
		}
	}
	
}

bool kill() // 달팽이로 걸어가면서 연속되는거 0으로 만들기
{
	bool is_kill = false;
	int sx = px; int sy = py;
	visited[sx][sy] = 1;
	int sd = 3;
	vector<pair<int, int>> vec;
	// 일단 중복되면 벡터에 좌표 넣음
	// 벡터 사이즈 4미만이면 벡터 버림
	// 사이즈 4이상이면 벡터에 있는 좌표 0으로 만듦
	while (sx != 0 || sy != 0)
	{
		int x = sx; int y = sy; // 구 좌표
		int nd = (sd + 1) % 4;
		int nx = sx + tdx[nd];
		int ny = sy + tdy[nd];
		if (!visited[nx][ny])
		{
			sx = nx; sy = ny;
			sd = nd;
		}
		else
		{
			sx = sx + tdx[sd];
			sy = sy + tdy[sd];
		}
		visited[sx][sy] = 1;
		if (map[x][y] == map[sx][sy])
		{
			vec.push_back(make_pair(x, y));
			if (sx == 0 && sy == 0 && vec.size()>=3)
			{
				vec.push_back(make_pair(0, 0));
				for (int sz = 0; sz < vec.size(); sz++)
				{
					int delx = vec[sz].first;
					int dely = vec[sz].second;
					score += map[delx][dely];
					map[delx][dely] = 0;
					is_kill = true;
				}
				vec.clear();
			}
		}
		else if (vec.size() >= 3)
		{
			vec.push_back(make_pair(x, y));
			for (int sz = 0; sz < vec.size(); sz++)
			{
				int delx = vec[sz].first;
				int dely = vec[sz].second;
				score += map[delx][dely];
				map[delx][dely] = 0;
			}
			vec.clear();
			is_kill = true;
		}
		else
		{
			vec.clear();
		}
		if (map[sx][sy] == 0) break;

	}
	vec.clear();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			visited[i][j] = 0;
		}
	}

	return is_kill;
}

void rerange()
{
	int sx = px; int sy = py;
	visited[sx][sy] = 1;
	int sd = 3;
	int lineidx = 0;
	while (sx != 0 || sy != 0)
	{
		int nd = (sd + 1) % 4;
		int nx = sx + tdx[nd];
		int ny = sy + tdy[nd];
		if (!visited[nx][ny])
		{
			sx = nx; sy = ny;
			sd = nd;
		}
		else
		{
			sx = sx + tdx[sd];
			sy = sy + tdy[sd];
		}
		visited[sx][sy] = 1;
		lines[lineidx++] = map[sx][sy];
	}


	int start = lines[0]; int startx = 0; int endx;
	int newidx = 0;
	newlines[newidx] = start;

	for (int i = 1; i < n*n; i++)
	{	
		endx = i;
		if (lines[i] == start)
		{
			continue;
		}
		else
		{
			newlines[newidx+1] = endx - startx;
			swap(newlines[newidx], newlines[newidx + 1]);
			start = lines[i];
			newidx += 2;
			newlines[newidx] = lines[i];
			startx = i;
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			temp[i][j] = 0;
			tvisit[i][j] = false;
			visited[i][j] = false;
			lines[i + j] = 0;
		}
	}
}

void makemap()
{
	int sx = px; int sy = py;
	visited[sx][sy] = 1;
	int sd = 3;
	int lineidx = 0;
	while (sx != 0 || sy != 0)
	{
		int nd = (sd + 1) % 4;
		int nx = sx + tdx[nd];
		int ny = sy + tdy[nd];
		if (!visited[nx][ny])
		{
			sx = nx; sy = ny;
			sd = nd;
		}
		else
		{
			sx = sx + tdx[sd];
			sy = sy + tdy[sd];
		}
		visited[sx][sy] = 1;
		temp[sx][sy] = newlines[lineidx++];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			map[i][j] = temp[i][j];
			temp[i][j] = 0;
			tvisit[i][j] = false;
			visited[i][j] = false;
			newlines[i + j] = 0;
		}
	}

}

int main()
{
	cin >> n >> m;
	px = n / 2; py = n / 2;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < m; i++)
	{
		int d, p;
		cin >> d >> p;
		attack(d, p);
		
		arrange();
		
		while (kill())
		{
			arrange();
		}
		
		rerange();

		makemap();
	}
	
	cout << score;
}