#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
#define EMPTY make_tuple(-1,-1,-1,-1,-1,-1)
#define Player tuple<int,int,int,int,int,int> // num, x, y, d, s 번호, 좌표, 방향, 초기 능력치, 총 능력치
int n, m, k;
Player player[400];
vector<int> gun[21][21];
int point[400];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

bool inRange(int x, int y)
{
	return (0 <= x && x < n && 0 <= y && y < n);
}

tuple<int, int, int> getNext(Player p)
{
	int x, y, d;
	tie(ignore, x, y, d, ignore, ignore) = p;
	int nx = x + dx[d];
	int ny = y + dy[d];
	if (!inRange(nx, ny))
	{
		if (d >= 2) d -= 2;
		else d += 2;
		nx = x + dx[d];
		ny = y + dy[d];
	}
	return make_tuple(nx, ny,d);
}

Player Find(int x, int y)
{
	for (int i = 0; i < m; i++)
	{
		int n, r, c;
		tie(n, r, c, ignore, ignore, ignore) = player[i];
		if (r == x && c == y)
		{
			return player[i];
		}
	}
	return EMPTY;
}

void Update(Player p)
{
	int num;
	tie(num, ignore, ignore, ignore, ignore, ignore) = p;
	for (int i = 0; i < m; i++)
	{
		int num_i;
		tie(num_i, ignore, ignore, ignore, ignore, ignore) = player[i];
		if (num == num_i)
		{
			player[i] = p;
			break;
		}
	}
}

void getGun(Player p)
{
	int num, x, y, d, a, g;
	tie(num, x, y, d, a, g) = p;
	gun[x][y].push_back(g);
	sort(gun[x][y].rbegin(), gun[x][y].rend());
	int new_gun = gun[x][y][0];
	gun[x][y].erase(gun[x][y].begin());
	Update(make_tuple(num, x, y, d, a, new_gun));
}

void LoserMove(Player p)
{
	int num, x, y, d, a, g;
	tie(num, x, y, d, a, g) = p;
	gun[x][y].push_back(g);
	g = 0;
	for (int i = 0; i < 4; i++)
	{
		int dir = (d + 1) % 4;
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		if (inRange(nx, ny) && Find(nx, ny) == EMPTY)
		{
			Update(make_tuple(num, nx, ny, dir, a, g));
			getGun(player[num]);
			break;
		}
	}
}

void Duel(Player p1, Player p2)
{
	int n1, s1, a1, n2, s2, a2;
	tie(n1, ignore, ignore, ignore, s1, a1) = p1;
	tie(n2, ignore, ignore, ignore, s2, a2) = p2;
	if (make_pair((s1+a1), s1) > make_pair((s2+a2), s2))
	{
		point[n1] += (s1 + a1) - (s2 + a2);
		LoserMove(p2);
		getGun(p1);
	}
	else
	{
		point[n2] += (s2 + a2) - (s1 + a1);
		LoserMove(p1);
		getGun(p2);
	}
}

void Simulate()
{
	for (int i = 0; i < m; i++)
	{
		int num, x, y, d, s, a;
		tie(num, x, y, d, s, a) = player[i];
		int nx, ny, nd;
		tie(nx, ny, nd) = getNext(player[i]);
		Player next_player = Find(nx, ny);
		Update(make_tuple(num, nx, ny, nd, s, a));

		if (next_player == EMPTY)
		{
			getGun(player[i]);
		}
		else
		{
			Duel(player[i], next_player);
		}
	}
}

int main()
{
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int g;
			cin >> g;
			gun[i][j].push_back(g);
		}
	}
	for (int i = 0; i < m; i++)
	{
		int x, y, d, s;
		cin >> x >> y >> d >> s;
		x--; y--;
		player[i] = make_tuple(i, x, y, d, s, 0);
	}

	while (k--)
	{
		Simulate();
	}

	for (int i = 0; i < m; i++)
	{
		cout << point[i] << " ";
	}
}