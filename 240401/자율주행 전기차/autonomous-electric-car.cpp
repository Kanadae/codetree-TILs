#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
int n, m, ch;
int map[21][21];
pair<int, int> goal[21][21];
int r, c;
int step[21][21];
queue<pair<int, int>> q;
bool visited[21][21];
vector<pair<int, int>> vec;

void bfs()
{
    int dx[4] = { 0,1,0,-1 };
    int dy[4] = { 1,0,-1,0 };
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
            step[nx][ny] = step[x][y] + 1;
            visited[nx][ny] = true;
            q.push(make_pair(nx, ny));
        }
    }
}

int main() {
    cin >> n >> m >> ch;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }
    cin >> r >> c;
    r--; c--;
    for (int i = 0; i < m; i++)
    {
        int xs, ys, xe, ye;
        cin >> xs >> ys >> xe >> ye;
        xs--; ys--; xe--; ye--;
        map[xs][ys] = 2; // 승객 위치
        goal[xs][ys] = make_pair(xe, ye);
    }

    while (m)
    {
        visited[r][c] = true;
        q.push(make_pair(r, c));
        bfs();
        int min_step = 1000000;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (map[i][j] != 2) continue;
                if (visited[i][j] == false) continue;
                if (min_step > step[i][j])
                {
                    vec.clear(); // vec에 min_step 2주소
                    min_step = step[i][j];
                    vec.push_back(make_pair(i, j));
                }
                else if (min_step == step[i][j])
                {
                    vec.push_back(make_pair(i, j));
                }
            }
        }
        sort(vec.begin(), vec.end());
        int cx = vec[0].first;
        int cy = vec[0].second;
        
        vec.clear();
       
        ch = ch - step[cx][cy];
      
        if (ch <= 0) // 승객 못태웠는데 연료 0 이하
        {
            break;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                visited[i][j] = false;
                step[i][j] = 0;
            }
        }

        q.push(make_pair(cx, cy));
        bfs();
        map[cx][cy] = 0;
        int gx = goal[cx][cy].first;
        int gy = goal[cx][cy].second;
        if (!visited[gx][gy]) break;
        if (ch < step[gx][gy])
        {
            break;
        }
        ch = ch - step[gx][gy];
        ch = ch + step[gx][gy] * 2;
        m--;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                visited[i][j] = false;
                step[i][j] = 0;
            }
        }

        r = gx;
        c = gy;
      
    }
    if (m != 0) cout << -1;
    else cout << ch;
    return 0;
}