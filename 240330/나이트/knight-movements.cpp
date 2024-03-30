#include <iostream>
#include <queue>
using namespace std;
int n, r1, c1, r2, c2;
int map[101][101];
int step[101][101];
int visited[101][101];

queue<pair<int,int>> q;
void bfs()
{
    int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 8; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (0 > nx || nx >= n || 0 > ny || ny >= n) continue;
            if (visited[nx][ny]) continue;
            visited[nx][ny] = true;
            step[nx][ny] = step[x][y] + 1;
            q.push(make_pair(nx,ny));
        }
    }
}

int main() {
    cin >> n;
    cin >> r1 >>c1 >> r2 >> c2;
    r1--; c1--; r2--; c2--;
    q.push(make_pair(r1,c1));
    bfs();
    if (visited[r2][c2] == false) cout << -1;
    else cout << step[r2][c2];
    return 0;
}