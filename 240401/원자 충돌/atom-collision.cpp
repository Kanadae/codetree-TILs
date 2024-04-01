#include <iostream>
#include <climits>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

// 모두 같은 방향이면 상하좌우, 상하좌우+대각선이면 대각선
int n, m, k; // 격자 크기, 원자 개수, 시간

int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

vector<tuple<int, int, int>> vec[51][51];
vector<tuple<int, int, int>> temp_vec[51][51];

int main()
{
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++)
	{
			int x, y, m, s, d;
			cin >> x >> y >> m >> s >> d; // 질량,속력,방향
			x--; y--;
			vec[x][y].push_back(make_tuple(m, s, d));

	}

	while (k--)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (vec[i][j].size() == 0) continue;
				for (int t = 0; t < vec[i][j].size(); t++)
				{
					int x = i; int y = j;
					int tm, ts, td;
					tie(tm, ts, td) = vec[i][j][t];
					
					for (int rate = 0; rate < ts; rate++)
					{
						int nx = x + dx[td];
						int ny = y + dy[td];
						if (0 > nx) x = n - 1;
						else if (nx >= n) x = 0;
						else x = nx;
						if (0 > ny) y = n - 1;
						else if (ny >= n) y = 0;
						else y = ny;
					}
					temp_vec[x][y].push_back(make_tuple(tm, ts, td));
				}
				vec[i][j].clear();
			}
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (temp_vec[i][j].size() == 0)continue;
				for (int size = 0; size < temp_vec[i][j].size(); size++)
				{
					int tm, ts, td;
					tie(tm, ts, td) = temp_vec[i][j][size];
					vec[i][j].push_back(make_tuple(tm, ts, td));
				}
				temp_vec[i][j].clear();
			}
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (vec[i][j].size() <= 1) continue;
				int msum = 0; // 무게합
				int ssum = 0; // 속도합
				int ud = 0, cross = 0; // 상하좌우 방향 , 대각선 방향 존재여부
				for (int size = 0; size < vec[i][j].size(); size++)
				{
					int tm, ts, td;
					tie(tm, ts, td) = vec[i][j][size];
					msum += tm;
					ssum += ts;
					if (td % 2 == 0) ud++;
					else cross++;
				}
				
				if (msum < 5)
				{
					vec[i][j].clear();
					continue;
				}

				msum = msum / 5;
				ssum = ssum / vec[i][j].size();
				int d;
				if (ud * cross == 0)
				{
					d = 0;
				}
				else d = 1;

				for (int ii = 0; ii < 4; ii++)
				{
					temp_vec[i][j].push_back(make_tuple(msum, ssum, d));
					d = d + 2;
				}
				vec[i][j].clear();
			}
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (temp_vec[i][j].size() == 0) continue;
				for (int size = 0; size < temp_vec[i][j].size(); size++)
				{
					int tm, ts, td;
					tie(tm, ts, td) = temp_vec[i][j][size];
					vec[i][j].push_back(make_tuple(tm, ts, td));
				}
				temp_vec[i][j].clear();
			}
		}

	}
	
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (vec[i][j].size() == 0) continue;
			for (int size = 0; size < vec[i][j].size(); size++)
			{
				int tm, ts, td;
				tie(tm, ts, td) = vec[i][j][size];
				ans += tm;
			}
		}
	}
	cout << ans;
}