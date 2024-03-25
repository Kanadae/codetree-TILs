#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int n, k, u, d;
int map[9][9];
vector<pair<int, int>> vec;
queue<pair<int, int>> q;
int city;
int max_city;
bool visited[9][9];

bool canGo(int x, int y)
{
    if (0 > x || x >= n || 0 > y || y >= n) return false;
    if (visited[x][y]) return false;
    return true;
}

void bfs()
{
    int dx[4] = { 0, -1, 0, 1 };
    int dy[4] = { 1, 0, -1, 0 };
    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if (canGo(new_x, new_y))
            {
                int diff = abs(map[x][y] - map[new_x][new_y]);
                if (diff >= u && d >= diff)
                {
                    city++;
                    cout << new_x << " " << new_y << " " << x << " " << y << endl;
                    cout << city << endl;
                    visited[new_x][new_y] = true;
                    q.push(make_pair(new_x, new_y));
                }
                
            }

        }
    }
}

void choose(int cur, int x, int y)
{
    if (x == n && y == n || cur == k)
    {
        if (cur != k) return;
        for (int i = 0; i < k; i++)
        {
            int start_x = vec[i].first;
            int start_y = vec[i].second;
            if (!visited[start_x][start_y])
            {
                city++;
                visited[start_x][start_y] = true;
            }
            q.push(make_pair(start_x, start_y));
            bfs();
        }
        if (max_city < city) max_city = city;
        city = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                visited[i][j] = false;
            }
        }
        return;
    }
    if (y == n) {
        if (x < n - 1) {
            x++;
            y = 0;
        } else
        {
            x = n;
            y = n;
            choose(cur, n, n);
            return;
        }
    }
    vec.push_back(make_pair(x, y));
    choose(cur + 1, x, y + 1);
    vec.pop_back();
    choose(cur, x, y + 1);
}

int main() {
    cin >> n >> k >> u >> d;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }

    choose(0, 0, 0);
    cout << max_city;
    return 0;
}