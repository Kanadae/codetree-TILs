#include <iostream>
#include <queue>
#include <vector>
using namespace std;

queue<pair<int, int>> q;
int n, l, r;
int map[51][51];
bool visited[51][51];
int ans;
vector<pair<int, int>> vec;
int cnt;
int flag = 0;

bool canGo(int x, int y)
{
    if (0 > x || x >= n || 0 > y || y >= n) return false;
    if (visited[x][y]) return false;
    return true;
}

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
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if (canGo(new_x, new_y))
            {
                int diff = abs(map[x][y] - map[new_x][new_y]);
                if (diff >= l && diff <= r)
                {
                    visited[new_x][new_y] = true;
                    vec.push_back(make_pair(new_x, new_y));
                    q.push(make_pair(new_x, new_y));
                    flag = 1;
                }
            }
        }
    }
}

int main() {
    cin >> n >> l >> r;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }
    int sum = 0;
    int div = 0;
    do
    {
        flag = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (!visited[i][j])
                {
                    visited[i][j] = true;
                    vec.push_back(make_pair(i, j));
                    q.push(make_pair(i, j));
                    bfs();
                    for (int a = 0; a < vec.size(); a++)
                    {
                        int val = map[vec[a].first][vec[a].second];
                        sum += val;
                    }
                    div = sum / vec.size();
                    for (int a = 0; a < vec.size(); a++)
                    {
                        map[vec[a].first][vec[a].second] = div;
                    }
                    vec.clear();
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                visited[i][j] = false;
            }
        }
        if (flag == 1) ans++;
        flag = 0;
    } while (flag);
    cout << ans;
    return 0;
}