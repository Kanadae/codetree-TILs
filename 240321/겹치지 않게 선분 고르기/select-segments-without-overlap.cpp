#include <iostream>
#include <vector>
using namespace std;

int n;
pair<int,int> line[16];
vector<int> vec;
int cnt = 1;
int max_cnt = 0;

void calc()
{
	int x = line[0].first;
	int y = line[0].second;
	int sig;
	for (int i = 1; i < n; i++)
	{
		int tx = line[i].first;
		int ty = line[i].second;
		if (tx == x || ty == y) continue;
		if (tx > x) sig = 1; else sig = 0;
		if (sig)
		{
			if (y >= tx) continue;
		}
		else if (ty >= x) continue;
		cnt++;
	}
	if (max_cnt < cnt) max_cnt = cnt;
	cnt = 1;
}

void choose(int cur)
{
	if (cur == n)
	{
		calc();
		return;
	}

	for (int i = 0; i < n; i++)
	{
		vec.push_back(i);
		choose(cur + 1);
		vec.pop_back();
	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		line[i] = make_pair(x, y);
	}
	choose(0);
	cout << max_cnt;
	return 0;
}