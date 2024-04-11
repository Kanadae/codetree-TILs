#include <iostream>
#include <vector>
using namespace std;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int n;
int map[21][21];
int new_map[21][21];
int temp_map[21][21];
vector<int> dir;
int maxi = 0;

void Print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << new_map[i][j] << " ";
		}
		cout << "\n";
	}
}

void upmove()
{
	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < n; i++)
		{

			for (int k = i + 1; k < n; k++)
			{
				if (new_map[k][j] == 0) continue;
				if (new_map[i][j] == new_map[k][j])
				{
					new_map[i][j] = new_map[i][j] * 2;
					new_map[k][j] = 0;
					i = k;
				} else
				{
					break;
				}
			}
		}
	}

	for (int j = 0; j < n; j++)
	{
		int tempidx = 0;
		for (int i = 0; i < n; i++)
		{
			if (new_map[i][j] == 0) continue;
			temp_map[tempidx++][j] = new_map[i][j];
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			new_map[i][j] = temp_map[i][j];
			temp_map[i][j] = 0;
		}
	}
}

void downmove()
{
	for (int j = 0; j < n; j++)
	{
		for (int i = n - 1; i >= 0; i--)
		{
			for (int k = i - 1; k >= 0; k--)
			{
				if (new_map[k][j] == 0) continue;
				if (new_map[i][j] == new_map[k][j])
				{
					new_map[i][j] = new_map[i][j] * 2;
					new_map[k][j] = 0;
					i = k;
				}
				else
				{
					break;
				}
			}
		}
	}

	for (int j = 0; j < n; j++)
	{
		int tempidx = n-1;
		for (int i = n-1; i >= 0; i--)
		{
			if (new_map[i][j] == 0) continue;
			temp_map[tempidx--][j] = new_map[i][j];
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			new_map[i][j] = temp_map[i][j];
			temp_map[i][j] = 0;
		}
	}
}

void rightmove()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = n - 1; j >= 0; j--)
		{
			for (int k = j - 1; k >= 0; k--)
			{
				if (new_map[i][k] == 0) continue;
				if (new_map[i][j] == new_map[i][k])
				{
					new_map[i][j] = new_map[i][j] * 2;
					new_map[i][k] = 0;
					j = k;
				}
				else
				{
					break;
				}
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		int tempidx = n - 1;
		for (int j = n - 1; j >= 0; j--)
		{
			if (new_map[i][j] == 0) continue;
			temp_map[i][tempidx--] = new_map[i][j];
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			new_map[i][j] = temp_map[i][j];
			temp_map[i][j] = 0;
		}
	}
}

void leftmove()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = j + 1; k < n; k++)
			{
				if (new_map[i][k] == 0) continue;
				if (new_map[i][j] == new_map[i][k])
				{
					new_map[i][j] = new_map[i][j] * 2;
					new_map[i][k] = 0;
					j = k;
				}
				else
				{
					break;
				}
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		int tempidx = 0;
		for (int j = 0; j < n; j++)
		{
			if (new_map[i][j] == 0) continue;
			temp_map[i][tempidx++] = new_map[i][j];
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			new_map[i][j] = temp_map[i][j];
			temp_map[i][j] = 0;
		}
	}
}

void simulate(int d)
{
	if (d == 0) // 위
	{
		upmove();
	}
	else if (d == 1) // 오른쪽
	{
		rightmove();
	}
	else if (d == 2) // 아래
	{
		downmove();
	}
	else if (d == 3) // 왼쪽
	{
		leftmove();
	}


}

void dfs(int cur)
{
	if (cur == 5)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				new_map[i][j] = map[i][j];
			}
		}

		for (int i = 0; i < 5; i++)
		{
			simulate(dir[i]);
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (maxi < new_map[i][j])
					maxi = new_map[i][j];
			}
		}
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		dir.push_back(i);
		dfs(cur + 1);
		dir.pop_back();
	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
			new_map[i][j] = map[i][j];
		}
	}
	
	dfs(0);
	cout << maxi;
}