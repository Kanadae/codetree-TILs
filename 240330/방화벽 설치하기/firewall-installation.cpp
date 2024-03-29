#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
int n, m;
int map[8][8];
vector<pair<int, int>> vec; // 방화벽 좌표 3개
bool visited[8][8];
pair<int, int> fire[10];
int fire_cnt;
queue<pair<int, int>> q;
int temp_burn; // 불이 도달한 칸
int min_burn = INT_MAX;
int wall;

void bfs()
{
    int dx[4] = { 0, 1,0 ,-1 };
    int dy[4] = { 1,0,-1,0 };
    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if (0 > new_x || new_x >= n || 0 > new_y || new_y >= m || visited[new_x][new_y] ||
                map[new_x][new_y] == 1) continue;
            visited[new_x][new_y] = true;
            temp_burn++;
            q.push(make_pair(new_x, new_y));
        }
    }
}

void dfs(int cur, int r, int c)
{
    if ((r == n - 1 && c == m) || cur == 3)
    {
        if (cur != 3) return;
        for (int i = 0; i < 3; i++)
        {
            int x = vec[i].first;
            int y = vec[i].second;
            map[x][y] = 1;
        }

        temp_burn = 0;
        for (int i = 0; i < fire_cnt; i++)
        {
            int x = fire[i].first;
            int y = fire[i].second;
            if (!visited[x][y])
            {
                temp_burn++;
                visited[x][y] = true;
            }
            q.push(make_pair(x, y));
            bfs();
        }
        if (min_burn > temp_burn)
        {
            min_burn = temp_burn;
        }
        for (int i = 0; i < 3; i++)
        {
            int x = vec[i].first;
            int y = vec[i].second;
            map[x][y] = 0; // 복구
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                visited[i][j] = false;
            }
        }
        return;
    }

    if (c == m)
    {
        r++; // 행 증가
        c = 0;
    }

    if (map[r][c] != 2 && map[r][c] != 1)
    {
        vec.push_back(make_pair(r, c));
        dfs(cur + 1, r, c + 1);
        vec.pop_back();
    }
    dfs(cur, r, c + 1);
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
            
            if (map[i][j] == 2)
            {
                fire[fire_cnt] = make_pair(i, j);
                fire_cnt++;
            }
            if (map[i][j] == 1)
            {
                wall++;
            }

        }
    }
    dfs(0, 0, 0);
    int ans = n * m - min_burn - 3 - wall;
    cout << ans;

    return 0;
}