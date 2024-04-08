#include <iostream>

using namespace std;

int n;
int arr[29][29]; // 숫자 관리
int group_cnt[900];
int group_n;
int ans = 0;
int group[29][29]; // 각 위치 그룹 번호 관리
bool visited[29][29];
int next_arr[29][29];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

bool inRange(int x, int y)
{
	return 0 <= x && x < n && 0 <= y && y < n;
}

void DFS(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i]; int ny = y + dy[i];
		if (inRange(nx, ny) && !visited[nx][ny] && arr[x][y] == arr[nx][ny])
		{
			visited[nx][ny] = true;
			group_cnt[group_n]++;
			group[nx][ny] = group_n;
			DFS(nx, ny);
		}
	}
}

void makeGroup()
{
	group_n = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			visited[i][j] = false;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (visited[i][j]) continue;
			group_n++;
			group_cnt[group_n] = 1;
			visited[i][j] = true;
			group[i][j] = group_n;
			DFS(i, j);
		}
}

int calc()
{
	int score = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			for (int d = 0; d < 4; d++)
			{
				int nx = i + dx[d]; int ny = j + dy[d];
				if (inRange(nx, ny) && arr[nx][ny] != arr[i][j])
				{
					int g1 = group[i][j]; int g2 = group[nx][ny]; // 각 그룹 번호
					int n1 = group_cnt[g1]; int n2 = group_cnt[g2]; // 그룹에 속한 개수
					score += (n1 + n2) * arr[i][j] * arr[nx][ny];
				}
			}
		}

	return score / 2;
}

int getScore()
{
	makeGroup();
	return calc();
}

void rotateSquare(int sx, int sy, int square_n)
{
	for (int x = sx; x < sx+square_n; x++)
		for (int y = sy; y < sy + square_n; y++)
		{
			int ox = x - sx; int oy = y - sy;
			int rx = oy; int ry = square_n - ox - 1;
			next_arr[rx + sx][ry + sy] = arr[x][y];
		}
}

void rotate()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			next_arr[i][j] = 0;

	int square_n = n / 2;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (j == square_n)
			{
				next_arr[j][i] = arr[i][j];
			}

			if (i == square_n)
			{
				next_arr[n - j - 1][i] = arr[i][j];
			}
		}
	rotateSquare(0, 0, square_n);
	rotateSquare(0, square_n + 1, square_n);
	rotateSquare(square_n + 1, 0, square_n);
	rotateSquare(square_n + 1, square_n + 1, square_n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			arr[i][j] = next_arr[i][j];
}

int main()
{
	cin >> n;
	for (int i =0; i< n; i++)
		for (int j = 0; j < n; j++)
		{
			cin >> arr[i][j];
		}
	int ans = 0;
	for (int i = 0; i < 4; i++)
	{
		// 예술 점수 구하기
		ans += getScore();
		// 회전
		rotate();
	}
	cout << ans;
}