#include <iostream>
#include <vector>
using namespace std;

int n;
pair<int,int> line[16];
vector<int> vec;
int cnt = 1;
int max_cnt = 0;
int c = 1;
int visited[16];
void calc()
{
	int idx = vec[0];
	int x = line[idx].first;
	int y = line[idx].second;
	int sig;
	for (int i = 1; i < n; i++)
	{
		int tidx = vec[i];
		int tx = line[tidx].first;
		int ty = line[tidx].second;
		if (tx == x || ty == y || ty == x || tx == y) continue;
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
		if (visited[i]) continue;
		visited[i] = true;
		vec.push_back(i);
		choose(cur + 1);
		vec.pop_back();
		visited[i] = false;
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