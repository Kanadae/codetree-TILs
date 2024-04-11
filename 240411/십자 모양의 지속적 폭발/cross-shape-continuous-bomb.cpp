#include <iostream>
using namespace std;

int map[200][200];
int temp[200][200];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int n, m;

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
void explode(int c)
{
	int exp = 0;
	for (int i = 0; i < n; i++)
	{
		if (map[i][c] != 0)
		{
			exp = i;
			break;
		}
	}

	int x = exp; int y = c;
	int bomb = map[x][y];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < bomb; j++)
		{
			int nx = x + j * dx[i];
			int ny = y + j * dy[i];
			if (!inRange(nx, ny)) continue;
			map[nx][ny] = 0;
		}
	}
}

void Move()
{
	for (int j = 0; j < n; j++)
	{
		int tidx = n - 1;
		for (int i = n - 1; i >= 0; i--)
		{
			if (map[i][j] == 0) continue;
			temp[tidx--][j] = map[i][j];
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			map[i][j] = temp[i][j];
			temp[i][j] = 0;
		}
	}

}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < m; i++)
	{
		int c;
		cin >> c; c--;
		explode(c);
		Move();
	}
	Print();
}