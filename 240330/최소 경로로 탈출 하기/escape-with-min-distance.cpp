#include <iostream>
#include <queue>
using namespace std;
int n,m;
queue<pair<int,int>> q;
int map[101][101];
int step[101][101];
int visited[101][101];

void bfs()
{
    int dx[4] = {0,1,0,-1};
    int dy[4] = {1,0,-1,0};
    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (0 > nx || nx >= n || 0 > ny || ny >= m) continue;
            if (visited[nx][ny]) continue;
            if (map[nx][ny] == 0) continue;
            step[nx][ny] = step[x][y] + 1;
            visited[nx][ny] = true;
            q.push(make_pair(nx,ny));
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
        }
    }

    q.push(make_pair(0,0));
    bfs();
    if (visited[n-1][m-1] == false) cout << -1;
    else cout << step[n-1][m-1];
    return 0;
}