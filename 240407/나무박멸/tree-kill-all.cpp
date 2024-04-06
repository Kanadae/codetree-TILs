#include <iostream>
using namespace std;

#define DIR 4
#define MAX_TURN 1000
#define MAX_N 20
#define MAX_LEAVE 10
int cross_dx[4] = { -1,1,1,-1 };
int cross_dy[4] = { 1,1,-1,-1 };
int tree_dx[4] = { -1,0,1,0 };
int tree_dy[4] = { 0,-1,0,1 };
int n, m, k, c;

int turn = 1;
int wall[20][20];
int tree[MAX_TURN + 1][MAX_N][MAX_N];
int dead[MAX_N][MAX_N];
int ans = 0;

bool inRange(int x, int y)
{
	return (0 <= x && x < n && 0 <= y && y < n);
}

bool canGo(int x, int y)
{
	return (inRange(x, y) && !wall[x][y] && !dead[x][y] && !tree[turn-1][x][y]);
}

void PRint()
{
	cout << "프린트 함수 호출\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << tree[turn][i][j] << " ";
		}
		cout << "\n";
	}
}

void grow()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (!tree[turn - 1][i][j]) continue;
			int cnt = 0;
			for (int d = 0; d < DIR; d++)
			{
				int x = i + tree_dx[d];
				int y = j + tree_dy[d];
				if (!inRange(x,y)) continue;
				if (tree[turn - 1][x][y] > 0) cnt++;
			}
			tree[turn - 1][i][j] += cnt;
		}
	}
}

void increase()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (!tree[turn - 1][i][j]) continue;
			int cnt = 0;
			for (int d = 0; d < DIR; d++)
			{
				int x = i + tree_dx[d];
				int y = j + tree_dy[d];
				if (canGo(x, y)) cnt++;
			}
			if (cnt == 0) continue;
			int new_t = tree[turn - 1][i][j] / cnt;
			for (int d = 0; d < DIR; d++)
			{
				int x = i + tree_dx[d];
				int y = j + tree_dy[d];
				if (canGo(x, y))
				{
					tree[turn][x][y] += new_t;
				}
			}
		}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			tree[turn][i][j] += tree[turn - 1][i][j];
		}
	
}

int get_kill(int x, int y)
{
	int cnt = 0;
	if (!tree[turn][x][y])
	{
		return cnt;
	}
	cnt = tree[turn][x][y];
	for (int d = 0; d < DIR; d++)
	{
		for (int z = 1; z <= k; z++)
		{
			int nx = x + z * cross_dx[d];
			int ny = y + z * cross_dy[d];
			if (!inRange(nx,ny)) continue;
			if (!tree[turn][nx][ny]) break;
			
			cnt += tree[turn][nx][ny];
		}
	}
	return cnt;
}

void do_kill()
{
	int max_cnt = -1;
	int x, y;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			int temp_cnt = get_kill(i, j);
			if (max_cnt < temp_cnt)
			{
				max_cnt = temp_cnt;
				x = i; y = j;
			}
		}
	
	ans += max_cnt;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (dead[i][j] > 0) dead[i][j]--;
		}
	dead[x][y] = c;
	if (tree[turn][x][y] <= 0) return;
	tree[turn][x][y] = 0;
	for (int d = 0; d < DIR; d++)
	{
		for (int z = 1; z <= k; z++)
		{
			int nx = x + z * cross_dx[d];
			int ny = y + z * cross_dy[d];
			if (!inRange(nx, ny)) break;
			dead[nx][ny] = c;
			if (wall[nx][ny]) break;
			if (tree[turn][nx][ny] <= 0) break;
			tree[turn][nx][ny] = 0;
		}
	}
	
}

void simulation()
{
	grow();
	increase();
	do_kill();
}

int main()
{
	cin >> n >> m >> k >> c;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int temp;
			cin >> temp;
			if (temp == -1) wall[i][j] = 1;
			else
			{
				tree[0][i][j] = temp;
			}
		}
	}

	while (turn <= m)
	{
		simulation();
		turn++;
	}

	cout << ans;
}