#include <iostream>
using namespace std;
int map[4][4];
int d;
int dx[4] = { -1,0,1,0 }; // 위, 오른쪽, 아래, 왼쪽
int dy[4] = { 0,1,0,-1 };
int temp[4][4];

void Print()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << map[i][j] << " ";
		}
		cout << "\n";
	}
}

void upmove()
{
	for (int j = 0; j < 4; j++)
	{
		int start = 0; int end = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int k = i + 1; k < 4; k++)
			{
				if (map[k][j] == 0) continue;
				if (map[i][j] == map[k][j])
				{
					map[i][j] = map[i][j] * 2;
					map[k][j] = 0;
					i = k; break;
				}
				else {
					break;
				}
			}
		}
	}
	
	for (int j = 0; j < 4; j++)
	{
		int tidx = 0;
		for (int i = 0; i < 4; i++)
		{
			if (map[i][j] == 0) continue;
			temp[tidx++][j] = map[i][j];
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			map[i][j] = temp[i][j];
			temp[i][j] = 0;
		}
	}

	//Print();
}

void downmove()
{
	for (int j = 0; j < 4; j++)
	{
		int start = 0; int end = 0;
		for (int i = 3; i >= 0; i--)
		{
			for (int k = i - 1; k >= 0; k--)
			{
				if (map[k][j] == 0) continue;
				if (map[i][j] == map[k][j])
				{
					map[i][j] = map[i][j] * 2;
					map[k][j] = 0;
					i = k; break;
				}
				else {
					break;
				}
			}
		}
	}
	
	for (int j = 0; j < 4; j++)
	{
		int tidx = 3;
		for (int i = 3; i >= 0; i--)
		{
			if (map[i][j] == 0) continue;
			temp[tidx--][j] = map[i][j];
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			map[i][j] = temp[i][j];
			temp[i][j] = 0;
		}
	}

}

void leftmove()
{
	for (int i = 0; i < 4; i++)
	{
		int start = 0; int end = 0;
		for (int j = 0; j < 4; j++)
		{
			for (int k = j + 1; k < 4; k++)
			{
				if (map[i][k] == 0) continue;
				if (map[i][j] == map[i][k])
				{
					map[i][j] = map[i][j] * 2;
					map[i][k] = 0;
					j = k; break;
				}
				else {
					break;
				}
			}
		}
	}
	
	for (int i = 0; i < 4; i++)
	{
		int tidx = 0;
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j] == 0) continue;
			temp[i][tidx++] = map[i][j];
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			map[i][j] = temp[i][j];
			temp[i][j] = 0;
		}
	}

	//Print();
}

void rightmove()
{
	for (int i = 0; i < 4; i++)
	{
		int start = 0; int end = 0;
		for (int j = 3; j >= 0; j--)
		{
			for (int k = j - 1; k >= 0; k--)
			{
				if (map[i][k] == 0) continue;
				if (map[i][j] == map[i][k])
				{
					map[i][j] = map[i][j] * 2;
					map[i][k] = 0;
					j = k; break;
				}
				else {
					break;
				}
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		int tidx = 3;
		for (int j = 3; j >= 0; j--)
		{
			if (map[i][j] == 0) continue;
			temp[i][tidx--] = map[i][j];
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			map[i][j] = temp[i][j];
			temp[i][j] = 0;
		}
	}
}

int main()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cin >> map[i][j];
		}
	}
	char tempd;
	cin >> tempd;
	if (tempd == 'U')
		upmove();
	else if (tempd == 'R')
		rightmove();
	else if (tempd == 'D')
		downmove();
	else if (tempd == 'L')
		leftmove();

	Print();
}