#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int n, m, k;
bool visited[101][101];
int map[101][101];
vector<pair<int, int>> stone;
vector<pair<int, int>> vec;
vector<pair<int, int>> start;
queue<pair<int, int>> q;
int root;
int max_root;

bool canGo(int x, int y)
{
    if (0 > x || x >= n || 0 > y || y >= n) return false;
    if (map[x][y]) return false;
    if (visited[x][y]) return false;
    return true;
}

void bfs()
{
    int dx[4] = { 0, 1, 0, -1 };
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
                root++;
                visited[new_x][new_y] = true;
                q.push(make_pair(new_x, new_y));
            }
        }
    }
}

void choose(int cur, int s)
{
    if (cur == stone.size())
    {
        if (s != m) return;
        for (int i = 0; i < vec.size(); i++)
        {
            int x, y;
            x = vec[i].first;
            y = vec[i].second;
            map[x][y] = 0;
        }
        for (int i = 0; i < k; i++)
        {
            int start_x, start_y;
            start_x = start[i].first;
            start_y = start[i].second;
            if (!visited[start_x][start_y])
            {
                visited[start_x][start_y] = true;
                root++;
            } else continue;
            q.push(make_pair(start_x, start_y));
            bfs();
        }
        if (max_root < root) max_root = root;
        root = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                visited[i][j] = false;
            }
        }
        for (int i = 0; i < vec.size(); i++)
        {
            int x,y;
            x = vec[i].first;
            y = vec[i].second;
            map[x][y] = 1;
        }
        return;
    }
    vec.push_back(stone[cur]);
    choose(cur + 1, s + 1);
    vec.pop_back();
    choose(cur + 1, s);
}

int main() {
    cin >> n >> k >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == 1) stone.push_back(make_pair(i, j));
        }
    }
    for (int i = 0; i < k; i++)
    {
        int x, y;
        cin >> x >> y;
        x--; y--;
        start.push_back(make_pair(x, y));
    }

    choose(0, 0);
    cout << max_root;
    return 0;
}