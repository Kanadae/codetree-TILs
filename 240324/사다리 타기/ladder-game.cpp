#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n, m;
vector<pair<int, int>> lines;
vector<pair<int, int>> selected;
int mini = 1000;
int ladder = 0;
bool is_sam()
{
	int ans1[12];
	int ans2[12];
	for (int i = 0; i < n; i++)
	{
		ans1[i] = ans2[i] = i;
	}

	for (int i = 0; i < lines.size(); i++)
	{
		int idx = lines[i].second;
		swap(ans1[idx], ans1[idx + 1]);
	}

	for (int i = 0; i < selected.size(); i++)
	{
		int idx = selected[i].second;
		swap(ans2[idx], ans2[idx + 1]);
	}

	for (int i = 0; i < n; i++)
	{
		if (ans1[i] != ans2[i]) return false;
	}
	return true;
}

void choose(int cnt)
{
	if (cnt == m)
	{
		if (is_sam())
		{
			ladder = selected.size();
			mini = min(ladder, mini);
		}
		return;
	}

	selected.push_back(lines[cnt]);
	choose(cnt + 1);
	selected.pop_back();
	choose(cnt + 1);
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;
		lines.push_back(make_pair(y, x - 1));
	}
	sort(lines.begin(), lines.end());
    choose(0);
	cout << mini;
}