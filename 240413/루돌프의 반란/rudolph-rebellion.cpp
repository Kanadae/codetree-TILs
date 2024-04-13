#include <iostream>
#include <tuple>
using namespace std;

int N, M, P, C, D;
pair<int, int> rudolf;
pair<int, int> santa[31];
int stun[31];
int map[51][51];
bool is_live[31];
int point[31];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

void Printmap()
{
	cout << "map : \n";
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cout << map[i][j] << " ";
		}
		cout << "\n";
	}
}
bool inRange(int x, int y)
{
	return 0 < x && x <= N && 0 < y && y <= N;
}

void moverudolf()
{
	int rx, ry;
	tie(rx, ry) = rudolf;
	int mindist = 100000000; int minx; int miny;
	int closeidx;
	for (int i = 1; i <= P; i++)
	{
		if (!is_live[i]) continue;
		int x, y;
		tie(x, y) = santa[i];
		int dist = (rx - x) * (rx - x) + (ry - y) * (ry - y);
		if (mindist > dist)
		{
			mindist = dist;
			minx = x; miny = y;
			closeidx = i;
		}
		else if (mindist == dist)
		{
			if (minx < x)
			{
				minx = x; miny = y; closeidx = i;
			}
			else if (minx == x)
			{
				if (miny < y)
				{
					minx = x; miny = y; closeidx = i;
				}
			}
		}
	}
	//cout << "closeidx : " << closeidx << "\n";
	int movex = 0, movey = 0;
	if (rx > minx)
	{
		movex = -1;
	}
	else if (rx < minx) movex = 1;
	if (ry > miny) movey = -1;
	else if (ry < miny) movey = 1;

	map[rx][ry] = 0;
	rx = rx + movex; ry = ry + movey;
	//cout << "rx ry : " << rx << " " << ry << "\n";
	rudolf = { rx,ry };

	if (map[rx][ry] > 0)
	{
		stun[map[rx][ry]] = 2;
		point[map[rx][ry]] += C;
		int x = rx;
		int y = ry;
		int firstx = x + movex * C;
		int firsty = y + movey * C;
		int lastx = firstx; int lasty = firsty;
		while (inRange(lastx, lasty) && map[lastx][lasty] > 0)
		{
			lastx = lastx + movex;
			lasty = lasty + movey;
		}
		while (lastx != firstx || lasty != firsty)
		{
			int beforex = lastx - movex;
			int beforey = lasty - movey;
			if (!inRange(beforex, beforey)) break;
			int idx = map[beforex][beforey];
			if (!inRange(lastx, lasty))
			{
				is_live[idx] = false;
			}
			else
			{
				map[lastx][lasty] = idx;
				santa[idx] = { lastx, lasty };
			}
			lastx = beforex;
			lasty = beforey;
		}
		santa[closeidx] = { firstx, firsty };
		if (inRange(firstx, firsty))
			map[firstx][firsty] = closeidx;
		else is_live[closeidx] = false;
	}

	//cout << rx << " " << ry << "\n";
	map[rx][ry] = -1;
}

void moveSanta()
{
	for (int i = 1; i <= P; i++)
	{
		if (!is_live[i] || stun[i] > 0) continue;
		int cx = santa[i].first;
		int cy = santa[i].second;
		int mindist = (cx - rudolf.first) * (cx - rudolf.first) +
			(cy - rudolf.second) * (cy - rudolf.second);
		int dir = -1;
		for (int d = 0; d < 4; d++)
		{
			int nx = cx + dx[d];
			int ny = cy + dy[d];
			if (!inRange(nx, ny) || map[nx][ny] > 0) continue;
			int dist = (nx - rudolf.first) * (nx - rudolf.first) +
				(ny - rudolf.second) * (ny - rudolf.second);
			if (mindist > dist)
			{
				mindist = dist;
				dir = d;
			}
		}
		if (dir == -1) continue;
		int x = cx + dx[dir];
		int y = cy + dy[dir];
		if (rudolf == make_pair(x, y))
		{
			stun[i] = 2;
			point[i] += D;
			int movex = -dx[dir];
			int movey = -dy[dir];
			int firstx = x + movex * D;
			int firsty = y + movey * D;
			int lastx = firstx; int lasty = firsty;
			while (inRange(lastx, lasty) && map[lastx][lasty] > 0)
			{
				lastx = lastx + movex;
				lasty = lasty + movey;
			}
			
			while (lastx != firstx || lasty != firsty)
			{
				int beforex = lastx - movex;
				int beforey = lasty - movey;
				if (!inRange(beforex, beforey)) break;
				int cur = map[beforex][beforey];
				if (!inRange(lastx, lasty))
				{
					is_live[cur] = false;
				}
				else
				{
					map[lastx][lasty] = cur;
					santa[cur] = { lastx, lasty };
				}

				lastx = beforex; lasty = beforey;
			}
			map[cx][cy] = 0;
			santa[i] = { firstx, firsty };
			if (inRange(firstx, firsty))
				map[firstx][firsty] = i;
			else is_live[i] = false;
		}
		else
		{
			map[santa[i].first][santa[i].second] = 0;
			santa[i] = { x,y };
			map[x][y] = i;
		}
	}
}

void pluspoint()
{
	for (int i = 1; i <= P; i++)
	{
		if (is_live[i]) point[i]++;
	}
}

void decaystun()
{
	for (int i = 1; i <= P; i++)
	{
		if (stun[i] > 0) stun[i]--;
	}
}

bool isend()
{
	for (int i = 1; i <= P; i++)
	{
		if (is_live[i])
			return false;
	}
	return true;
}

void simulate()
{
	//루돌프 이동
	moverudolf();
	// 산타 이동
	moveSanta();
	decaystun();
	pluspoint();
	//Printmap();
}

void printpoint()
{
	for (int i = 1; i <= P; i++)
	{
		cout << point[i] << " ";
	}
}

int main()
{
	cin >> N >> M >> P >> C >> D;
	int r, c;
	cin >> r >> c;
	rudolf = { r,c };
	map[r][c] = -1; // 루돌프
	for (int i = 1; i <= P; i++)
	{
		int n, r, c;
		cin >> n >> r >> c;
		santa[n] = { r,c };
		map[r][c] = n;
	}

	for (int i = 1; i <= P; i++)
	{
		is_live[i] = true;
	}

	while (M--)
	{
		simulate();
		if (isend()) break;
	}

	printpoint();
}