#include <iostream>
#include <queue>
#include <tuple>
using namespace std;

bool visited[101][101];
queue<pair<int, int>> q;
pair<int, int> cur;
int map[101][101];
int n, k;

bool canGo(int x, int y, int target_num)
{
    if (!(0 <= x && x < n && 0 <= y && y < n)) return false;
    if (target_num <= map[x][y] || visited[x][y]) return false;
    return true;
}
void bfs()
{
    int dx[4] = { 0, 1, 0, -1 };
    int dy[4] = { 1, 0, -1, 0 };
    int cur_x = cur.first;
    int cur_y = cur.second;
    q.push(make_pair(cur_x, cur_y));
    visited[cur_x][cur_y] = true;
    int target_num = map[cur_x][cur_y];
    while (!q.empty())
    {
        pair<int, int> c = q.front();
        int x = c.first;
        int y = c.second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (canGo(nx, ny, target_num))
            {
                q.push(make_pair(nx, ny));
                visited[nx][ny] = true;
            }
        }
    }
}
bool change(pair<int, int> new_xy, pair<int, int> best)
{
    if (best == make_pair(- 1, -1)) return true;
    int nx = new_xy.first;
    int ny = new_xy.second;
    int bestx = best.first;
    int besty = best.second;
    return make_tuple(map[nx][ny], -nx, -ny) > make_tuple(map[bestx][besty], -bestx, -besty);
}

void Initial()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            visited[i][j] = false;
        }
    }
}

bool Move()
{
    Initial();
    bfs();
    pair<int, int> best = make_pair(- 1, -1);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!visited[i][j] || make_pair(i, j) == cur) continue;
            pair<int, int> new_xy = make_pair(i, j);
            if (change(new_xy, best)) best = new_xy;
        }
    }

    if (best == make_pair(- 1, -1)) return false;
    else
    {
        cur = best;
        return true;
    }
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }
    int r, c;
    cin >> r >> c;
    r--; c--;
    cur = make_pair(r,c);
    while (k--)
    {
        if (!Move()) break;
    }
    cout << cur.first + 1 << " " << cur.second + 1;
    return 0;
}