#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int n, k;
int wall;
pair<int,int> wall_xy[8];
int map[101][101];
int step[101][101];
int r1,c1,r2,c2;
int visited[101][101];
vector<pair<int,int>> vec;
queue<pair<int,int>> q;

int ans = INT_MAX;

void bfs()
{
    int dx[4] = {0,-1,0,1};
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
            if (0 > nx || nx >= n || 0 > ny || ny >= n) continue;
            if (visited[nx][ny]) continue;
            if (map[nx][ny] == 1) continue;
            visited[nx][ny] = true;
            step[nx][ny] = step[x][y] + 1;
            q.push(make_pair(nx,ny));
        }
    }
}

void dfs(int cur, int idx)
{
    if (cur == k || idx == wall)
    {
        if (cur != k) return;
        for (int i = 0; i < k; i++)
        {
            int x = vec[i].first;
            int y = vec[i].second;
            map[x][y] = 0;
        }

        q.push(make_pair(r1,c1));
        bfs();

        if (visited[r2][c2])
        {
            if (ans > step[r2][c2]) ans = step[r2][c2];
        }

        for (int i = 0; i < k; i++)
        {
            int x = vec[i].first;
            int y = vec[i].second;
            map[x][y] = 1;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                step[i][j] = 0;
                visited[i][j] = false;
            }
        }

        return;
    }

    vec.push_back(wall_xy[idx]);
    dfs(cur+1,idx+1);
    vec.pop_back();
    dfs(cur,idx+1);
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == 1)
            {
                wall_xy[wall++] = make_pair(i,j);
            }
        }
    }
    cin >> r1 >> c1 >> r2 >> c2;
    r1--; c1--; r2--; c2--;
    
    dfs(0,0);

    if (ans == INT_MAX) cout << -1;
    else cout << ans;
    return 0;
}