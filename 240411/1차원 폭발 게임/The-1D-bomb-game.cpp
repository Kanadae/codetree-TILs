#include <iostream>

using namespace std;
int n, m;
int map[101];
int temp[101];

void Print()
{
	for (int i = 0; i < n; i++)
		cout << map[i] << " ";
	cout << "\n";
}

void makeZero(int start, int end)
{
	for (int i = start; i <= end; i++)
	{
		map[i] = 0;
	}
}

void copytemp()
{
	int tidx = 0;
	int zero = 0;
	for (int i = 0; i < n; i++)
	{
		if (map[i] == 0) continue;
		temp[tidx++] = map[i];
	}

	n = tidx;
	for (int i = 0; i < n; i++)
	{
		map[i] = temp[i];
		temp[i] = 0;
	}

}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		cin >> map[i];
	}

	bool is_bombed = false;
	do{
		is_bombed = false;
		int start = 0; int end = 0;
		for (int i = 0; i < n; i++)
		{
			if (i < start) continue;
			for (int j = i + 1; j < n; j++)
			{
				if (map[i] != map[j])
				{
					break;
				}
				end++;
			}
			if (start == end)
			{
				start = start + 1;
				end = start;
			}
			else if (start - end == m)
			{
				makeZero(start, end);
				start = end + 1;
				end = start;
				is_bombed = true;
			}
			else
			{
				makeZero(start, end);
				start = end + 1;
				end = start;
				is_bombed = true;
			} 
		}
		copytemp();

	} while (is_bombed);

	cout << n << "\n";
	for (int i = 0; i < n; i++)
	{
		cout << map[i] << "\n";
	}

}