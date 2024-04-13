#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

int n, m, k; // 격자 크기, 팀의 개수, 라운드 수

int map[21][21];
int color[21][21]; // 각 팀 색
bool visited[21][21];
int newmap[21][21];
bool tvisit[21][21];

int people[6];
int dx[4] = { 0,1,0,-1 }; 
int dy[4] = { -1,0,1,0 }; 
// 방향 상관없이 벽마주치면 가던 방향 다음 방향으로 가고
// 다음 방향도 벽이면 다음 방향의 반대방향으로 가기
int turn = 1;
int t;
int ans = 0;

bool inRange(int x, int y)
{
	return 0 <= x && x < n && 0 <= y && y < n;
}

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

void Move()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			// 머리 찾아내기
			if (map[i][j] != 1) continue;
			int hx = i; int hy = j; // 머리 위치
			int culcor = color[hx][hy]; // 현재 바닥 색
			// 1. 리더 방향 찾고, 리더 움직이기
			int ld = 0;
			for (int d = 0; d < 4; d++)
			{
				int nx = hx + dx[d]; int ny = hy + dy[d];
				if (map[nx][ny] == 2 || map[nx][ny] == 3)
				{
					if (d < 2) ld = d += 2;
					else ld = d -= 2;
					break;
				}
			}
			int nx = hx + dx[ld]; int ny = hy + dy[ld];
			if (!inRange(nx, ny) || color[nx][ny] != culcor)
			{
				ld = (ld + 1) % 4;
				nx = hx + dx[ld]; ny = hy + dy[ld];
				if (!inRange(nx, ny) || color[nx][ny] != culcor)
				{
					if (ld < 2) ld += 2;
					else ld -= 2;
					nx = hx + dx[ld]; ny = hy + dy[ld];
				}
			}
			hx = nx; hy = ny;
			newmap[hx][hy] = 1;

			int cnt = people[culcor] - 1;
			// 리더 방향 반대방향으로 걸어가면서 사람 채우기
			int dir;
			if (ld < 2) dir = ld + 2; else dir = ld - 2;
			for (int i = 0; i < cnt; i++)
			{
				int nx = hx + dx[dir];
				int ny = hy + dy[dir];
				if (!inRange(nx, ny) || color[nx][ny] != culcor)
				{
					dir = (dir + 1) % 4;
					nx = hx + dx[dir]; ny = hy + dy[dir];
					if (!inRange(nx, ny) || color[nx][ny] != culcor)
					{
						if (dir < 2) dir += 2;
						else dir -= 2;
						nx = hx + dx[dir]; ny = hy + dy[dir];
					}
				}
				hx = nx; hy = ny;
				newmap[hx][hy] = 2;
				if (i == cnt - 1) newmap[hx][hy] = 3;
 			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			map[i][j] = newmap[i][j];
			newmap[i][j] = 0;
		}
	}

}

void Throw()
{
	int temp = t / n;
	int rc = t - temp * n;
	int hitx = -1, hity = -1;
	if (temp == 0) // 왼쪽에서 공 쏨
	{
		int i = rc;
		for (int j = 0; j < n; j++)
		{
			if (map[i][j] > 0)
			{
				hitx = i; hity = j;
				break;
			}
		}
	}
	else if (temp == 1)
	{
		int j = rc;
		for (int i = n - 1; i >= 0; i--)
		{
			if (map[i][j] > 0)
			{
				hitx = i; hity = j;
				break;
			}
		}
	}
	else if (temp == 2)
	{
		int i = rc;
		for (int j = n - 1; j >= 0; j--)
		{
			if (map[i][j] > 0)
			{
				hitx = i; hity = j;
				break;
			}
		}
	}
	else if (temp == 3)
	{
		int j = rc;
		for (int i = 0; i < n; i++)
		{
			if (map[i][j] > 0)
			{
				hitx = i; hity = j;
				break;
			}
		}
	}
	if (hitx == -1 && hity == -1) return;
	// 점수 계산
	int curcol = color[hitx][hity];
	int hx, hy; // 맞은 사람의 팀에 속한 머리사람
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (curcol == color[i][j] && map[i][j] == 1)
			{
				hx = i; hy = j;
				break;
			}
		}
	}
	int headx = hx; int heady = hy;
	//cout << "map\n";
	//Print();
	//cout << hx << " " << hy;
	int ld = 0;
	for (int d = 0; d < 4; d++)
	{
		int nx = hx + dx[d]; int ny = hy + dy[d];
		if (map[nx][ny] == 2 || map[nx][ny] == 3)
		{
			ld = d;
			break;
		}
	}
	int cnt = people[curcol];
	//cout << "cnt : " << cnt <<endl;
	for (int i = 0; i < cnt - 1; i++)
	{
		int nx = hx + dx[ld];
		int ny = hy + dy[ld];
		if (!inRange(nx, ny) || color[nx][ny] != curcol)
		{
			ld = (ld + 1) % 4;
			nx = hx + dx[ld]; ny = hy + dy[ld];
			if (!inRange(nx, ny) || color[nx][ny] != curcol)
			{
				if (ld < 2) ld += 2;
				else ld -= 2;
				nx = hx + dx[ld]; ny = hy + dy[ld];
			}
		}
		if (nx == hitx && ny == hity)
		{
			ans += (i + 2) * (i + 2);
		}
		hx = nx; hy = ny;
	}
	if (headx == hitx && heady == hity) ans += 1;
	
	swap(map[hx][hy], map[headx][heady]);
	

}
// 머리랑 꼬리 바꿔야함
// 머리가 맞을때 점수 계산 안했음

void simulate()
{
	Move();
	Throw();
}

int main()
{
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
		}
	}

	// color 제작
	int curcol = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int pcnt = 0;
			if (map[i][j] == 0 || visited[i][j]) continue;
			if (map[i][j] < 4) pcnt++;
			visited[i][j] = true;
			color[i][j] = curcol;
			queue<pair<int, int>> q;
			q.push(make_pair(i, j));
			while (!q.empty())
			{
				int x = q.front().first;
				int y = q.front().second;
				q.pop();
				for (int d = 0; d < 4; d++)
				{
					int nx = x + dx[d];
					int ny = y + dy[d];
					if (!inRange(nx, ny)) continue;
					if (map[nx][ny] == 0 || visited[nx][ny]) continue;
					if (map[nx][ny] < 4) pcnt++;
					visited[nx][ny] = true;
					q.push(make_pair(nx, ny));
					color[nx][ny] = curcol;
				}
			}

			people[curcol] = pcnt;
			curcol++;
		}
	}

	t = 0;
	while (turn <= k)
	{
		simulate();
		//cout << "map\n";
		//Print();
		turn++;
		t++;
		if (t >= 4 * n)
		{
			t = 1;
		}
		
	}

	cout << ans;
}