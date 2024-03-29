#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, m, kk;
int map[10][10]; // 현재 맵의 양분
int nut[10][10]; // 사이클마다 추가될 양분
int virus_cnt[10][10]; // 각 칸마다 바이러스 개수
vector<int> age[10][10]; // 각 칸의 바이러스 나이 (바이러스 개수만큼 존재)

int die_virus[10][10]; // 죽고나서 영양분 추가
int die_cnt[10][10]; // 죽은 바이러스 개수만큼 pop_back()

int new_virus[10][10];

int dx[8] = { -1,-1,0,1,1,1,0,-1 };
int dy[8] = { 0,1,1,1,0,-1,-1,-1 };

int main()
{
	cin >> n >> m >> kk;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> nut[i][j];
			map[i][j] = 5;
		}
	}
	for (int i = 0; i < m; i++)
	{
		int r, c, a;
		cin >> r >> c >> a;
		r--; c--;
		virus_cnt[r][c]++;
		age[r][c].push_back(a);
	}
	
	while (kk--)
	{
		// 나이순으로 오름차순 정렬
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				sort(age[i][j].begin(), age[i][j].end());
				
			}
		}
		
		// 어린 나이순으로 양분 섭취
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				for (int k = 0; k < virus_cnt[i][j]; k++)
				{
					if (age[i][j][k] > map[i][j])
					{
						die_cnt[i][j]++;
						die_virus[i][j] = die_virus[i][j] + age[i][j][k] / 2;
						
					}
					else
					{
						map[i][j] -= age[i][j][k];
						age[i][j][k]++;
					}
				}
			}
		}
		

		// 죽은만큼 양분 더하기, 바이러스 죽이기
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				map[i][j] += die_virus[i][j]; // 시체 영양분
				die_virus[i][j] = 0;
				for (int k = 0; k < die_cnt[i][j]; k++)
				{
					virus_cnt[i][j]--;
					age[i][j].pop_back();
				}
				die_cnt[i][j] = 0;
			}
		}

		// 번식
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				for (int k = 0; k < virus_cnt[i][j]; k++)
				{
					if (age[i][j][k] % 5 == 0) // 번식
					{
						for (int d = 0; d < 8; d++)
						{
							int new_x = i + dx[d];
							int new_y = j + dy[d];
							if (0 > new_x || new_x >= n || 0 > new_y || new_y >= n) continue;
							new_virus[new_x][new_y]++;
						}
					}
				}
			}
		}

		// nut 추가
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				map[i][j] += nut[i][j];
				for (int k = 0; k < new_virus[i][j]; k++)
				{
					virus_cnt[i][j]++;
					age[i][j].push_back(1);
				}
				new_virus[i][j] = 0;
			}
		}
		
	}


	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			ans += virus_cnt[i][j];
		}
	}

	cout << ans;
}