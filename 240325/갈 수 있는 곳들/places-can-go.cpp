#include <iostream>
#include <queue>
using namespace std;
int n, k;
queue<pair<int,int>> q;
bool visited[101][101];
int map[101][101];
int ans;

bool Cango(int x, int y)
{
    if (0 > x || x >= n || 0 > y || y >= n) return false;
    if (visited[x][y]) return false;
    if (map[x][y]) return false;
    return true;
}

void bfs()
{
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    while (!q.empty())
    {
        int x, y;
        x = q.front().first;
        y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if (Cango(new_x,new_y))
            {
                visited[new_x][new_y] = true;
                ans++;
                q.push(make_pair(new_x,new_y));
            }
        }
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

    for (int i = 0; i < k; i++)
    {
        int x,y;
        cin >> x >> y;
        x--; y--;
        q.push(make_pair(x,y));
        bfs();
    }
    cout << ans;
    return 0;
}